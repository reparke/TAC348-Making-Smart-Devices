
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_WARN);
/*
We'll work on Lab 1. For now, just start with stage 1

Stage 1: 
  Create a latch so the on-board LED turn on and stays on when the
button is pressed the on-board LED turns off and stays off when the button
is pressed again 

Stage 2: Change the firmware so when the button is pressed, the
following light sequence is displayed on the RGB LED red for 1/2 sec green for
1/2 sec blue for 1/2 sec orange for 1/2 sec 

Stage 3: Change the firmware so when
the button is pressed, a random color is show on the RGB LED

*/


const int PIN_RED = SCL;
const int PIN_GREEN = MISO;
const int PIN_BLUE = MOSI;
const int PIN_BUTTON = D5;

int prevButtonVal = HIGH;
//store / track whether the LED is on or not
boolean isLedOn = false;

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    Serial.begin(9600);
}

void loop() {

  // //stage 1 - latch
  // //what var do we need? currButtonVal and prevButtonVal
  // //latch to turn RED LED on
  // int currentButtonVal = digitalRead(PIN_BUTTON);
  // //what is the condition for a press (AKA falling edge)
  // if (currentButtonVal == LOW && prevButtonVal == HIGH) {
  //   //inside here, we know the button was pressed
  //   /*
  //     if LED is on, turn off AND update the state 
  //     else turn ON LED and update the state
  //   */
  //  if (isLedOn == true) {
  //   digitalWrite(PIN_RED, LOW);
  //   isLedOn = false;
  //  }
  //  else { //LED RED is currently OFF
  //   digitalWrite(PIN_RED, HIGH);
  //   isLedOn = true;
  //  }
  // }
  // //update prevButton
  // prevButtonVal = currentButtonVal;

  //stage 2 - sequence
  int currentButtonVal = digitalRead(PIN_BUTTON);
  if (currentButtonVal == LOW && prevButtonVal == HIGH) {
    //red
    digitalWrite(PIN_RED, HIGH);
    digitalWrite(PIN_GREEN, LOW);
    digitalWrite(PIN_BLUE, LOW);
    delay(500);

    //green
    digitalWrite(PIN_RED, LOW);
    digitalWrite(PIN_GREEN, HIGH);
    digitalWrite(PIN_BLUE, LOW);
    delay(500);

    //blue 
    digitalWrite(PIN_RED, LOW);
    digitalWrite(PIN_GREEN, LOW);
    digitalWrite(PIN_BLUE, HIGH);
    delay(500);

    //orange
    // orange is a mix colors
    //we need analogwrite
    analogWrite(PIN_RED, 255);
    analogWrite(PIN_GREEN, 120);
    analogWrite(PIN_BLUE, 0); //same as digitalWrite(PIN_BLUE, LOW);
    delay(500);



  }
  //update prevButton
  prevButtonVal = currentButtonVal;
}
