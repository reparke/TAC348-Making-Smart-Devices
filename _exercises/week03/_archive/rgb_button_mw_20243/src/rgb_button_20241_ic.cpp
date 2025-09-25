
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_WARN);

// pin labels
const int PIN_BUTTON = D5;
const int PIN_RED = SCL;     // D1 is the same SCL, you can use either name
const int PIN_GREEN = MISO;  // Photon says "MI"
const int PIN_BLUE = MOSI;   // phohon says "NO"
const int PIN_ONBOARD_LED = D7;

int prevButtonVal = HIGH;
bool isLedOn = false;

// in C++, we must DEFINE functions BEFORE we USE THEM

// create a function to change our RGB LED
void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void displayRandomRgbColor() { // doesn't need input because numbers will be random
  //generate random 
  // random(startNum, endNumNotIncluded)
  // random(5, 10) --> range 5, 6, 7, 8, 9 (but not 10)
  int r = random(0,256);    //generate rand # from 0-255
  int g = random(0,256);
  int b = random(0,256);

  changeRgbLed(r,g,b);

}

void changeRgbLedString(String color) {
  if (color == "red") {
    changeRgbLed(255,0,0);
  }
  else if (color == "white") {
    changeRgbLed(255,255,255);
  }
  // we could keep going here
}

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_ONBOARD_LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // /* stage 1 - latch
    //   we need to store what happened last time (which means this needs to be
    //   global)
    //     --> local var (ie in a fn get erased every time we leave the
    //     function)

    //   Button press: HIGH to LOW
    //   button release: LOW to HIGH
    // */
    // int currButtonVal = digitalRead(PIN_BUTTON);
    // if (currButtonVal == LOW && prevButtonVal == HIGH) {
    //     // if onboard led is ON, then turn it off and update its state
    //     ("whether
    //     // on or off") else turn LED ON (and update state)
    //     if (isLedOn == true) {
    //         isLedOn = false;
    //         digitalWrite(PIN_ONBOARD_LED, LOW);
    //     } else {  // led is currently off
    //         isLedOn = true;
    //         digitalWrite(PIN_ONBOARD_LED, HIGH);
    //     }
    // }
    // // outside the IF, update prevButton
    // prevButtonVal = currButtonVal;

    /* stage 2 - RGB
     */
    // int currButtonVal = digitalRead(PIN_BUTTON);
    // if (currButtonVal == LOW && prevButtonVal == HIGH) {
    //     // how we show red?
    //     // digitalWrite(PIN_RED, HIGH);  // analogWrite(PIN_LED, 255);
    //     // digitalWrite(PIN_GREEN, LOW);
    //     // digitalWrite(PIN_BLUE, LOW);
    //     changeRgbLed(255,0,0);
    //     delay(500);

    //     // show green
    //     // digitalWrite(PIN_RED, LOW);
    //     // digitalWrite(PIN_GREEN, HIGH);
    //     // digitalWrite(PIN_BLUE, LOW);
    //     changeRgbLed(0,255, 0);
    //     delay(500);

    //     // show blue
    //     // digitalWrite(PIN_RED, LOW);
    //     // digitalWrite(PIN_GREEN, LOW);
    //     // digitalWrite(PIN_BLUE, HIGH);
    //     changeRgbLed(0,0,255);
    //     delay(500);

    //     // orange: mix of colors we need analog write
    //     // analogWrite(PIN_RED, 255);
    //     // analogWrite(PIN_GREEN, 120);
    //     // analogWrite(PIN_BLUE, 0);
    //     changeRgbLed(255, 120, 0);
    //     delay(500);

    //     changeRgbLed(0,0,0);    // led off
    // }
    // prevButtonVal = currButtonVal;

    // stage 3
    int currButtonVal = digitalRead(PIN_BUTTON);
    if (currButtonVal == LOW && prevButtonVal == HIGH) {
      //how do display a random color on RGB LED?
      // displayRandomRgbColor();

      changeRgbLedString("white");    //just as example
      //question: can we change the color with strings?
    }

    prevButtonVal = currButtonVal;

    
}

/*
  ADC from 0-4095  ---> PWM from 0-255
  int potVal (ADC Val)
  syntax
    outputVal = map(inputVal, inRangeStart, inRangeEnd, outRangeStart, outRangeEnd)

  int pwmVal = map(potVal, 0, 4095, 0, 255);

*/