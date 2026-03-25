/*

    how do we get data FROM photon TO app
    and
                       FROM app TO photon

    1) data FROM photon TO app (easier to understand)
        Blynk.virtualWrite(VIRTUAL_PIN, DATA)

        BUT!!!!!!!!!!!!!!!!

        Blynk has a VERY VERY VERRRRRRY  strict quota
        so if we sent too many messages to blynk, our accounts will be frozen till the end of the month

        we must be cautious not to send too much data too frequently
        --> virtualWrite needs to either be 
                                1) insid a millis timer (unplug photon when done)
                                2) called infrequently (eg on a button)


    2) data FROM app TO PHOTON ---> this one is different!
        EVENT DRIVEN PROGRAMMING

        we write a function ("event handler") but WE DONT CALL IT EVER!
        ---> when the photon detects a specific "event", it will call that function
                    AUTOMATICALLY

    syntax: create this function
    BLYNK_WRITE(VIRTUAL_PIN) {
    }
    ex:
    BLYNK_WRITE(V9) {
        //this function is called AUTOMATICALLY when data is sent from APP on 
                virtual pin V9
    }
*/


//step 1 blynk setup - add BLYNK API / tokens
// these go ABOVE the include
#define BLYNK_TEMPLATE_ID "TMPL27zMterD7"
#define BLYNK_TEMPLATE_NAME "Week 7 TTh"
#define BLYNK_AUTH_TOKEN "Jbu9656E4Yee2ixM04noCYwVoEYROJ--"

//step 2 of blynk setup - add the include
#include <blynk.h>

#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;  

int prevSwitchVal = HIGH;
unsigned long prevMillis = 0;       //timer for sending rand num
const unsigned long INTERVAL = 10000; //10 s

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

// handle the event when a button is pressed ON THE APP
BLYNK_WRITE(V5) {
    //fn called everytime the app button is pressed OR released
    Serial.println("Button activity!");
    //lets distinguish press vs release

    //every time an event is sent from Blynk, it gives us a param/var
    //    --> param

    int buttonVal = param.asInt();  //param.asString()
    if(buttonVal == 1) {
        changeLedColor(random(0,256), random(0, 256), random(0, 256));
    }
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
//step 3 of blynk setup -- Blynk.begin
    delay(5000);
    Blynk.begin(BLYNK_AUTH_TOKEN);
    //.begin sets up the connection between our photon and the app
}

/*
    when the mag switch is open, print ONE message that says "switch opened"
    when the mag switch is closed, print ONE message that says "switch closed"

    Latch like buttons --

    Prev        Curr                Switch status
    H           H               --> unchanged: open
    H           L               --> just closed         "falling edge"
    L           H               --> just opened         "rising edge"
    L           L               --> unchanged: closed

*/

void loop() {
    //step 4- blynk setup - Blynk.run
    Blynk.run();    // this func is NEVER in millis
    // this maintains a constant connection to the app for data exchange

    //generate rand numb and send to app
    // Blynk.virtualwrite to send number from photon to app
    // but what should be cautious of when doing this?
    //      --> dont' send too many messages
    //  cautious guidelines 
    //  1) use virtualWrite only occassionally (switch)
    //  or
    //  2) use long millis timer and make sure to unplug photon when not testing

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL) {
        prevMillis = currMillis;

        int randNum = random(0, 256);
        Blynk.virtualWrite(V6, randNum);
    }


    // digital input
    int switchVal = digitalRead(PIN_SWITCH);
    // Serial.println(switchVal);

    if (prevSwitchVal == HIGH && switchVal == LOW) {
        Serial.println("switch just closed");

        //send the switch status to blynk
        Blynk.virtualWrite(V3, "closed");
    }
    // else or else if?
    //   we want else if because there are 2 conditions we want to ignore
    else if (prevSwitchVal == LOW && switchVal == HIGH) {
        Serial.println("switch just opened");
        Blynk.virtualWrite(V3, "open");
    }
    // don't forget to update prev
    prevSwitchVal = switchVal;
}
