#include "particle_ble_setup.h"
// doesn't include servo

/*
  Use Adafruit Bluefruit app
  (https://learn.adafruit.com/bluefruit-le-connect/controller)
  Connect to Argon -> controller

  - use color picker to change LED
  - use controller to play a tone and flash on-board LED

  CONFIGURATION
  RGB LED (common cathode) connected to Argon
    R - A2
    G - A1
    B - A0

  Buzzer - D6

  On-board LED - D7
*/

const int PIN_RED = A2;
const int PIN_GREEN = A1;
const int PIN_BLUE = A0;

const int PIN_BUZZER = D6;

const int PIN_LED = D7;

void setup() {
  /* === START BLE SETUP === */
  particle_ble_setup();
  /* === END BLE SETUP === */

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_RED, OUTPUT);
  Serial.begin(9600);
}

void loop() {}

// onDataReceived() is event handler for incoming data via RX characteristic
// When the RXCharacteristic receives data, the event handler is called

/*  Sample Code to communicate from Argon to Adafruit Bluefruit app
  When "1" is pressed down on Bluefruit app, on-board LED D7 will blink twice
  When "UP" is pressed down on Bluefruit app, on-board LED D7 will turn on
  When "UP" is released on Bluefruit app, on-board LED D7 will turn off
  When "RIGHT" is pressed on Bluefruit app, play a tone

  When color picker is used, change RGB LED color

  The command scheme is from the Adafruit Bluefruit app
    ex: [‘!’] [‘B’] [‘4’] [‘1’] [CRC]
    https://learn.adafruit.com/bluefruit-le-connect/controller
*/

// Note: uint8_t is a byte ("unsigned integer of length 8 bits")
void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer,
                    void* context) {
  /* === START DEBUG PRINTING ===
           uncomment following loop to see commands being sent by app ==
   */
  for (size_t ii = 0; ii < len; ii++) {
    Serial.print(data[ii]);
    Serial.print(" ");
  }
  Serial.println();
  for (size_t ii = 0; ii < len; ii++) {
    Serial.write(data[ii]);
    Serial.print(" ");
  }
  Serial.println();
  /* === END DEBUG PRINTING === */

  if (len > 4) {  // make sure there at least four bytes
    if (data[0] == '!' && data[1] == 'B' && data[2] == '1' &&
        data[3] == '1') {  // button 1 pressed -> blink
      digitalWrite(PIN_LED, HIGH);
      delay(200);
      digitalWrite(PIN_LED, LOW);
      delay(200);
    } else if (data[0] == '!' && data[1] == 'B' && data[2] == '5' &&
               data[3] == '1') {  // button UP pressed -> LED on
      digitalWrite(PIN_LED, HIGH);
    } else if (data[0] == '!' && data[1] == 'B' && data[2] == '5' &&
               data[3] == '0') {  // button UP released -> LED off
      digitalWrite(PIN_LED, LOW);
    }
    // added to send a tone to D6 when right arrow is pressed
    else if (data[0] == '!' && data[1] == 'B' && data[2] == '8' &&
             data[3] == '0') {  // button UP released -> LED off
      tone(PIN_BUZZER, 1000, 500);
    } else if (data[0] == '!' && data[1] == 'C') {
      Serial.print("R as uint ");
      Serial.println(data[2]);

      changeRgbLight(data[2], data[3], data[4]);
    }
  }
}
// void changeRgbLight(uint8_t r, uint8_t g, uint8_t b) {
void changeRgbLight(int r, int g, int b) {
  analogWrite(PIN_RED, r);
  analogWrite(PIN_GREEN, g);
  analogWrite(PIN_BLUE, b);
}
