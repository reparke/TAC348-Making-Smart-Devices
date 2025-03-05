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

//test RGB
void testRgb() {
    changeLedColor(255,0,0);
    delay(1000);
    changeLedColor(0,255,0);
    delay(1000);
    changeLedColor(0,0,255);
    delay(1000);
    changeLedColor(255,255,255);
    delay(1000);
}

void setup()
{
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
}

void loop()
{
    //read mag switch
    int curSwitchVal = digitalRead(PIN_SWITCH);
    // testRgb();

    /*
        when the mag switch is closed, publish ONE event to the particle cloud
            -- message saying switch was closed and show RED on RGB LED
        when the switch is open, publish ONE event to cloud
            -- saying switch was opened         and show WHITE on LED

        hint: this is similar to what we've done before. Think about about what
    variables we need

    similar to a latch -- but what is the diff
        with button, we interested in button press

    prev    curr
     H        L     -->     switch was just closed
     L        H     -->     switch was just opened
     H        H     -->     switch IS STILL OPEN
     L        L     -->     switch is STILL CLOSED


*/  // falling edge
    if (prevSwitchVal == HIGH && curSwitchVal == LOW) {
        Serial.println("Door was just closed");
        Particle.publish("Door State", "Door was just closed");
        changeLedColor(255,0,0);
    }
    //rising ed
    else if (prevSwitchVal == LOW && curSwitchVal == HIGH) {
        Serial.println("Door was just opened");
        Particle.publish("Door State", "Door was just opened");
        changeLedColor(255, 255, 255);
    }
    prevSwitchVal = curSwitchVal;
}