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
#include "bitmaps.h"

double SPEED_SOUND_CM_ROOM_TEMP_FAHR = 0.03444;
int MAX_RANGE_CM = 78;
int MIN_RANGE_CM = 0;


double distanceCm;
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
  oled.drawBitmap(trojan);
  oled.display();      // Display what's in the buffer (splashscreen)
  delay(1000);         // Delay 1000 ms
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

/********************************************************************************/
void loop() {
    // start trigger
    digitalWrite(PIN_TRIGGER, LOW);  // prepare
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);  // prepare
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);  // prepare

    int timeRoundTrip = pulseIn(PIN_ECHO, HIGH);  // wait for round trip time
    distanceCm = timeRoundTrip * SPEED_SOUND_CM_ROOM_TEMP_FAHR / 2;

    Serial.print("Dist to object:");
    if (distanceCm >= MAX_RANGE_CM ||
        distanceCm <= MIN_RANGE_CM) {  // these units can be CM only because
                                       // that is what the sensor reports

        Serial.print("out of range");
    } else {
        Serial.print(distanceCm);
        Serial.print(" cm");
    }
    Serial.println();


    delay(500);
}
