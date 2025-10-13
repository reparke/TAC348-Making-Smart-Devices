
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;

int prevSwitch = HIGH;

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
    mag switch is normally open or closed? OPEN

    when swtich is closed, publish ONE message to cloud that says "switch was closed" and show white on LED

    when switch is open, publish ONE message to cloud "switch was opened" and show Red on LED

    typically with a latch, we have cared the falling edge H->L (ignore rising edge)

    CurSwitch               PrevSwitch
      L                         H               --> switch was just closed
      H                         L               --> switch was just opened
      L                         L               --> still closed
      H                         H               --> still open

*/

void loop() {
    int curSwitch = digitalRead(PIN_SWITCH);

    if (curSwitch == HIGH && prevSwitch == LOW) {
        //falling edge
        Particle.publish("Switch", "switch was opened");
        changeLedColor(255,0,0);
        Serial.println("opened");
    }
    else if (curSwitch == LOW && prevSwitch == HIGH) {
        //rising edge
        Particle.publish("Switch", "switch was closed");
        changeLedColor(255, 255, 255);
        Serial.println("closed");
    }
    prevSwitch = curSwitch;
}