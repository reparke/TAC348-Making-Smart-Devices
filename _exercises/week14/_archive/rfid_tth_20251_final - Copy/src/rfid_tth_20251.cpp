#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#include "MFRC522.h"

#define SS_PIN A0   // SDA on RFID sensor
#define RST_PIN A1  // RST on RFID sensor

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

String card1 = "0E 8B 8E 6A";
String card2 = "4E B3 01 BF";

void setup() {
    Serial.begin(9600);  // Initialize serial communications with the PC
    mfrc522.setSPIConfig();

    mfrc522.PCD_Init();  // Init MFRC522 card
    Serial.println("Scan PICC to see UID and type...");
}

/*
    scan a card, and print a message saying either card1 or card2 was scanned or
   unknown
*/

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

    String scannedCard = ""; 
    if (mfrc522.PICC_IsNewCardPresent()) {
        if (mfrc522.PICC_ReadCardSerial()) {
            for (byte i = 0; i < mfrc522.uid.size; i++) {
                // Serial.print(uid->uidByte[i] < 0x10 ? " 0" : " ");
                // Serial.print(uid->uidByte[i], HEX);
                scannedCard += String (mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                scannedCard += String (mfrc522.uid.uidByte[i], HEX);
            }
            scannedCard.toUpperCase();
            scannedCard.trim();
            // Serial.println("Scanned card: " + scannedCard);
            if (scannedCard == card1) {
                Serial.println("Found card 1! _" + card1);
            }
            else if (scannedCard == card2) {
                Serial.println("Found card2! _" + card2);
            }
            else {
                Serial.println("Unknown card _" + scannedCard + "_");
            }
        }
    }
}
