#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
  4 things we do with new proj?
  1 configure proj
  2 create pin labels
  3 pin modes
  4 serial setup (serial.begin)
*/

const int PIN_BUTTON = D5;
const int PIN_RED = SCL;
const int PIN_GREEN = MISO;  // says "MI"
const int PIN_BLUE = MOSI;   // says "MOSI"

int counter = 0;  // track button presses

int prevButtonVal = HIGH;  // "default" not pressed
bool isLedOn = false;      // technically just the RED led

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // v1 - read

    // while button is pressed, turn on LED
    // AND each time button is pressed, increase a counter
    /*
      how do we make the button being pressed turn on the LED?
      how do we track # of times button is pressed?
        need a Global Var

    */
    // int buttonVal = digitalRead(PIN_BUTTON);
    // if (buttonVal == LOW) { //button press
    //   digitalWrite(PIN_RED, HIGH);
    //   counter = counter + 1;
    //   //counter++;  say as counter = counter + 1
    // }
    // else {  //button release
    //   digitalWrite(PIN_RED, LOW);
    // }

    // Serial.println("buttonVal = " + String(buttonVal) + ", counter = " +
    // String(counter));

    // v2 - Latch
    // lets track button presses
    //  we need var to track what happened LAST TIME -- global or locaL?
    //     if we want memory, we need it to be GLOBAL

    // int currButtonVal = digitalRead(PIN_BUTTON);
    // // in C++, "AND" is written as "&&"
    // // in C++, "OR"  is written as "||"
    // if (prevButtonVal == HIGH && currButtonVal == LOW) {
    //     // we now know the button was pressed exactly one time
    //     counter = counter + 1;
    //     Serial.println("counter = " + String(counter));

    // }

    // // SUPER IMPORTANT!!!!!!!!
    // // with a latch, ALWAYS make sure to update prevButtonBal OUTSIDE the IF
    // prevButtonVal = currButtonVal;  // this is we track the past

    // v3 - toggle
    // we need to track the STATE of our led
    /*
      we need to know if the LED is on--> then latch press turns off
      if led is OFF--> then a latch turns ON
    */

    // int currButtonVal = digitalRead(PIN_BUTTON);
    // if (prevButtonVal == HIGH && currButtonVal == LOW) {
    //     // we now know the button was pressed exactly one time
    //     counter = counter + 1;
    //     Serial.println("counter = " + String(counter));
    //     if (isLedOn == false) {
    //         // turn on the LED and update the state var
    //         digitalWrite(PIN_RED, HIGH);  // turn on
    //         isLedOn = true;               // update the state
    //     } else {                          // isLedOn is true
    //         // turn off led and update var
    //         digitalWrite(PIN_RED, LOW);
    //         isLedOn = false;
    //     }
    // }

    // prevButtonVal = currButtonVal;  // this is we track the past

    //v4 - RGB LED practice
    //turn on blue LED for 500 ms
    //turn on yellow led for 500 ms -- green and red together
    digitalWrite(PIN_BLUE, HIGH);
    delay(500);
    digitalWrite(PIN_BLUE, LOW);

    digitalWrite(PIN_RED, HIGH);
    digitalWrite(PIN_GREEN, HIGH);
    delay(500);
    digitalWrite(PIN_RED,LOW);
    digitalWrite(PIN_GREEN, LOW);


/*
  press button, led shows white
  press button again, led show orange
  press again, led turn off

  repeat

  hints: remember a latch can track individual presses
                  orange requires different amounts of red green blue

  */

  }
