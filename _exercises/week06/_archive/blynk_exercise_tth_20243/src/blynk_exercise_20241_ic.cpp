#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

//step 1 - create blynk tokens
#define BLYNK_TEMPLATE_ID "TMPL2dAVkcaSX"
#define BLYNK_TEMPLATE_NAME "Week 6 Exercise"
#define BLYNK_AUTH_TOKEN "OzhOfxhrXY_IUjxIWO8-Mc-B7GJ7f3CW"

//step 2 - add blynk library
#include <blynk.h>

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;

const unsigned long INTERVAL_BLYNK = 1000;
unsigned long prevMillis = 0;

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

//to send data FROM APP to PHOTON
// we create a special function Called BLYNK_WRITE(PIN)
//the body of this function is what you want to happen when button is pressed
BLYNK_WRITE(V5) {
    //if button is pressed down, turn on LED
    //if button is not pressed, turn off LED
    //to do that, we need to know what is the buttonVal
    // blynk gives us a special variable called "param"

    int buttonVal = param.asInt();
    if (buttonVal == 0){
        changeLedColor(0,0,255);
    }
    else {
        changeLedColor(0,0,0);
    }
} 



void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
    //step 3 - connect to blynk
    delay(5000);
    Blynk.begin(BLYNK_AUTH_TOKEN);
}


/*
    send data FROM PHOTON to APP
    -
    when we do this, we want to be careful that we don't send too often
    so we usually want to use a millis timer

    -----------------
    Event Driven Programming
    - 
    we write a function, but we DONT CALL THAT FUNCTION EVER!!!
        --> the function is to be called LATER by the device itself under circumstances

    EVENT happpens and then the function is called ON OUR BEHALF

    Blynk
        we will write a function that will be called automatically when 
            the user presses a button on blynk

*/



void loop() { 
    //step 4 - start Blynk
    Blynk.run(); // IMPORTANT! don't put blynk.run in the millis timer

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL_BLYNK) {
        prevMillis = currMillis;
        //update blynk bysending data FROM PHOTON to APP
        //    virtualWrite(PIN, DATA)
        int randNum = random(0,256);
        Blynk.virtualWrite(V6, randNum);

        //how do we send the current switch state?
        int switchVal = digitalRead(PIN_SWITCH);
        //in blynk datastream, is the switch val sent as int or string? --string
        if (switchVal == HIGH) {
            Blynk.virtualWrite(V3, "open");
        }
        else {
            Blynk.virtualWrite(V3, "closed");
        }

    }
}











