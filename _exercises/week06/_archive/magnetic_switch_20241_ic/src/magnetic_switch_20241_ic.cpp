#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*

    When the magnetic switch is opened or closed, publish cloud event with the
   message door was opened or door was closed. Note only one publish should
   occur every time door is opened or closed (Hint: Think about how this
   operation is similar to other things we’ve done. what variables would you
   need to this?)

    Your event name should be TAC348_Door
    Change the RGB colors based on their door status
        Red means the door is open
        White means the door is closed

*/

const int PIN_LED = D7;
const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;  // aka MOSI pin
const int PIN_SWITCH = D2;

int prevDoorState = HIGH;
int currDoorState = HIGH;

void changeLedColor(int r, int g, int b) {
    // theoretical "recipe" or algorithm using these input
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
}

void loop() {
    currDoorState = digitalRead(PIN_SWITCH);
    // Serial.println(currDoorState);
    if (currDoorState == LOW && prevDoorState == HIGH) {
        Serial.println("Door was closed");
        Particle.publish("Door state", "Door was closed");
        changeLedColor(255, 0, 0);
    } else if (currDoorState == HIGH && prevDoorState == LOW) {
        Serial.println("Door was opened");
        Particle.publish("Door State", "Door was opened");
        changeLedColor(255, 255, 255);
    }
    prevDoorState = currDoorState;
}