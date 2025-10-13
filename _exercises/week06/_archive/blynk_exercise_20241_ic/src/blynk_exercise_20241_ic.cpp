#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// copy these 3 lines from Blynk website > devices > your device > device info
#define BLYNK_TEMPLATE_ID "TMPL2bpkvWhkl"
#define BLYNK_TEMPLATE_NAME "Week 6"
// #define BLYNK_AUTH_TOKEN "hB0CUlmcrAQE6hYI0yXmXCBDt7kLITJl"
#define BLYNK_AUTH_TOKEN "hB0CUlmcrAQE6hYI0yXmXCBDt7kLITJl"

// include the library
#include <blynk.h>

// two other things we need to do to connect with Blynk
//      start connection in SETUP
//      update connection in LOOP

const int PIN_LED = D7;
const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15; // aka MOSI pin
const int PIN_SWITCH = D2;

int prevDoorState = HIGH;
int currDoorState = HIGH;

unsigned long prevMillis = 0;
const unsigned long INTERVAL_BLYNK =
    1000;  // update from ARGON to APP every 1 sec

/*
    EVENT DRIVEN PROGRAMMING

    we write a function, but we DONT CALL that function EVER
        this function is to be called in a specific situation AKA when a certain
   EVENT happens is useful when we don't know when the event will happen also
   when there is a some necessary lag between when the event happens

    Ex: we write a function that will handle what happens when the use presses
   button in Blynk app but we DONT CALL THAT FUNCTION instead, when the event
   happens (e.g. user presses button on App), then the ARgon will AUTOMAGICALLY
   call that function for us

    receive data FROM app TO argon
*/

void changeLedColor(int r, int g, int b) {
    // theoretical "recipe" or algorithm using these input
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

BLYNK_WRITE(V5) {
    // whenever data is sent from APP to ARGON on THIS pin,
    // the argon will execute for us

    // lets see what data was sent from APP
    int buttonVal = param.asInt();  // param is a Blynk object which lets us
                                    // access the value that was sent

    if (buttonVal == 0) {
        changeLedColor(255, 255, 255);
        Serial.println("Button val 0");
    } else {
        changeLedColor(0, 0, 0);
        Serial.println("Button val 1");
    }
}

void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);

    // start Blynk connection
    Blynk.begin(BLYNK_AUTH_TOKEN);
}

void loop() {
    // update Blynk connection
    Blynk.run();
    /*
        if we are using Blynk, everything in LOOP must be within millis block
        we are sending data to Blynk--we had to make sure that all ddata we send
       in a millis block
    */

    unsigned long curMillis = millis();
    if (curMillis - prevMillis > INTERVAL_BLYNK) {
        prevMillis = curMillis;
        int randomNum = random(0, 256);

        /*
        to send data FROM Argon TO App
            Blynk.virtualWrite(VIRTUAL_PIN, DATA);
                virtual pin is a datastream we set up on the Blynk website
                data is whatever we are sending (int, float, string)
        */
        Blynk.virtualWrite(V6, randomNum);
        Serial.println("Random number = " + String(randomNum));

        int switchVal = digitalRead(PIN_SWITCH);
        if (switchVal == HIGH) {
            Blynk.virtualWrite(V3, "open");
        } else {
            Blynk.virtualWrite(V3, "closed");
        }

        // currDoorState = digitalRead(PIN_SWITCH);
        // // Serial.println(currDoorState);
        // if (currDoorState == LOW && prevDoorState == HIGH) {
        //     Serial.println("Door was closed");
        //     Blynk.virtualWrite(V3, "closed");  // send randNum on virtual pin
        //     v6
        // } else if (currDoorState == HIGH && prevDoorState == LOW) {
        //     Serial.println("Door was opened");
        //     Blynk.virtualWrite(V3, "open");  // send randNum on virtual pin
        //     v6
        // }
        // prevDoorState = currDoorState;
    }
}