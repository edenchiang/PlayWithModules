// 定義腳位（此時 ENA 請插著黑色跳帽，不要接線）
const int IN1 = 5;  // 控制方向與速度 1
const int IN2 = 6;  // 控制方向與速度 2

// PWM 設定
const int freq = 20000;       // 頻率 20kHz（適合直流馬達，比較不會有高頻噪音）
const int resolution = 8;     // 8 位元解析度（速度範圍 0 - 255）

const int channel1 = 0;       // IN1 使用的 PWM 頻道
const int channel2 = 1;       // IN2 使用的 PWM 頻道

void setup() {
  // 【新版語法】將 IN1 和 IN2 分別綁定不同的 PWM 頻道
  ledcAttachChannel(IN1, freq, resolution, channel1);
  ledcAttachChannel(IN2, freq, resolution, channel2);
}

void loop() {
  // 1. 正轉 - 慢速 (PWM 100)
  ledcWrite(IN1, 100); 
  ledcWrite(IN2, 0); 
  delay(3000);

  // 2. 正轉 - 全速 (PWM 255)
  ledcWrite(IN1, 255); 
  ledcWrite(IN2, 0); 
  delay(3000);

  // 3. 停止
  ledcWrite(IN1, 0);   
  ledcWrite(IN2, 0);   
  delay(2000);

  // 4. 反轉 - 中速 (PWM 160)
  ledcWrite(IN1, 0);   
  ledcWrite(IN2, 160); 
  delay(3000);

  // 5. 停止
  ledcWrite(IN1, 0);   
  ledcWrite(IN2, 0);   
  delay(2000);
}
