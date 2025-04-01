#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// ultrasonic pins
const int PIN_ECHO = D6;
const int PIN_TRIGGER = D5;

const int WARNING_RANGE = 5; //5 inches
const int MIN_RANGE = 1; 
const int MAX_RANGE = 157;

float SPEED_SOUND_CM = 0.03444;
float CM_TO_IN = 0.393701;

void setup() {
    Serial.begin(9600);
    pinMode(PIN_ECHO, INPUT); //Ultra -> P2
    pinMode(PIN_TRIGGER, OUTPUT); //P2 -> Ultra
}

/*
    measure distance
    display
        less than 1 in or more than 157 in, show out of range

        less than 5 in, show warning

        otherwise, show distance
*/

void loop() {
    digitalWrite(PIN_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);
    //these 5 lines of code start the sensor reading
    //aka sending the 8 pulses out

    //pulseIn -- returns the time for signal to change
    int sensorTime = pulseIn(PIN_ECHO, HIGH);

    float distanceCm = sensorTime * SPEED_SOUND_CM / 2;

    float distanceIn = distanceCm * CM_TO_IN;

    // OR is C++ is ||
    if (distanceIn <= MIN_RANGE ||distanceIn >= MAX_RANGE ) {
        Serial.println("Out of range: " + String(distanceIn, 1));
    }
    else if (distanceIn <= WARNING_RANGE) {
        Serial.println("Warning: " + String(distanceIn, 1));
    }
    else {
        Serial.println("Distance: " + String(distanceIn, 1));
    }
    delay(500);
}
