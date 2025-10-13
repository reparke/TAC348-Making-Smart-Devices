#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// 1 blynk tokens
#define BLYNK_TEMPLATE_ID "TMPL2ZN5Kl1pr"
#define BLYNK_TEMPLATE_NAME "Week 6 Exercise"
#define BLYNK_AUTH_TOKEN "cmIEBmyoDpZY8v6dkY5VxrMYdOZmRlyV"
// 2 install and include library
#include <blynk.h>  // if you see red lines, close and reopen

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

/*

*/

int prevSwitchVal = HIGH;  // open
unsigned long prevMillis = 0;
const unsigned long INTERVAL_BLYNK = 1000;

/*   when we want data to go from APP to PHOTON
        we create a special function BLYNK_WRITE(PIN)
        the code in this function is trigger when you press a button ON THE APP

*/
// write function for when use presses button ON THE APP
BLYNK_WRITE(V5) {
    // how do we know if the button was PRESSED or RELEASED?
    // blynk gives a special parameter / variable called param
    // param represents the data that was sent from APP to PHOTON
    int buttonVal = param.asInt();  // 0 or 1, high or low-->button state

    if (buttonVal == 0) {
        changeLedColor(0, 0, 255);
    } else {
        changeLedColor(255, 0, 0);
    }
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
    // 3 - enable Blynk
    delay(5000);
    Blynk.begin(BLYNK_AUTH_TOKEN);
}

void loop() {
    Blynk.run();

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL_BLYNK) {
        prevMillis = currMillis;
        int randNum = random(0, 256);

        /* to send data from the PHOTON to the APP
            Blynk.virtualWrite(VIRTUALPIN, DATA)
        */
        Blynk.virtualWrite(V6, randNum);
    }

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
    // no else because we dont' care about the other states

    prevSwitchVal = currSwitchVal;
}