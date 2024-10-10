/**
Example for connecing multiple RC522 modules to Arduino Uno, in this case, there are three RC522 modules connected to Arduino Uno.
Modified from: Example code of RC522 module - ReadUidMultiReader
Modified by: Eden Chiang (i.chiang@tue.nl)
*/

#include <SPI.h>
#include <MFRC522.h>

/**
   Global settings
*/
//////// pins and wirings
// Not connected to modules, only configured
#define RST_PIN         3          
// connect to SDA of the modules
#define SS_PIN_1        10
#define SS_PIN_2        9
#define SS_PIN_3        8
//  pin   connect_to
//  11    MOSI
//  12    MISO
//  13    SCK

// SDA pin array
byte ssPins[] = {SS_PIN_1, SS_PIN_2, SS_PIN_3};

// total amount of modules
#define NR_OF_READERS   3

//////// initialization
// reader module instances
MFRC522 mfrc522[NR_OF_READERS];

/**
   Initialize.
*/
void setup() {
  // Initialize serial communications with the PC
  Serial.begin(9600); 
  // while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  // Init SPI bus
  SPI.begin();        

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}

/**
   Main loop.
*/
void loop() {

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Look for new cards

    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      Serial.print(F("Reader "));
      Serial.print(reader);
      // Show some details of the PICC (that is: the tag/card)
      Serial.print(F(": Card UID:"));
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      Serial.println();
      Serial.print(F("PICC type: "));
      MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
      Serial.println(mfrc522[reader].PICC_GetTypeName(piccType));

      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader
}

/**
   Helper routine to dump a byte array as hex values to Serial.
*/
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
