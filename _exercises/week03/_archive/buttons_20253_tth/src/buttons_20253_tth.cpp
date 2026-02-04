
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
  New projects
  1 configure for device
  2 create GLOBAL pin label
  3 pin modes in setup
  4 serial.begin(9600) in setup

*/

const int PIN_LED = A2;
const int PIN_BUTTON = D4;
int counter = 0;
int prevButtonVal = HIGH;

void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}

void loop() {
    // v1 - read
    // int buttonVal = digitalRead(PIN_BUTTON);  // HIGH or LOW

    // // how can we get the button to turn on the LED?
    // //  idea: we connect LED directly to button
    // //  if statement
    // if (buttonVal == HIGH) {         // HIGH means NOT PRESSED
    //     digitalWrite(PIN_LED, LOW);  // button not pressed, LED off
    // } else {                         // LOW which PRESSED
    //     digitalWrite(PIN_LED, HIGH);
    // }

    // Serial.println("Button val = " + String(buttonVal));

    // its ok to make extra variables
    // remember difference between local and GLOBAL


    // int buttonVal = digitalRead(PIN_BUTTON);  // HIGH or LOW
    // if (buttonVal == LOW) {  // pressed
    //     counter = counter + 1;
    //     Serial.println("Counter = " + String(counter));
    // } 

    // v2 - counter
    // one button increases a counter by one for each press-->print out counter
    int currButtonVal = digitalRead(PIN_BUTTON);
    if (prevButtonVal == HIGH && currButtonVal == LOW) {
      //NOW WE KNOW this is ONE SINGLE PRESS
      counter = counter + 1;
      Serial.println(counter);
    }

    //SUPER IMPORTANT!
    //with a LATCH, always make sure to update the prev value OUTSIDE the IF
    prevButtonVal = currButtonVal;

    //v3 - one press turns LED on, one press turns off

}