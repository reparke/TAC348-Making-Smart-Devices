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

void testRgb() {
    changeLedColor(255, 0, 0);
    delay(1000);
    changeLedColor(0, 255, 0);
    delay(1000);
    changeLedColor(0, 0, 255);
    delay(1000);
    changeLedColor(255, 255, 255);
    delay(1000);
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
}

/*
    when mag switch is closed, publish ONE cloud event with the message that the
   switch was closed when the switch is opened, publish ONE cloud event as well


    curSwtichVal        prevSwitchVal
      L                     H                   -> switch just closed
      H                     L                   -> switch just opened
      L                     L                   -> still closed
      H                     H                   -> still opened

*/
void loop() {
    // testRgb();
    int switchVal = digitalRead(PIN_SWITCH);

    if (switchVal == HIGH && prevSwitchVal == LOW) {  // rising edge
        // open
        Serial.println("Switch was opened");
        Particle.publish("Door State", "Switch was opened");
        changeLedColor(255, 255, 255);
    } else if (switchVal == LOW && prevSwitchVal == HIGH) {  // falling edge
        // closed
        Serial.println("Switch was closed");
        Particle.publish("Door State", "Switch was closed");
        changeLedColor(255, 0, 0);
    }
    prevSwitchVal = switchVal;
}