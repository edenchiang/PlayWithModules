Notes for testing modules in different platforms.
<br>

## Modules with Arduino boards
[Arduino Uno with MFRC522 - RFID reader / writer module](https://github.com/miguelbalboa/rfid)

<br>

## General questions
### Q. Why does my button not work properly?
A. Few things to check:

1. [Official document](https://docs.arduino.cc/built-in-examples/digital/Button)
2. If you don't want to use the resistor between the button and Uno, some changes of the code is required:
	```java
	...

	void setup() {
		...
		pinMode(buttonPin, INPUT_PULLUP);
	}

	...
	```
3. The debouncing ([What is debouncing?](https://www.techtarget.com/whatis/definition/debouncing#:~:text=Debouncing%20is%20removing%20unwanted%20input,hardware%20switches%2C%20programs%20and%20websites.)) with the resistor is required for making the button work properly because it can provide stable voltage status as the button is pressing. Otherwise the signal (voltage) will be in floating status and you will never know whether the button is pressed or not by the signal.


