
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

// pin labels
const int PIN_BUTTON = D5;
const int PIN_RED = SCL;     // also called D1
const int PIN_GREEN = MISO;  // photon says "MI"
const int PIN_BLUE = MOSI;   // photon says "MO"

// for latch - store the prev button value (ie last time through loop)
int prevButtonVal = HIGH;
bool isRedLedOn = false;

/* functions in C++
      - The order we define fn is VERY IMPORTANT -> you have to define a fn
   before you use
      - we have to include the return type
      - all input param also have a var type
      - VOID is the return type when a function DOES NOT return anything
*/

// param: 3 int representing 0-255 for red, green, and blue
// return: none
void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void randomRgbLed() {
  //generate 3 random numbers
  // random(startValue, endValueNOTIncluded)
  // random (5, 10) --> 5, 6, 7, 8, 9 (NOT 10)
  int r = random(0, 256);  //256 because the end value is not included in random()
  int g = random(0, 256);
  int b = random(0, 256);

  changeRgbLed(r, g, b);
}

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // version 1: create latch
    //       when you press the button, the red LED will turn on and stay one
    //       when you press the button again, the red LED will turn off and stay
    //       off you don't need a counter
    // int currButtonVal = digitalRead(PIN_BUTTON);
    // /*
    //     prev    curr
    //     HIGH    LOW         -> press down  (falling edge)
    //     LOW     HIGH        --> release    (rising edge)
    //     HIGH    HIGH        --> button is NOT pressed
    //     LOW     LOW          -> button is held down
    // */
    // if (currButtonVal == LOW && prevButtonVal == HIGH) {  // button press!

    //     if (isRedLedOn == true) {
    //         isRedLedOn = false;
    //         digitalWrite(PIN_RED, HIGH);
    //     }
    //     else {
    //         isRedLedOn = true;
    //         digitalWrite(PIN_RED, LOW);
    //     }
    // }
    // // update prev
    // prevButtonVal = currButtonVal;  // this update is OUTSIDE the IF

    // version 2
    //  when you press button once, show the following
    //  red for 1/2 sec, green for 1/2, white for 1/2 sec, and orange for 1/2
    //  sec
    // int currButtonVal = digitalRead(PIN_BUTTON);

    // if (currButtonVal == LOW && prevButtonVal == HIGH) {
    //     // red
    //     // digitalWrite(PIN_RED, HIGH);
    //     // digitalWrite(PIN_GREEN, LOW);
    //     // digitalWrite(PIN_BLUE, LOW);
    //     changeRgbLed(255, 0, 0);
    //     delay(500);

    //     // green
    //     // digitalWrite(PIN_RED, LOW);
    //     // digitalWrite(PIN_GREEN, HIGH);  // red is still on
    //     // digitalWrite(PIN_BLUE, LOW);
    //     changeRgbLed(0, 255, 0);
    //     delay(500);

    //     // white
    //     // digitalWrite(PIN_RED, HIGH);
    //     // digitalWrite(PIN_GREEN, HIGH);
    //     // digitalWrite(PIN_BLUE, HIGH);
    //     changeRgbLed(255, 255, 255);
    //     delay(500);

    //     // orange
    //     // analogWrite(PIN_RED, 255);
    //     // analogWrite(PIN_GREEN, 127);
    //     // analogWrite(PIN_BLUE, 0);
    //     changeRgbLed(255, 127, 0);
    //     delay(500);
    // }
    // prevButtonVal = currButtonVal;
    
    //version 4 - press button and generate a RANDOM color
    int currButtonVal = digitalRead(PIN_BUTTON);
    if (currButtonVal == LOW && prevButtonVal == HIGH) {
      randomRgbLed();
    }

    prevButtonVal = currButtonVal;
}