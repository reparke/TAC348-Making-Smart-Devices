#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
    to use blynk, there are 4 steps we need to take


*/

// step 1: copy the three values from blynk website (use your own)
//  find this on blynk
#define BLYNK_TEMPLATE_ID "TMPL2YNk7BNmD"
#define BLYNK_TEMPLATE_NAME "Week 6 MW Exercise"
#define BLYNK_AUTH_TOKEN "WWeuPK5Ccjt25w3n4WRrise92RYcUaGJ"

// step 2: include blynk.h
#include <blynk.h>


// step 3: start blynk in setup
// step 4: Blynk.run in loop

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;

/*
    mag switch is NORMALLY open

    when the switch is closed, publish ONE event with the message that the
   switch was closed

    when the switch is open, publish ONE event with the message the swithc was
   opened

    usually, with button latch, we trigger on the falling edge (H -> L)
        we ignore the rising edge

    mag swithc
    curVal         prevVal
      L               H                           -> switch just closed
      H               L                           -> switch just opened
      L               L                           -> still closed
      H               H                           -> still open

*/

int prevSwitchVal = HIGH;

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

/*
    how do we get data FROM app TO PHOTON
        --> EVENT DRIVEN PROGRAMMING

    we write a function but WE DONT CALL IT
        -> when the photon detects "an event", THE photon call the function AUTOMATICALLY

    BLYNK_WRITE(VIRTUALPIN#) {
        code
    }

datastream for button is V5
anytime there is ANY change on pin V5, this funciton will be called
--> press button, release button 
    */
BLYNK_WRITE(V5) {
    
    //by default, blynk send a 0 when pressed, and a 1 when released
    //in this func, we can use "param" to get the value
    
    int buttonVal = param.asInt();      //if string, we could day param.asString()
    if (buttonVal == 0) {
        Serial.println("Button was pressed");
    }
}


void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
    // step 3
    Blynk.begin(BLYNK_AUTH_TOKEN);
}

/*
    data from PHOTON to APP
    data from APP to PHOTON

    data from PHOTON to APP
    -
    Blynk.virtualWrite(VIRTUAL_PIN#, VALUE)
    *** important! we don't want to do virtualWrite too often
        --> it shouldn't in loop() without a millis timer or some latch
*/

unsigned long prevMillis = 0;
const unsigned long BLYNK_INTERVAL = 1000;

void loop() {
    Blynk.run();

    // to send a randon number, we need to make sure we use a millis timer to
    // slow
    //  down how often the message is published

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > BLYNK_INTERVAL) {
        prevMillis = currMillis;
        int randNumber = random(0, 256);
        Blynk.virtualWrite(V6, randNumber);
    }

    int currSwitchVal = digitalRead(PIN_SWITCH);

    if (currSwitchVal == LOW && prevSwitchVal == HIGH) {
        Serial.println("Switch just closed");
        Particle.publish("Switch", "switch was closed");
        changeLedColor(255, 255, 255);
        Blynk.virtualWrite(V3, "closed");
    } else if (currSwitchVal == HIGH && prevSwitchVal == LOW) {
        Serial.println("Switch just opened");
        Particle.publish("Switch", "switch was opened");
        changeLedColor(255, 0, 0);
        Blynk.virtualWrite(V3, "opened");
    }

    prevSwitchVal = currSwitchVal;
}