
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;

int prevSwitchVal = HIGH;
/*
mag switch is normally open

exercise
    when the switch is closed, print ONE message saying "switch was closed"
    when the switch is opened, print ONE message saying "switch was opened"

    --> hint: switch is basically a button...so what does that make you think?

    currVal             prevVal                 Meaning
    L                   H                       --> closed - falling edge
    H                   L                       --> open - rising edge
    L                   L                       --> closed
    H                   H                       --> open

*/

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
}
void loop() {
    int currSwitchVal = digitalRead(PIN_SWITCH);
    if (currSwitchVal == LOW && prevSwitchVal == HIGH) {
        Serial.println("switch was closed");
    }
    else if (currSwitchVal == HIGH && prevSwitchVal == LOW) {
        Serial.println("Switch was opened");
    }
    //important!
    prevSwitchVal = currSwitchVal;
}