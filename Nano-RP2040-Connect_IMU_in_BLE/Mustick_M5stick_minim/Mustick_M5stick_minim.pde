/**
 * Description: This is a reimplimentation for an old student project, "Mustick" in 2008 of TU/e.
 * Interaction: The IMU sensor data of Arduino Nano RP2040 Connect will be sent to this Python script,
 *              and the data will be transfer to an internal web server over port 12000. Then in 
 *              Processing, the data will change the speed of playing music or pause the playing if 
 *              the IMU side is not moving.
 *   Technique: I use BLE here, but the original prototype uses the xBee modules for data transmittion.
 *    Hardware: Arduino Nano RP2040 Connect
 *              Seeed Studio Lipo Rider Plus
 *              Lipo battery
 *              Raspberry Pi (I use RPi 4 here) with DAC shield
 *                - It's difficult for RPi OS to decode audio file with integrated audio chip, so, I add
 *                  an additional DAC shield for decoding audio signal, which can do the decoding task
 *                  smoothly.
 * Programming: Arduino IDE
 *              Python
 *              Processing (This file)
 *  Created by: I-Tang (Eden) Chiang @ Oct.14, 2026
 **/

import ddf.minim.*;
import ddf.minim.ugens.*; // UGens
import oscP5.*;
import netP5.*;

// Music play control
Minim minim;
AudioOutput out;
FilePlayer filePlayer;
TickRate rateControl;

boolean isPlaying = false;
boolean isMoving = false;
float accelData = 0.0;
float speed = 0.0;
float diff = 0.0;
float lastAccelData = 0.0;
int state = 0;
int consistantTime = 500;
long lastUpdateAtTime = 0;

// Data receiver
OscP5 oscP5;

void setup() {
  // Assign main music output in Raspberry Pi OS
  System.setProperty("javax.sound.sampled.Clip", "com.sun.media.sound.DirectAudioDeviceProvider");
  System.setProperty("javax.sound.sampled.SourceDataLine", "com.sun.media.sound.DirectAudioDeviceProvider");
  
  // Listen on port 12000 for Python's incoming network packets
  oscP5 = new OscP5(this, 12000);

  // canvas init
  size(200, 200);
  textSize(24);

  // music player setup
  minim = new Minim(this);
  out = minim.getLineOut();

  // load music file
  filePlayer = new FilePlayer(minim.loadFileStream("song.wav"));

  // init speed controller, 1.0f for general speed
  rateControl = new TickRate(speed);

  // speed control
  filePlayer.patch(rateControl).patch(out);

  // play and loop file
  filePlayer.loop();
}

void draw() {
  background(40);
  textAlign(CENTER, CENTER);
  String status = "STILL";  // state 0 as default
  long current = millis();

  if (lastAccelData == accelData && current - lastUpdateAtTime > consistantTime) {
    state = 0;
  }

  // debugging
  // println("state: " + state + "\tcurrent:" + current + "\tlast update: " + lastUpdateAtTime);

  switch(state) {
  case 1:
    // "MOVING" state
    status = "MOVING";
    fill(0, 255, 0);

    if (speed < 1) {
      speed += 0.1;
      if (speed > 1)  speed = 1;
    }

    // debugging
    //println("speed:" + speed);

    // update play speed
    lastAccelData = accelData;
    rateControl.value.setLastValue(speed);
    break;
  case 0:
  default:
    // "STILL" state
    fill(255, 0, 0);

    if (speed > 0.2)  speed -= 0.015;
    else  speed = 0;

    // debugging
    //println("speed:" + speed);

    // reset play speed as 0
    rateControl.value.setLastValue(speed);
    break;
  }

  text(status, width/2, height/2);
  
  // debugging
  // println(status);
}

int zeroCounter = 0;
long silentMillis = 0;

// Automatically triggers whenever Python sends new accelerometer data
void oscEvent(OscMessage theOscMessage) {
  float inFloat = 0.0;
  isMoving = true;
  lastUpdateAtTime = millis();

  try {
    // try to parse incoming data
    if (theOscMessage.checkAddrPattern("/accel")) {
      inFloat = theOscMessage.get(0).floatValue();
    }

    diff = abs(inFloat - accelData);
    accelData = inFloat;

    if (diff > 1) {
      if (accelData < 8) speed = map(accelData, 0.3, 8, 0.2, 1);
      else speed = 1;

      state = 1;
    } else {
      zeroCounter += 1;
      if (zeroCounter > 8) {

        // change state
        zeroCounter = 0;
        state = 0;
      }
    }
  } catch (Exception e) {
    e.printStackTrace();
  }

  println("serial event:" + accelData);
}
