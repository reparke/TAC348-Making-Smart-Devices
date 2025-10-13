#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// to use blynk, there are 4 steps
// step 1: copy these variables
#define BLYNK_TEMPLATE_ID "TMPL2fshaJSC7"
#define BLYNK_TEMPLATE_NAME "Week 6 Ex"
#define BLYNK_AUTH_TOKEN "pK2Je3IRE-td4vRzRAw3fKGQxU_vguM6"

// step 2
#include <blynk.h>  //probably to open/close workbench

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;

int prevSwitchVal = HIGH;
unsigned long prevMillis = 0;
const unsigned long INTERVAL_BLYNK = 1000;

/*
    how do get from app to the device?
    EVENT-DRIVEN PROGRAMMING
    we write a function but WE DONT CALL IT!
        -> when the photon detects the "event", then the photon CALLS THE
   FUNCTION automatically

    BLYNK_WRITE(VIRTUAL_PIN) {
        code
    }
*/
// datastream for button was V5
// anytime there is ANY change on pin V5, this function is called
// when you press button, this function is called
// AND when you release, this function is called AGAIN
BLYNK_WRITE(V5) {
    //    Serial.println("Button was pressed in blynk app!");
    // in this function, we use the "param" variable
    //--param let's us access the data that sent
    int virtualButtonVal = param.asInt();
    if (virtualButtonVal == 0) {
        Serial.println("Virtual Button was pressed");
    }

    // int num = param.asInt();    //telling C++ that it should treat this data as in
    // String msg = param.asString();
}

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

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
    // step 3: start blynk connection
    Blynk.begin(BLYNK_AUTH_TOKEN);
}

/*
    when mag switch is closed, publish ONE cloud event with the message that the
   switch was closed when the switch is opened, publish ONE cloud event as well


    curSwtichVal        prevSwitchVal
      L                     H                   -> switch just closed
      H                     L                   -> switch just opened
      L                     L                   -> still closed
      H                     H                   -> still opened

*/

/*
blynk: we send data FROM app to Photon (ex. button)
and    we send data FROM Photon to app (ex. temperature and humidity)

to send data from Photon to app, use Blynk.virtualWrite(PIN, DATA)

    IMPORTANT!: we can't all virtualWrite too often so either it needs to be
            1) in millis timer
         or 2) triggered infrequently

    Blynk.run() should NEVER be in a millis block

*/
void loop() {
    // testRgb();
    // step 4:
    Blynk.run();  // continually maintains the connection with app

    
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > INTERVAL_BLYNK) {
        prevMillis = curMillis;
        // lets generate a random number and send to app
        int randomNumber = random(0, 256);
        // we set up teh random number datastream on V6
        Blynk.virtualWrite(V6, randomNumber);
    }

    int switchVal = digitalRead(PIN_SWITCH);

    if (switchVal == HIGH && prevSwitchVal == LOW) {  // rising edge
        // open
        Serial.println("Switch was opened");
        Particle.publish("Door State", "Switch was opened");
        changeLedColor(255, 255, 255);
        // door state datastream was v5
        Blynk.virtualWrite(V3, "opened");
    } else if (switchVal == LOW && prevSwitchVal == HIGH) {  // falling edge
        // closed
        Serial.println("Switch was closed");
        Particle.publish("Door State", "Switch was closed");
        changeLedColor(255, 0, 0);
        Blynk.virtualWrite(V3, "closed");
    }
    prevSwitchVal = switchVal;
}