
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);

SYSTEM_THREAD(ENABLED);

// SerialLogHandler logHandler(LOG_LEVEL_INFO);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
  with ALL LEDs, we use 330 Ohms resistor
  will BUTTONS, we use 10k resistor
*/

/* Lab
Stage 1: Create a latch so the red LED turn on and stays on when the button
is pressed, and the red LED turns off and stays off when the button is
pressed again

*/

const int PIN_RED = SCL;
const int PIN_GREEN = MISO;  // pin MI
const int PIN_BLUE = MOSI;   // pin MO
const int PIN_BUTTON = D5;

int prevButtonVal = HIGH;
boolean isLedOn = false;

// in c++, we have to DEFINE function before we CALL
// fn: changeRgbColor
// return: nothing --> void
// input params: 3 integers
void changeRgbColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void displayRandomColor() {
  int r = random(0, 256);   //random(a, b) --> number from a to b-1
                            //random(0,256) --> from 0-255
  int g = random(0, 256);
  int b = random(0, 256);

  changeRgbColor(r,g,b);
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}

void loop() {
    // // stage 1: Latch
    //   int currButtonVal = digitalRead(PIN_BUTTON);
    //   if (currButtonVal == LOW && prevButtonVal == HIGH) {
    //     if (isLedOn == true) {
    //       digitalWrite(PIN_RED, LOW);   //the OUTPUT of the device
    //       isLedOn = false;              // the STATE of the device
    //       //print statement here
    //     }
    //     else { // LEd is off
    //       isLedOn = true;
    //       digitalWrite(PIN_RED, HIGH);
    //       //print statement here
    //     }
    //   }
    //   prevButtonVal = currButtonVal; //happens OUTSIDE the IF

    /*
    Stage 2: Change the firmware so when the button is pressed, the
    following light sequence is displayed on the RGB LED red for 1/2 sec,
     green for 1/2 sec,
     blue for 1/2 sec,
     orange for 1/2 sec
    */
    // int curButtonVal = digitalRead(PIN_BUTTON);
    // if (curButtonVal == LOW && prevButtonVal == HIGH) {
    //   //red
    //   // digitalWrite(PIN_RED, HIGH);
    //   // digitalWrite(PIN_GREEN, LOW);
    //   // digitalWrite(PIN_BLUE, LOW);
    //   changeRgbColor(255, 0, 0);
    //   delay(500);
    //   //green
    //   // digitalWrite(PIN_RED, LOW);
    //   // digitalWrite(PIN_GREEN, HIGH);
    //   // digitalWrite(PIN_BLUE, LOW);
    //   changeRgbColor(0,255,0);
    //   delay(500);
    //   // blue
    //   // digitalWrite(PIN_RED, LOW);
    //   // digitalWrite(PIN_GREEN, LOW);
    //   // digitalWrite(PIN_BLUE, HIGH);
    //   changeRgbColor(0, 0, 255);
    //   delay(500);
    //   //orange
    //   // analogWrite(PIN_RED, 255);
    //   // analogWrite(PIN_GREEN, 112);
    //   // analogWrite(PIN_BLUE, 0);
    //   changeRgbColor(255, 112, 0);
    //   delay(500);
    //   // analogWrite(PIN_RED, 0);
    //   // analogWrite(PIN_GREEN, 0);
    //   // analogWrite(PIN_BLUE, 0);
    //   changeRgbColor(0,0,0);
    // }
    // prevButtonVal = curButtonVal;

  //stage 3 - display random color when button is pressed
    int curButtonVal = digitalRead(PIN_BUTTON);
    if (curButtonVal == LOW && prevButtonVal == HIGH) {
      displayRandomColor();
    }
    prevButtonVal = curButtonVal;
}