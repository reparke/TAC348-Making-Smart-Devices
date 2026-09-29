
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
    when the switch is closed, print one message that says "Switch was closed"

    when the switch is open, print one message that says "switch was opened"

    hint: we need some kind of latch
    hint2: switch is a digital input device

    curSWitch           prevSwitch      Means what?
    L                   L               --> no change; swtich still closed
    L                   H               --> was closed
    H                   L               --> was open
    H                   H               --> still open
*/

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
}

void loop() {
    int currSwitchVal = digitalRead(PIN_SWITCH);

    //H -> LOW (falling edge)
    if (currSwitchVal == HIGH && prevSwitchVal == LOW) {
        Serial.println("Switch was just opened");
    }
    else if (currSwitchVal == LOW && prevSwitchVal == HIGH) {
        Serial.println("Switch was closed");
    }
    //dont forget
    prevSwitchVal = currSwitchVal;

}