#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/* LAB

  press button, led shows white
  press button again, led show orange
  press again, led turn off

  repeat

  hints: remember a latch can track individual presses
                  orange requires different amounts of red green blue

  */

const int PIN_BUTTON = D5;
const int PIN_RED = SCL;
const int PIN_GREEN = MISO;  // says "MI"
const int PIN_BLUE = MOSI;   // says "MOSI"

int prevButtonVal = HIGH;  // "default" not pressed
int ledState = 0;  // cycle between white, orange, off (or mod with counter)

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // build latch
    int currButtonVal = digitalRead(PIN_BUTTON);
    if (prevButtonVal == HIGH && currButtonVal == LOW) {
        // here is what we want to happen on press
        if (ledState == 0) {  // white
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_GREEN, HIGH);
            digitalWrite(PIN_BLUE, HIGH);
        } else if (ledState == 1) {
            // orange -- to diplay, we need analoswrite
            // r 255, green 98, blue 0
            analogWrite(PIN_RED, 255);  // same as digitalWrite HIGH
            analogWrite(PIN_GREEN, 98);
            analogWrite(PIN_BLUE, 0);
        } else {                      // off
            analogWrite(PIN_RED, 0);  // same as digitalWrite HIGH
            analogWrite(PIN_GREEN, 0);
            analogWrite(PIN_BLUE, 0);
        }
        ledState = ledState + 1;
        // reset our counter --> use IF or modulus
        if (ledState >= 3) {
            ledState = 0;
        }
    }
    // make sure to have update
    prevButtonVal = currButtonVal;
}

// void loop() {
//     // build latch
//     int currButtonVal = digitalRead(PIN_BUTTON);
//     if (prevButtonVal == HIGH && currButtonVal == LOW) {
      
//         //code you want to happen on a SINGLE press 

//     }
//     // make sure to have update
//     prevButtonVal = currButtonVal;
// }
