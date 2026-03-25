

#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;

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

/*
    when the mag switch is open, print ONE message that says "switch opened"
    when the mag switch is closed, print ONE message that says "switch closed"

    Latch like buttons --

    Prev        Curr                Switch status
    H           H               --> unchanged: open
    H           L               --> just closed         "falling edge"
    L           H               --> just opened         "rising edge"
    L           L               --> unchanged: closed

*/

void loop() {
    // digital input
    int switchVal = digitalRead(PIN_SWITCH);
    // Serial.println(switchVal);

    if (prevSwitchVal == HIGH && switchVal == LOW) {
        Serial.println("switch just closed");
    }
    // else or else if?
    //   we want else if because there are 2 conditions we want to ignore
    else if (prevSwitchVal == LOW && switchVal == HIGH) {
        Serial.println("switch just opened");
    }
    // don't forget to update prev
    prevSwitchVal = switchVal;
}
