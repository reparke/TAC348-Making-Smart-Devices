
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/* new projects
  1) pin labels
  2) configure proj
  3) pin modes
  4) Serial.begin
*/

const int PIN_BUTTON = D2;
const int PIN_LED = A2;
const int PIN_ONBOARD_LED = D7;

int counter = 0;
// new var
int prevButtonVal = HIGH;
bool isLedOn = false;

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_ONBOARD_LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // v1 - read button
    // int buttonVal = digitalRead(PIN_BUTTON);
    // Serial.println("Button val = " + String(buttonVal));
    // //to make led turn on
    // if (buttonVal == LOW) {  // button is PRESSED
    //   digitalWrite(PIN_LED, HIGH);
    // }
    // else {                  // button is NOT PRESSED
    //   digitalWrite(PIN_LED, LOW);
    // }

    // create a counter
    // increment the counter everytime the button is pressed and also display
    // the counter value
    // int buttonVal = digitalRead(PIN_BUTTON);
    // if (buttonVal == LOW) {  // pressed
    //     counter = counter + 1;
    //     digitalWrite(PIN_LED, HIGH);
    //     Serial.println("Counter = " + String(counter));
    // } else {
    //     digitalWrite(PIN_LED, LOW);
    // }

    // LATCH!

    // what is happening now
    int currButtonVal = digitalRead(PIN_BUTTON);
    // ONE press is when prev was H and curr is L
    if (currButtonVal == LOW && prevButtonVal == HIGH) {  // FALLING EDGE
        // in this IF block, we know button was pressed once
        if (isLedOn == false) {  // led is off, so turn it on
            digitalWrite(PIN_LED, HIGH);
            digitalWrite(PIN_ONBOARD_LED, LOW);
            isLedOn = true;
        } else {  // led is on
            digitalWrite(PIN_LED, LOW);
            digitalWrite(PIN_ONBOARD_LED, HIGH);
            isLedOn = false;
        }

        counter = counter + 1;
        Serial.println("Counter = " + String(counter));
    }

    // SUPER IMPORTANT!
    // update the prev val
    prevButtonVal = currButtonVal;

    // how do we toggle the LED on and off?

    // v3 - one press of the button turns the led on
    //      another press turn the led off
    // we need to track the STATE of the LED (is on or off)
}