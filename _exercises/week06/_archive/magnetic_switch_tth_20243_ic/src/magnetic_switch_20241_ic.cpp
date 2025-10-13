#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;

int prevSwitchVal = HIGH; //switch open

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

// function just for testing purposes
void testRgbLed() {
    changeLedColor(255,0,0);
    delay(1000);
    changeLedColor(0,255,0);
    delay(1000);
    changeLedColor(0,0,255);
    delay(1000);
    changeLedColor(255, 255,255);
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
    when the mag switch is closed (or opened), publish ONE cloud event saying "switch was opened (or closed)" and make the LED red if closed, or white if opened

    hint: think about how this operation is similar to other "structures" we have built before
    similar to a latch!

    switch
    Prev        Curr        What happened?
    H           L             switch  was just closed -- falling edge
    H           H             stays open
    L           H             switch was just opened   -- rising edge
    L           L             stays closed 


*/


void loop() {
    //for testing
    // testRgbLed();
    int currSwitchVal = digitalRead(PIN_SWITCH);

    if (prevSwitchVal == HIGH && currSwitchVal == LOW) {
        //switch was just closed
        changeLedColor(255,0,0);
        Serial.println("Switch was closed");
        Particle.publish("Switch status", "Switch was closed");
    }
    else if (prevSwitchVal == LOW && currSwitchVal == HIGH) {
        changeLedColor(255, 255, 255);
        Serial.println("Switch was opened");
        Particle.publish("Switch status", "Switch was opened");
    }
    // else {
    //     //nothing
    // }

    prevSwitchVal = currSwitchVal;
}