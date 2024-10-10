
#include "Adafruit_Thermal.h"

#define TX_PIN1 17 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN1 16 // Arduino receive   GREEN WIRE   labeled TX on printer

// HardwareSerial mySerial(2);
Adafruit_Thermal printer(&Serial2); 

// =======================================================================

#include "OOCSI.h"

// use this if you want the OOCSI-ESP library to manage the connection to the Wifi
// SSID of your Wifi network, the library currently does not support WPA2 Enterprise networks
const char* ssid = "SSID_NAME";
// Password of your Wifi network.
const char* password = "PASSWORD-OF-SSID";

// name for connecting with OOCSI (unique handle)
const char* OOCSIName = "ESP_OOCSI_CLIENT_RECEIVER_####";
// put the adress of your OOCSI server here, can be URL or IP address string
const char* hostserver = "OOCSI_SERVER";

// OOCSI reference for the entire sketch
OOCSI oocsi = OOCSI();

// =======================================================================

void setup() {
  // init ESP32 serial ports and printer
  // be aware the baudrate of your serial monitor, it should be the same
  // as you set here
  // start serial monitor and wait for input
  Serial.begin(115200);

  // Initialize HardwareSerial 2 of ESP32 for printer
  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page 
  //       with long press of the button on your printer.
  Serial2.begin(9600, SERIAL_8N1, RX_PIN1, TX_PIN1);  

  printer.begin();        // init printer

  // init oocsi
  oocsi.connect(OOCSIName, hostserver, ssid, password, processOOCSI);

  // subscribe to a channel
  Serial.println("subscribing to esp-testchannel");
  oocsi.subscribe("esp-testchannel");
}

void loop() {
  // put your main code here, to run repeatedly:
  // ...

  // let OOCSI check for incoming data
  // use keepAlive() if you do NOT need to receive data
  oocsi.check();
  delay(500);
}

void processOOCSI() {
  // oocsi.printMessage();

  // if something input from esp-testchannel on OOCSI
  String text = oocsi.getString("text", "");
  String sender = oocsi.getString("sender", "");
  int num = oocsi.getInt("number", -1);
  bool truth = oocsi.getBool("boolean", false);

  // do the print
  printer.setFont('A');
  printer.println("input from serial:");
  printer.print("text:");
  printer.println(text);
  printer.print("sender:");
  printer.println(sender);
  printer.print("number:");
  printer.println(num);
  printer.print("truth:");
  printer.println(truth);
  printer.print("timestamp:");
  printer.println(oocsi.getTimeStamp());
  // printer.feed(2);
  printer.feed(1);
  printer.sleep();
  delay(3000);
  printer.wake();
  printer.setDefault();

  // respond to serial monitor
  Serial.println("data from esp-testchannel has been printed!\n=================");
}
 

