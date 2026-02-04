#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = SCL;
const int PIN_GREEN = MISO;  //on board its MI
const int PIN_BLUE = MOSI;  //on board its MO
const int PIN_BUTTON  = D5;

int state = 0;
int prevButtonVal = HIGH;


void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  Serial.begin(9600);
}
void loop() {
 

  //v2 - LATCH
  int currButtonVal = digitalRead(PIN_BUTTON);

  //check for prev button val HIGH and current button val low
  //for tracking prev button val, we need global var
  //in c++, && means and
  if (prevButtonVal == HIGH && currButtonVal == LOW) {
    //NOW WE NOW WE HAVE ONE SINGLE PRESS!
    state = state  + 1;
    if (state == 4) {
      state = 0;
    }
    
    Serial.println("counter = " + String(state));

    if (state == 0) {
        digitalWrite(PIN_RED, HIGH);
        digitalWrite(PIN_BLUE, LOW);
        digitalWrite(PIN_GREEN, LOW);
    }
    if (state == 1) {
        analogWrite(PIN_RED, 245);
        analogWrite(PIN_GREEN, 121);
        analogWrite(PIN_BLUE, 39);
    }
    if (state == 2) {
        digitalWrite(PIN_RED, HIGH);
        digitalWrite(PIN_BLUE, HIGH);
        digitalWrite(PIN_GREEN, HIGH);
    }
    if (state == 3) {
        analogWrite(PIN_RED, random(0,256));
        analogWrite(PIN_GREEN, random(0, 256));
        analogWrite(PIN_BLUE, random(0, 256));
    }
  }

  //SUPER IMPORTANT!
  //with a latch, ALWAYS make sure to update the prevButton OUTSIDE the IF
  prevButtonVal = currButtonVal;


  // //v3 - RGB
  // //turn RGB blue for 500 ms
  // //then turn green for 500 ms
  // digitalWrite(PIN_RED, LOW);
  // digitalWrite(PIN_BLUE, HIGH);
  // digitalWrite(PIN_GREEN, LOW);
  // delay(500);

  // digitalWrite(PIN_RED, LOW);
  // digitalWrite(PIN_BLUE, LOW);
  // digitalWrite(PIN_GREEN, HIGH);
  // delay(500);




}
/*
  what if we want to press the button to turn on the LED,
  then press the button AGAIN to turn off the LED?

  --> we need to track the STATE of the LED
*/