#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = SCL;
const int PIN_GREEN = MISO;  //on board its MI
const int PIN_BLUE = MOSI;  //on board its MO
const int PIN_BUTTON  = D5;

/*
  for all LEDs (including all 3 RGB pins), we use a 330 Ohm
  for all buttons, we use a 10 k ohm
*/
int counter = 0;
int prevButtonVal = HIGH;
int isLedOn = false;

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  Serial.begin(9600);
}
void loop() {
  // v1 - read
  // int buttonVal = digitalRead(PIN_BUTTON); //this will give us HIGH or LOW
  // //Serial.println("Button = " + String(buttonVal));
  // //how can we make the button turn on the led?
  // if (buttonVal == LOW) { //button is pressed
  //   digitalWrite(PIN_RED, HIGH);
  //   counter = counter + 1;
  //   Serial.println("counter = " + String(counter));
  // }
  // else {  //button is not pressed
  //   digitalWrite(PIN_RED, LOW);
  // }
  // //how do count num button presses
  // // delay(200);


  // //v2 - LATCH
  // int currButtonVal = digitalRead(PIN_BUTTON);

  // //check for prev button val HIGH and current button val low
  // //for tracking prev button val, we need global var
  // //in c++, && means and
  // if (prevButtonVal == HIGH && currButtonVal == LOW) {
  //   //NOW WE NOW WE HAVE ONE SINGLE PRESS!
  //   counter = counter + 1;
  //   Serial.println("counter = " + String(counter));

  //   // if led is on, turn off
  //   //if led is off, turn on
  //   if (isLedOn == true) {
  //     isLedOn = false;
  //     digitalWrite(PIN_RED, LOW);
  //   }
  //   else{ 
  //     //light is OFF
  //     isLedOn = true;
  //     digitalWrite(PIN_RED, HIGH);
  //   }

  // }

  // //SUPER IMPORTANT!
  // //with a latch, ALWAYS make sure to update the prevButton OUTSIDE the IF
  // prevButtonVal = currButtonVal;


  //v3 - RGB
  //turn RGB blue for 500 ms
  //then turn green for 500 ms
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_BLUE, HIGH);
  digitalWrite(PIN_GREEN, LOW);
  delay(500);

  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_BLUE, LOW);
  digitalWrite(PIN_GREEN, HIGH);
  delay(500);




}
/*
  what if we want to press the button to turn on the LED,
  then press the button AGAIN to turn off the LED?

  --> we need to track the STATE of the LED
*/