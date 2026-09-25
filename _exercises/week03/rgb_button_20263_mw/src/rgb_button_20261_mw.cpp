#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);


/*
  4 things we do when starting every project
  1 configure for device
  2 pin labels
  3 pin modes
  4 setup serial
*/
const int PIN_BUTTON = D5;
const int PIN_RED = SCL; //same as D1
const int PIN_GREEN = MISO;  // on board it says "MI"
const int PIN_BLUE = MOSI;  // on board says "MO"

int numPresses = 0;
int prevButtonVal = HIGH; //start off with button NOT PRESSED

void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // int buttonPresses = 0; //local var 
  //v1 - basic reading button
  //button is a digital input device
  // read with digitalRead --> HIGH or LOW
 // as long as the button is pressed, turn on the red LED, and increment a counter
  // when button is not pressed, turn on green led instead
  /*
    whenever we are building something where we need to "remember" something that happened before, what do we need to have?
      --> GLOBAL VAR
  */

  // int buttonVal = digitalRead(PIN_BUTTON);
  // // Serial.println("buttonVal = " + String(buttonVal));
  // if (buttonVal == HIGH) {   // button is NOT pressed
  //   digitalWrite(PIN_RED, LOW);
  //   digitalWrite(PIN_GREEN, HIGH);
  //   digitalWrite(PIN_BLUE, LOW);
  // }
  // else { //button is pressed LOW
  //   digitalWrite(PIN_RED, HIGH);
  //   digitalWrite(PIN_GREEN,  LOW);
  //   digitalWrite(PIN_BLUE, LOW);
  //   numPresses = numPresses + 1;
  //   Serial.println("presses = " + String(numPresses));
  // }


  // //v2 latch
  // int currButtonVal = digitalRead(PIN_BUTTON);
  // //we need a global var to track what the button was LAST TIME
  // //in c++, "AND" in a boolean expression (if) is &&
  // //in C++, "OR" is ||
  // if (prevButtonVal == HIGH && currButtonVal == LOW) {
  //   // we know this is ONE button press (aka falling edge)
  //   numPresses = numPresses + 1;
  //   Serial.println("Num presses = " + String(numPresses));
  // }
  // //SUPER IMPORTATNT!!!!
  // // we must ALWAYS update prev to curr at the end of the loop (outside the IF)
  // prevButtonVal = currButtonVal;

  //v3 - basic RGB LEDs
  //turn on blue for 500 ms
  //turn on magenta for 500 ms
  //turn off for 500 ms
  //blue
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, HIGH);
  delay(500);

  //magenta
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, HIGH);
  delay(500);

  //off
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, LOW);
  delay(500);

  /*
    press button, show white
    press button again, show orange
    press button 3rd time, show random color

    each time button is pressed, show a counter

    hint: random(0, 10) --> gives random number from 0 to 9

    hint: some colors like orange requires different amounts of red, green, blue

  */

}







