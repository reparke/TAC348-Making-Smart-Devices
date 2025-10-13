
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;


/*
    mag switch is NORMALLY open 

    when the switch is closed, publish ONE event with the message that the switch was closed

    when the switch is open, publish ONE event with the message the swithc was opened

    usually, with button latch, we trigger on the falling edge (H -> L)
        we ignore the rising edge

    mag swithc
    curVal         prevVal
      L               H                           -> switch just closed
      H               L                           -> switch just opened
      L               L                           -> still closed
      H               H                           -> still open
      
*/

int prevSwitchVal = HIGH;

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
}

void loop() {
    int currSwitchVal = digitalRead(PIN_SWITCH);

    if (currSwitchVal == LOW && prevSwitchVal == HIGH) {
        Serial.println("Switch just closed");
        Particle.publish("Switch", "switch was closed");
        changeLedColor(255,255,255);
    }
    else if (currSwitchVal == HIGH && prevSwitchVal == LOW) {
        Serial.println("Switch just opened");
        Particle.publish("Switch", "switch was opened");
        changeLedColor(255, 0,0);
    }

    prevSwitchVal = currSwitchVal;
}