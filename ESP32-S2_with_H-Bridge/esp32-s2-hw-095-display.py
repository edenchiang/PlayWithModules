import time
from machine import Pin, PWM, I2C
import ssd1306

# ==================== 1. 初始化內建 OLED 螢幕 ====================
# 【重要】Wemos S2 Pico 特有步驟：必須先將 OLED 的 Reset 腳位拉高才能通電！
import time
from machine import Pin, I2C
import ssd1306

# 1. 強制執行硬體 Reset 觸發順序（非常重要！）
oled_rst = Pin(18, Pin.OUT, value=1)
time.sleep_ms(50)
oled_rst.value(0)  # 先拉低複位訊號
time.sleep_ms(50)
oled_rst.value(1)  # 再拉高釋放複位，讓 OLED 晶片真正開機
time.sleep_ms(100) # 給螢幕一點啟動時間

# 2. 初始化 I2C (Wemos S2 Pico 預設內建螢幕腳位 SDA=8, SCL=9)
i2c = I2C(0, sda=Pin(8), scl=Pin(9), freq=400000)

# 3. 初始化 128x32 OLED 螢幕
try:
    oled = ssd1306.SSD1306_I2C(128, 32, i2c)
    oled.fill(0)
    oled.text("System Ready!", 0, 0)
    oled.show()
    print("OLED 螢幕初始化成功！")
except Exception as e:
    print("OLED 初始化失敗：", e)


# ==================== 2. 初始化馬達 PWM ====================
in1 = PWM(Pin(4), freq=20000, duty=0)
in2 = PWM(Pin(5), freq=20000, duty=0)

# ==================== 3. 顯示與控制函數 ====================
def update_display(direction, speed_pct):
    """更新 OLED 畫面，顯示方向與速度百分比"""
    oled.fill(0) # 清除畫面
    oled.text("Motor Status:", 0, 0)
    oled.text(f"DIR  : {direction}", 0, 12)
    oled.text(f"SPEED: {speed_pct}%", 0, 24)
    oled.show()

def motor_forward(speed):
    """正轉，speed 範圍 0 ~ 1023"""
    in1.duty(speed)
    in2.duty(0)
    # 計算百分比 (speed / 1023 * 100)
    pct = int((speed / 1023) * 100)
    update_display("FORWARD", pct)

def motor_backward(speed):
    """反轉，speed 範圍 0 ~ 1023"""
    in1.duty(0)
    in2.duty(speed)
    pct = int((speed / 1023) * 100)
    update_display("BACKWARD", pct)

def motor_stop():
    """停止"""
    in1.duty(0)
    in2.duty(0)
    update_display("STOPPED", 0)

# ==================== 4. 主程式循環 ====================
try:
    while True:
        # 1. 正轉 - 慢速
        motor_forward(400)
        time.sleep(3)

        # 2. 正轉 - 全速
        motor_forward(1023)
        time.sleep(3)

        # 3. 停止
        motor_stop()
        time.sleep(2)

        # 4. 反轉 - 中速
        motor_backward(700)
        time.sleep(3)

        # 5. 停止
        motor_stop()
        time.sleep(2)

except KeyboardInterrupt:
    print("程式停止，關閉馬達與螢幕")
    motor_stop()
    oled.fill(0)
    oled.show()
