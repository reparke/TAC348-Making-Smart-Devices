
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

/*
  new projects
  1) configure for device
  2) set global constants for pin label
  3) set pin mode
  4) Serial.begin(9600)
*/

const int PIN_LED = D3;
const int PIN_BUTTON = D2;

int counter = 0;
int prevButtonVal = HIGH;   //what was the button val the LAST time in the loop func

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  Serial.begin(9600);
}


void loop() {
  //button v1
  // //buttons are digital input devices --> 0 or 1
  // int buttonVal = digitalRead(PIN_BUTTON);
  // // Serial.println("Button val = " + String(buttonVal));

  // //use button to turn on LED
  // // when I press the button, the LED turns on
  // //when I release the button, the  LED turns off
  // if (buttonVal == HIGH) { //button is NOT pressed
  //   digitalWrite(PIN_LED, LOW);
  // }
  // else {      //else means button IS PRESSED
  //   digitalWrite(PIN_LED, HIGH);
  //   counter = counter + 1;
  //   Serial.println("Counter = " + String(counter));
  // }
  // delay(100); 

  //every time we press the button, we want a counter to increase
  //print the counter out 

  int currButtonVal = digitalRead(PIN_BUTTON);
  //what is a button press? currVal is LOW and the prevVal is HIGH
  // &&  means "and"
  if (currButtonVal == LOW && prevButtonVal == HIGH) {
    counter = counter + 1;
    Serial.println("Counter = " + String(counter));
  }

  //VERY IMPORTANT! 
  //for button latch code to work, we need to UPDATE the prevButtonVal at the end of the loop
  prevButtonVal = currButtonVal;

  //what if we wanted the LED to turn on and stay on when pressed
  //and turn off and stay off when pressed a second time?
}
