#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// configuring blynk
//step 1: add the Blynk parameters from the website
#define BLYNK_TEMPLATE_ID "TMPL2ey3gT1o5"
#define BLYNK_TEMPLATE_NAME "Week6 Ex"
#define BLYNK_AUTH_TOKEN "foOrUMLZqexXBn8yk8Hy284D6t1bX9UF"

//step 2: install and include library
#include <blynk.h>

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;

int prevSwitchVal = HIGH;
unsigned long prevMillis = 0;
const unsigned long BLYNK_INTERVAL = 1000;

/*
    EVENT-DRIVEN PROGRAMMING -- how data goes from APP to PHOTON (e.g virtual button press)

    event: an triggering condition that we are WAITING 
        --> ASYNCHRONOUS
    we write a function that will be called WHEN THE EVENT happens
        --BUT we don't actuall call the fn ourselves
        --instead, the photon calls it automatically

    for blynk, we define a function called BLYNK_WRITE(VIRTUAL_PIN#)
        inside the function, put the code you want to execute when there is SOME 
        change on that virtual pin

*/

// we made virtual button datastream to be pin V5
BLYNK_WRITE(V5) {
    Serial.println("Button was pressed in blynk app!");
}

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

// test RGB
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
    // step 3: start Blynk
    Blynk.begin(BLYNK_AUTH_TOKEN);
}

/*
Blynk       two different ways we to code
    1) data goes FROM PHOTON to APP
    2) data goes FROM APP TO PHOTON

    #1 data from PHOTON to APP
    Blynk.run() should NEVER be in a millis timer
        we need to NEVER use delay (or only VERY VERY short delay)

    we put the messages we sending to the APP in a millis timer
*/


void loop() {
    //step 4: add Blynk.run()
    Blynk.run();    //continually refreshes the data / connection to the App

    unsigned long curMillis = millis();
    if (curMillis - prevMillis > BLYNK_INTERVAL) {
        prevMillis = curMillis;
        //now lets send a random number from PHOTON to APP
        int randomNum = random(0,256);
        //use Blynk.virtualWrite(PIN, VALUE)
        // we used datastream V6 for random number
        Blynk.virtualWrite(V6, randomNum);
    }


    // read mag switch
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
        changeLedColor(255, 0, 0);
        //v3 was our switch state datastream
        Blynk.virtualWrite(V3, "closed");
    }
    // rising ed
    else if (prevSwitchVal == LOW && curSwitchVal == HIGH) {
        Serial.println("Door was just opened");
        Particle.publish("Door State", "Door was just opened");
        changeLedColor(255, 255, 255);
        Blynk.virtualWrite(V3, "open");
    }
    prevSwitchVal = curSwitchVal;
}