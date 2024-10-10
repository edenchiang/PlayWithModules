/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates a few text styles & layouts, bitmap printing, etc.

  IMPORTANT: DECLARATIONS DIFFER FROM PRIOR VERSIONS OF THIS LIBRARY.
  This is to support newer & more board types, especially ones that don't
  support SoftwareSerial (e.g. Arduino Due).  You can pass any Stream
  (e.g. Serial1) to the printer constructor.  See notes below.
  ------------------------------------------------------------------------*/

#include "Adafruit_Thermal.h"

// Here's the new syntax when using SoftwareSerial (e.g. Arduino Uno) ----
// If using hardware serial instead, comment out or remove these lines:

#include "SoftwareSerial.h"
#define TX_PIN1 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN1 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN1, TX_PIN1);
Adafruit_Thermal printer(&mySerial); 
// Then see setup() function regarding serial & printer begin() calls.

// Here's the syntax for hardware serial (e.g. Arduino Due) --------------
// Un-comment the following line if using hardware serial:

//Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.

// -----------------------------------------------------------------------

void setup() {
  // be aware the baudrate of your serial monitor, it should be the same
  // as you set here
  // start serial monitor and wait for input
  Serial.begin(9600);

  // Initialize SoftwareSerial for printer 1
  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page 
  //       with long press of the button on your printer.
  mySerial.begin(9600);  

  printer.begin();        // Init printer 1
}

void loop() {
  if (Serial.available() > 0) {
    // if something input from serial monitor
    String data = Serial.readString();
    String dataToTrim = data;
    // prevent from empty string
    dataToTrim.trim();

    if (dataToTrim.length() > 0) {
      // do the print
      printer.setFont('A');
      printer.println("input from serial:");
      printer.println(data);
      // printer.feed();
      printer.feed(1);
      printer.sleep();
      delay(3000);
      printer.wake();
      printer.setDefault();

      // respond to serial monitor
      Serial.println(data);
      Serial.println("input printed!\n=================");
    }
  }

  delay(10);
}
 

