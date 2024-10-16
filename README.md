# What's happening here?

It's a place for notes of testing modules in different platforms.

<br />

## Modules

- [MFRC522 RFID reader / writer module --- with Arduino Uno](RFID-reader_MFRC522)

- [Thermal printer EM5820 --- with Arduino Uno / ESP32](thermal-printer_EM5820)

<br />

## General questions

### Q. Why does my button not work properly?

A. Few things to check:

1. [Official document](https://docs.arduino.cc/built-in-examples/digital/Button)
2. If you don't want to add the resistor between the button and Uno, some changes of the code in `setup()` is required:
	```java
	...

	void setup() {
		...
		pinMode(buttonPin, INPUT_PULLUP);
	}

	...
	```

3. The debouncing ([What is debouncing?](https://www.techtarget.com/whatis/definition/debouncing#:~:text=Debouncing%20is%20removing%20unwanted%20input,hardware%20switches%2C%20programs%20and%20websites.)) with the resistor is necessary for removing unwanted input noise from buttons, switches and other inputs. Otherwise the signal (voltage) will be unstable and you will never know whether the button is pressed or not by the signal.
