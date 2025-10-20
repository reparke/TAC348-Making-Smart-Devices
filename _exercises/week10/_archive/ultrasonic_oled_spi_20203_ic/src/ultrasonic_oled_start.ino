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
const int PIN_ECHO = D2;     //Sensors sends to ARGON INPUT
const int PIN_TRIGGER = D3;  //ARGON OUTPUT sends to sensor

//global constant
double SPEED_SOUND_CM = 0.03444;  //temperature dependent
double CONV_CM_TO_IN = 0.3437;

int MAX_RANGE_CM = 78;  // 30 in
int MIN_RANGE_CM = 0;
int WARNING_RANGE_CM = 12;  //4.7

void setup() {
    Serial.begin(9600);  // begin serial communication with the computer
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory
    oled.display();      // Display what's in the buffer (splashscreen)
    delay(1000);         // Delay 1000 ms

    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

/********************************************************************************/
void loop() {
    //start measurement
    //send low for 2 us, high for 10 us, low (sequence)
    digitalWrite(PIN_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);
    //now sensor starts

    //measure time (measuring time it takes for pin to go High to Low)
    int roundTripTime = pulseIn(PIN_ECHO, HIGH);  //listen when pin is HIGH, stop listening when pin is low

    double distanceCm = roundTripTime * SPEED_SOUND_CM / 2;
    double distanceIn = distanceCm * CONV_CM_TO_IN;
    Serial.print("Dist to object: ");
    if (distanceCm >= MAX_RANGE_CM ||
        distanceCm <= MIN_RANGE_CM) {  // these units can be CM only because that
                                       // is what the sensor reports
        Serial.print("out of range " + String(distanceCm));
        oled.clear(PAGE);
        oled.drawBitmap(no_small_bmp);
        oled.setCursor(0, 40);  //far left, 40 rows down from top
        oled.setFontType(0);
        oled.print("out of range");
        oled.display();
    } else if (distanceCm > 0 && distanceCm < WARNING_RANGE_CM) {
        Serial.print("Warning " + String(distanceCm));
        oled.clear(PAGE);
        oled.drawBitmap(warning_small_bmp);
        oled.setCursor(0, 40);  //far left, 40 rows down from top
        oled.setFontType(0);
        oled.print(String(distanceCm,2) + " cm");
        oled.display();
    } else {
        Serial.print("OK distance" + String(distanceCm));
        oled.clear(PAGE);
        oled.drawBitmap(yes_small_bmp);
        oled.setCursor(0, 40);  //far left, 40 rows down from top
        oled.setFontType(0);
        oled.print(String(distanceCm,2) + " cm");
        oled.display();
    }

    Serial.println();

    delay(500);
}
