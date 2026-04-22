
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
 * MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W
 AND R BY COOQROBOT.
 * The library file MFRC522.h has a wealth of useful info. Please read it.
 * The functions are documented in MFRC522.cpp.
 *
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Created by Miguel Balboa (circuitito.com), Jan, 2012.
 * Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013
 (Translation to English, refactored, comments, anti collision, cascade levels.)
 * Released into the public domain.
 *
 * Sample program showing how to read data from a PICC using a MFRC522 reader on
 the Arduino SPI interface.
 *-----------------------------------------------------------------------------
 empty_skull
 * Aggiunti pin per arduino Mega
 * add pin configuration for arduino mega
 * http://mac86project.altervista.org/
 -----------------------------------------------------------------------------
 Nicola Coppola
 * Pin layout should be as follows:
 * Signal     Pin              Pin               Pin			Pin
 *            Arduino Uno      Arduino Mega      SPARK			MFRC522
 board
 * ---------------------------------------------------------------------------
 * Reset      9                5                 ANY (D2)		RST
 * SPI SS     10               53                ANY (A2)		SDA
 * SPI MOSI   11               51                A5
 MOSI
 * SPI MISO   12               50                A4
 MISO
 * SPI SCK    13               52                A3 SCK
 *
 * The reader can be found on eBay for around 5 dollars. Search for "mf-rc522"
 on ebay.com.
 */

// #include <SPI.h>
#include "MFRC522.h"

// #define SS_PIN SS
// #define RST_PIN D2
#define SS_PIN A0
#define RST_PIN A1

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

/*
    The RFID cards have an UUID and they have some storage (not much)

    how to use
    - just use the UUID
        code handles storing info and data access
    -store data on the card itself (1 KB)

    ex: hotel - check out is 11 am --> ask for a late checkout 2pm
        next day at 1 pm: you can't access your room

    how does a hotel room access panel know when you are supposed to checkout?
      possibilities
        1. the reader gets real-time data and is networked to the hotel system
            your card UUID is linked your account which knows when you will
   checkout
        2. checkout time is stored on the card itself

        why 1) network?
            -can we reuse
            -much more flexiblity - advanced
        why 2) on card
            -easier
            -less battery replacement
            -reliable

*/

const String CARD1 = "4E B3 01 BF";
const String CARD2 = "57 67 BA 60";

void setup() {
    Serial.begin(9600);  // Initialize serial communications with the PC
    mfrc522.setSPIConfig();

    mfrc522.PCD_Init();  // Init MFRC522 card
    Serial.println("Scan PICC to see UID and type...");
}

void loop() {
    // // Look for new cards
    // if (!mfrc522.PICC_IsNewCardPresent()) {
    //     return;
    // }

    // // Select one of the cards
    // if (!mfrc522.PICC_ReadCardSerial()) {
    //     return;
    // }

    // // Dump debug info about the card. PICC_HaltA() is automatically called.
    // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

    /*
    following the example here
    -if card is present
    -if we can read the serial
        -use a for loop to access the UID from the card
        -STORE IT in variable
    -compare scanned card with our stored cards
    */

    String scannedCard = "";  // new card we are scanning
    if (mfrc522.PICC_IsNewCardPresent() == true) {
        if (mfrc522.PICC_ReadCardSerial() == true) {
            // figure out how to get the UID into a var
            for (byte i = 0; i < mfrc522.uid.size; i++) {
                scannedCard += String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                scannedCard += String(mfrc522.uid.uidByte[i], HEX);
            }
        }
        scannedCard.toUpperCase();
        scannedCard.trim()

        // Serial.println("Scanned Card:" + scannedCard);
        if(scannedCard == CARD1) {
            Serial.println("Found card 1");
        }
        else if (scannedCard == CARD2) {
            Serial.println("Found card 2");
        }
    }
}
