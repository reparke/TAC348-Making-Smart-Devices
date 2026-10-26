/*  Wiring

  OLED
  ----
    MicroOLED ------------- Argon
    GND ------------------- GND
    3.3 ------------------- 3.3V (VCC)
    D1/MOSI --------------- MO (don't change)
    D0/SCK ---------------- SCK (don't change)
    D2  ------------------- unused
    D/C ------------------- A0 (can be any digital pin)
    RST ------------------- A1 (can be any digital pin)
    CS  ------------------- A2 (can be any digital pin)

Ultrasonic Sensor
    Trigger: D3
    Echo: D2

*/
#include "SparkFunMicroOLED.h"  // Include MicroOLED library

//////////////////////////
// MicroOLED Definition //
//////////////////////////
#define PIN_OLED_RST A1  // Connect RST to pin 6
#define PIN_OLED_DC A0   // Connect DC to pin 5 (required for SPI)
#define PIN_OLED_CS A2   // Connect CS to pin A2 (required for SPI)
MicroOLED oled(MODE_SPI, PIN_OLED_RST, PIN_OLED_DC, PIN_OLED_CS);

//////////////////////////
// Ultrasonic Distance  //
//////////////////////////
const int PIN_ECHO = D2;
const int PIN_TRIGGER = D3;

void setup() {
    Serial.begin(9600);  // begin serial communication with the computer
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory
    oled.display();      // Display what's in the buffer (splashscreen)
    delay(1000);         // Delay 1000 ms
}

/********************************************************************************/
void loop() {}
