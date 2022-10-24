/*  Wiring

  OLED
  ----
    MicroOLED ------------- Argon
    GND ------------------- GND
    3.3 ------------------- 3.3V (VCC)
    D1/MOSI ----------------- MO (don't change)
    D0/SCK ------------------ SCK (don't change)
    D2  ------------------- unused
    D/C ------------------- A0 (can be any digital pin)
                RST ------------------- A1 (can be any digital pin)
                CS  ------------------- A2 (can be any digital pin)

Ultrasonic Sensor
  Trigger: D3;
  Echo: D2;

*/
#include "SparkFunMicroOLED.h"  // Include MicroOLED library
#include "bitmaps_symbols.h"

//////////////////////////
// MicroOLED Definition //
//////////////////////////
#define PIN_OLED_RST A1  // Connect RST to pin 6
#define PIN_OLED_DC A0   // Connect DC to pin 5 (required for SPI)
#define PIN_OLED_CS A2   // Connect CS to pin A2 (required for SPI)
MicroOLED oled(MODE_SPI, PIN_OLED_RST, PIN_OLED_DC, PIN_OLED_CS);

double SPEED_SOUND_CM_ROOM_TEMP_FAHR = 0.03444;
double CONV_FACTOR_CM_TO_IN = 0.3437;
int MAX_RANGE_CM = 78;  // 30 in
int MIN_RANGE_CM = 0;
int WARNING_RANGE_CM = 12;  //4.7

const int PIN_ECHO = D2;
const int PIN_TRIGGER = D3;

// bool unitInCm = true;  // true is CM, false is IN
double distanceCm;
double distanceIn;

void setup() {
  Serial.begin(9600);  // begin serial communication with the computer
  oled.begin();        // Initialize the OLED
  oled.clear(ALL);     // Clear the display's internal memory
  oled.drawBitmap(trojan_bmp);
  oled.display();      // Display what's in the buffer (splashscreen)
  delay(1000);         // Delay 1000 ms

  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

/********************************************************************************/
void loop() {
  measureDistance();

  updateOLED();

  delay(500);  // need to pause in order to get next valid reading from sensor
}

void measureDistance() {
  // start trigger
  digitalWrite(PIN_TRIGGER, LOW);  // prepare
  delayMicroseconds(2);
  digitalWrite(PIN_TRIGGER, HIGH);  // prepare
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);  // prepare

  int timeRoundTrip = pulseIn(PIN_ECHO, HIGH);  // wait for round trip time
  distanceCm = timeRoundTrip * SPEED_SOUND_CM_ROOM_TEMP_FAHR / 2;
  distanceIn = distanceCm * CONV_FACTOR_CM_TO_IN;
}

void updateOLED() {
  Serial.print("Dist to object:");
  if (distanceCm >= MAX_RANGE_CM ||
      distanceCm <= MIN_RANGE_CM) {  // these units can be CM only because that
                                     // is what the sensor reports

    Serial.print("out of range");
    oled.clear(PAGE);      // Clear the display
    oled.drawBitmap(no_bmp);
    // oled.setFontType(0);   // Switch to the large-number font
    // oled.setCursor(40, 0);  // Set the cursor to top-left
    // oled.print("Out of range");
    oled.display();  // Update the display
  } 
  else if (distanceCm > 0 && distanceCm < WARNING_RANGE_CM) {
    Serial.print("Warning");
    oled.clear(PAGE);      // Clear the display
    oled.drawBitmap(warning_bmp_320x240);
    oled.setFontType(0);   // Switch to the large-number font
    oled.setCursor(0, 40);  // Set the cursor to top-left
    oled.print(String(distanceIn, 2) + " in");
    oled.display();  // Update the display
  }
    else {
    Serial.print("OK distance");
    oled.clear(PAGE);      // Clear the display
    oled.drawBitmap(yes_bmp_320x240);
    oled.setFontType(0);   // Switch to the large-number font
    oled.setCursor(0, 40);  // Set the cursor to top-left
    oled.print(String(distanceIn, 2) + " in");
    oled.display();  // Update the display
  }

  Serial.println();

  // debug
  /*
  Serial.print("Round trip time: ");
  Serial.println(timeRoundTrip);
  Serial.print("Distance in cm: ");
  Serial.println(distanceCm);
  */
}
