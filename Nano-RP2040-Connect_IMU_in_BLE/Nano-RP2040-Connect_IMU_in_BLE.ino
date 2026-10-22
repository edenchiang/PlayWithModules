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
 *              Raspberry Pi (I use RPi 4 here) with audio shield
 *                - It's difficult for RPi OS to decode audio file with integrated audio chip, so, I add
 *                  an additional DAC shield for decoding audio signal, which can do the decoding task
 *                  smoothly.
 *     Code in: Arduino IDE (This file)
 *              Python
 *              Processing
 *  Created by: I-Tang (Eden) Chiang @ Oct.14, 2026
 **/

#include <Arduino_LSM6DSOX.h>
#include <ArduinoBLE.h>
#include <floatToString.h>
#include "secrets.h"

// Define BLE service with the credentials in "secrets.h"
BLEService uartService(SERVICE_UUID);
BLEStringCharacteristic txCharacteristic(CHARACTERISTIC_UUID, BLENotify, 20);

unsigned long previousMillis = 0;
const long interval = 200;  // transfer per 200 ms

void setup() {
  Serial.begin(115200);

  // 1. IMU initialization
  if (!IMU.begin()) {
    Serial.println("Fail to initialize LSM6DSOX sensor.");
    while (1)
      ;
  }

  // 2. BLE initialization
  if (!BLE.begin()) {
    Serial.println("Fail to initialize BLE module");
    while (1)
      ;
  }

  // Setup for BLE service and name 
  BLE.setLocalName(TARGET_NAME);
  BLE.setAdvertisedService(uartService);
  uartService.addCharacteristic(txCharacteristic);
  BLE.addService(uartService);

  // start advertising and waiting for getting connected
  BLE.advertise();
  Serial.println("BLE ready, waiting for getting connected...");
}

int stillCounter = 0;
void loop() {
  // Read IMU sensor
  if (IMU.accelerationAvailable()) {
    BLEDevice central = BLE.central();
    float x, y, z;
    IMU.readAcceleration(x, y, z);

    if (central && central.connected()) {
      // cauculate strangth of movement, and minus 1 for gravity on z-axis
      float motionIntensity = abs(x) + abs(y) + abs(abs(z) - 1.0);
      String status = "0";

      if (motionIntensity > 0.6) {
        // debugging
        // Serial.print("status: ");

        Serial.println(status);
        status = String(motionIntensity, 4);

        // transfer data via BLE
        txCharacteristic.writeValue(status);
      } else {
        if (stillCounter < 10) stillCounter += 1;
        else {
          stillCounter = 0;
          // Serial.print("status: ");
          Serial.println(status);
          motionIntensity = 0;
          status = String(motionIntensity, 4);
          txCharacteristic.writeValue(status);
        }
      }
      delay(30);
    }
  }
}
