#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUTTON = D5;
const int PIN_RED = SCL;
const int PIN_GREEN = MISO;  // says "MI" on photon
const int PIN_BLUE = MOSI;   // says "MO" on photon

int counter = 0;
bool isLedOn = false;
int prevButtonVal = HIGH;

int state = 0;

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    Serial.begin(9600);
}
void loop() {
    // //part 1 - toggle
    //   int currButtonVal = digitalRead(PIN_BUTTON);
    //   if (prevButtonVal == HIGH && currButtonVal == LOW) {
    //       // if led is on, turn off
    //       // if led is off, turn on
    //       if (isLedOn == true) {
    //           isLedOn = false;
    //           digitalWrite(PIN_RED, LOW);
    //       } else {
    //           // light is OFF
    //           isLedOn = true;
    //           digitalWrite(PIN_RED, HIGH);
    //       }
    //   }
    //   prevButtonVal = currButtonVal;

    // part 2
    int currButtonVal = digitalRead(PIN_BUTTON);
    if (prevButtonVal == HIGH && currButtonVal == LOW) {
        // four possible states (colors)
        state = state + 1;
        // use modulus or if statement to keep range 0 - 3
        if (state == 4) {
            state = 0;
        }
        if (state == 0) {  // blue
            digitalWrite(PIN_RED, LOW);
            digitalWrite(PIN_GREEN, LOW);
            digitalWrite(PIN_BLUE, HIGH);
        } else if (state == 1) {  // magenta
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_GREEN, LOW);
            digitalWrite(PIN_BLUE, HIGH);

        } else if (state == 2) {  // orange
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 137);
            analogWrite(PIN_BLUE, 0);

        } else {  // random
            analogWrite(PIN_RED, random(0,256));
            analogWrite(PIN_GREEN, random(0, 256));
            analogWrite(PIN_BLUE, random(0, 256));
        }
    }

    prevButtonVal = currButtonVal;
}
