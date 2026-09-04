// Pin define, ENA should be connected to the 5V pin above!
const int IN1 = 5;
const int IN2 = 6;

// PWM 設定
const int freq = 20000;       // freqency: 20kHz, good for DC motor for reduce high requency noice
const int resolution = 8;     // 8 bits resolution of speed in range 0 - 255

const int channel1 = 0;       // PWM channel for IN1
const int channel2 = 1;       // PWM channel for IN2

void setup() {
  // attach IN1 and IN2 to different channels
  ledcAttachChannel(IN1, freq, resolution, channel1);
  ledcAttachChannel(IN2, freq, resolution, channel2);
}

void loop() {
  // 1. forward - slow (PWM 100)
  ledcWrite(IN1, 100);
  ledcWrite(IN2, 0);
  delay(3000);

  // 2. forward - full speed (PWM 255)
  ledcWrite(IN1, 255);
  ledcWrite(IN2, 0);
  delay(3000);

  // 3. stop
  ledcWrite(IN1, 0);
  ledcWrite(IN2, 0);
  delay(2000);

  // 4. backward - middle (PWM 160)
  ledcWrite(IN1, 0);
  ledcWrite(IN2, 160);
  delay(3000);

  // 5. stop
  ledcWrite(IN1, 0);
  ledcWrite(IN2, 0);
  delay(2000);
}
