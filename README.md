# What's happening here?

It's a place for notes of testing modules in different platforms.

<br />

## Modules

- [MFRC522 RFID reader / writer module --- with Arduino Uno](/RFID-reader_MFRC522)
- [Thermal printer EM5820 --- with Arduino Uno / ESP32](/thermal-printer_EM5820)
- [Raspberry Pi RP2040 with ESP-12 chip](/RPi-Pico_with_ESP-12S/)
- [Turn Arduino Nano ESP32 into a pyboard of CircuitPython](/Nano-ESP32_in_CircuitPython/)

<br />

## Something going wrong?

### General questions

#### Q. Why does my button not work properly?

A. Few things to check:

1. [Official document](https://docs.arduino.cc/built-in-examples/digital/Button)
2. If you don't want to add the resistor between the button and Uno GND pin, some changes of the code in `setup()` is required:

```java
void setup() {
	...
	pinMode(buttonPin, INPUT_PULLUP);
}
```

3. The debouncing ([What is debouncing?](https://www.techtarget.com/whatis/definition/debouncing#:~:text=Debouncing%20is%20removing%20unwanted%20input,hardware%20switches%2C%20programs%20and%20websites.)) with the resistor is necessary for removing unwanted input noise from buttons, switches and other inputs. Otherwise the signal (voltage) will be unstable and you will never know whether the button is pressed or not by the signal.

<br />

### ESP32 platform

#### Q. My sensors don't work on ESP32 as ESP32 is connected to the Internet, or vise versa! But they work fine separately, why?

A. Check the following articles for pinout and the limitation of using the network feature to make sure your wiring is correct:

- [Analog to Digital Converter](https://docs.espressif.com/projects/esp-idf/en/v4.2/esp32/api-reference/peripherals/adc.html#overview)
- [Pinout reference](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)
- Use the correct library and credential for Wi-Fi connection
