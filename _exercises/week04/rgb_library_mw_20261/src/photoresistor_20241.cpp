

#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);


const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;  // photon say "MO"
const int PIN_PHOTORESISTOR = A1;

const int THRESHOLD_AMBIENT = 2700;
const int THRESHOLD_DARK = 400;


/*
    in programming we can ADD / IMPORT / INCLUDE extra code libraries

    there are a few libraries specific to working with RGB
*/
#include "rgb-controls.h"
using namespace RGBControls;

// Led led(D0, D1, D2);
Led led(PIN_RED, PIN_GREEN, PIN_BLUE);
Color red(255, 0, 0);
Color blue(0, 0, 255);

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_PHOTORESISTOR, INPUT);
    Serial.begin(9600);
}
void loop() { 
    led.fade(red, blue, 1000);
 }