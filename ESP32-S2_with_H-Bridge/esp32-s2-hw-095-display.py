import time
from machine import Pin, PWM, I2C
import ssd1306


# ==================== 1. Initialize OLED display ====================
# 【IMPORTANT!!】Espacially for Wemos S2 Pico: Reset pin of OLED have to be pulled to HIGH to start!
# 1. Forcely reset display
oled_rst = Pin(18, Pin.OUT, value=1)
time.sleep_ms(50)
oled_rst.value(0)  # pull down
time.sleep_ms(50)
oled_rst.value(1)  # set HIGH to start display
time.sleep_ms(100) # starting LED takes some time

# 2. Initicalize I2C (display pins of Wemos S2 Pico: SDA=8, SCL=9)
i2c = I2C(0, sda=Pin(8), scl=Pin(9), freq=400000)

# 3. Initicalize 128x32 OLED display
try:
    oled = ssd1306.SSD1306_I2C(128, 32, i2c)
    oled.fill(0)
    oled.text("System Ready!", 0, 0)
    oled.show()
    print("OLED display initialization done!")
except Exception as e:
    print("OLED fail to start:", e)


# ==================== 2. Initialize motor PWM ====================
in1 = PWM(Pin(4), freq=20000, duty=0)
in2 = PWM(Pin(5), freq=20000, duty=0)

# ==================== 3. Functions for display and control ====================
def update_display(direction, speed_pct):
    """update OLED display to show speed and status"""
    oled.fill(0) # clean display
    oled.text("Motor Status:", 0, 0)
    oled.text(f"DIR  : {direction}", 0, 12)
    oled.text(f"SPEED: {speed_pct}%", 0, 24)
    oled.show()

def motor_forward(speed):
    """forward, speed from 0 ~ 1023"""
    in1.duty(speed)
    in2.duty(0)
    # ratio of speed: (speed / 1023 * 100)
    pct = int((speed / 1023) * 100)
    update_display("FORWARD", pct)

def motor_backward(speed):
    """backward, speed from 0 ~ 1023"""
    in1.duty(0)
    in2.duty(speed)
    pct = int((speed / 1023) * 100)
    update_display("BACKWARD", pct)

def motor_stop():
    """stop"""
    in1.duty(0)
    in2.duty(0)
    update_display("STOPPED", 0)

# ==================== 4. main loop ====================
try:
    while True:
        # 1. forward - slow
        motor_forward(400)
        time.sleep(3)

        # 2. forward - full speed
        motor_forward(1023)
        time.sleep(3)

        # 3. stop
        motor_stop()
        time.sleep(2)

        # 4. backward - middle
        motor_backward(700)
        time.sleep(3)

        # 5. stop
        motor_stop()
        time.sleep(2)

except KeyboardInterrupt:
    print("program stop, shut down motor and display")
    motor_stop()
    oled.fill(0)
    oled.show()
