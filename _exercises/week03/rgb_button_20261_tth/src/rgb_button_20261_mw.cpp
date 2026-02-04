#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUTTON = D5;
const int PIN_RED = SCL;
const int PIN_GREEN = MISO;  //says "MI" on photon
const int PIN_BLUE = MOSI;  //says "MO" on photon


int counter = 0;
int prevButtonVal = HIGH;

void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  Serial.begin(9600);

}
void loop() {
//v1 -- read button
// int buttonVal = digitalRead(PIN_BUTTON); // gives HIGH or LOW
// if (buttonVal == LOW) {  //pressed
//   digitalWrite(PIN_RED, HIGH);
//   counter = counter + 1;
//   Serial.println("counter = " + String(counter));
// }
// else { //not pressed
//   digitalWrite(PIN_RED, LOW);
// }
// Serial.println("button = " + String(buttonVal));
//what if want the LED on when the button is pressed?
// what if we want to count the num times button is pressed?


// //v2 - latch
// // we track button last time in loop, and button val now
// // when prev = H and curr = L, that is ONE PRESS
// // the prevbutton should be a global
// int currButtonVal = digitalRead(PIN_BUTTON);
//   //in C++, "and" in a conditional statement is &&
// if (prevButtonVal == HIGH && currButtonVal == LOW) {
//   //this is the falling edge so we know we get ONLY ONCE
//   counter = counter + 1;
//   Serial.println(counter);
// }
// // SUPER IMPORTANT!
// // with latch, make sure we update prevbutton OUTSIDE THE IF

// prevButtonVal = currButtonVal;

// v3 - RGB LED
// show blue for 1 sec then show green for 1 sec
// digitalWrite(PIN_RED, LOW);
// digitalWrite(PIN_BLUE, HIGH);
// digitalWrite(PIN_GREEN, LOW);
// delay(1000);
// digitalWrite(PIN_RED, LOW);
// digitalWrite(PIN_BLUE, LOW);
// digitalWrite(PIN_GREEN, HIGH);
// delay(1000);


/*
  lab
  part 1
  press the button to show white and white stays on when you release button
  press the button AGAIN to turn off
  (toggle)
  hint: consider how we know (track) whether the light is on or not


  part 2
  commment out part 1
  press button once to show blue
  press again to show magenta
  press 3rd time to show orange
  press 4th to show a random color (different each time)
  hint 1: random(0, 11) ---> random number from 0-10
  hint 2: a color like orange requires "different amounts" of red green blue
*/
}






/*
              input           output
Analog

Digital


Digital OUtput
- LED
- values: HIGH LOW
- digitalWrite

Analog Output
- also LED
- 0 - 255 -- PWM
- analogWrite

Analog Input
- pot
- 0- 495 -- ADC
- analogRead

Digital Input
- button
- values: HIGH and LOW
- digitalInput



*/




























