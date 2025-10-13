#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

/* function is for testing RGB only*/
void testRgbLed() {
    changeLedColor(255, 0, 0);  // red
    delay(1000);
    changeLedColor(0, 255, 0);  // green
    delay(1000);
    changeLedColor(0, 0, 255);  // blue
    delay(1000);
    changeLedColor(255, 255, 255);  // white
    delay(1000);
}

/*
    when the mag switch is closed or opened, publish ONE cloud event, with the
   message being that the switch was open or closed. Only publish ONE message
   each time

    Hint:  think about how this operation is similar to other "structures" we've
   built before. What variables would you need to make this happen?

    Also, change RGB color to RED when door close, and white when door open
*/

int prevSwitchVal = HIGH;  // open

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
}

void loop() {
    // testing
    //  testRgbLed();
    int currSwitchVal = digitalRead(PIN_SWITCH);

    /* prev    curr
        H       L       -> switch closed
        L       H       -> switch opened
        L       L       -> still closed
        H       H       -> still open
    */

    // when is closed, that is open -> close which means high -> low
    if (prevSwitchVal == HIGH && currSwitchVal == LOW) {
        Serial.println("Door was closed");
        Particle.publish("Door state", "Door was closed");
        changeLedColor(255, 0, 0);
    } else if (prevSwitchVal == LOW && currSwitchVal == HIGH) {
        Serial.println("Door was open");
        Particle.publish("Door state", "Door was opened");
        changeLedColor(255, 255, 255);
    }
    //no else because we dont' care about the other states

    prevSwitchVal = currSwitchVal;
}