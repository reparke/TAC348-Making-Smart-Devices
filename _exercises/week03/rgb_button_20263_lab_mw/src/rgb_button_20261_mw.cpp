#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);
/*
  press button, show white
  press button again, show orange
  press button 3rd time, show random color

  each time button is pressed, show a counter

  hint: random(0, 10) --> gives random number from 0 to 9

  hint: some colors like orange requires different amounts of red, green, blue

*/

const int PIN_BUTTON = D5;
const int PIN_RED = SCL;     // same as D1
const int PIN_GREEN = MISO;  // on board it says "MI"
const int PIN_BLUE = MOSI;   // on board says "MO"

int prevButtonVal = HIGH;
int counter = 0;

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);

    Serial.begin(9600);
}

void loop() {
    // latch
    int currButtonVal = digitalRead(PIN_BUTTON);
    if (prevButtonVal == HIGH && currButtonVal == LOW) {
        if (counter == 0) {  // white
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_GREEN, HIGH);
            digitalWrite(PIN_BLUE, HIGH);

        } else if (counter == 1) {  // orange
            // use PWM and analogWrite
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 100);
            analogWrite(PIN_BLUE, 0);

        } else {  // random color
            analogWrite(PIN_RED, random(0,256));
            analogWrite(PIN_GREEN, random(0,256));
            analogWrite(PIN_BLUE, random(0,256));
        }

        // make sure that our if works for 3, 4,5, ...
        if (counter >= 3) {
            counter = 0;  // reset
        }
        counter = counter + 1;
    }
    prevButtonVal = currButtonVal;  // important
}
//we should also increment counter