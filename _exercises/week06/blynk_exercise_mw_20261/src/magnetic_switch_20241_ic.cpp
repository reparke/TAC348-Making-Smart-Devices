#define BLYNK_TEMPLATE_ID "TMPL21BiP1QIU"
#define BLYNK_TEMPLATE_NAME "Week 7 MW Exericse"
#define BLYNK_AUTH_TOKEN "4SDu4rE1g8vA_9eTUaRRquSx0IHl6HBM"

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
unsigned long prevMillis = 0;
const unsigned long INTERVAL = 10000;

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

/*
    mag switch is normally open

    when the switch is closed, print ONE message that says "switch was closed"
        and show white on LED

    when swtich is open, print ONE message that says "switch was opened"
        and show red

    ==> secret we need some kind of latch

    CurSwitch               PrevSwitch
    L                       L               --> no change; still closed
    L                       H               --> switch opened
    H                       L               --> switch closed
    H                       H               --> no change; still open
*/

/*
    how to connect BLYNK to Firmware code
    1) include the three BLYNK token for our device
    2) include blynk.h UNDERNEATH the blynk token
    3) in setup, include short delay and blynk.begin
    4) in loop, Blynk.run()
*/

/*
    With Blynk, we can send from PHOTON to APP, and from APP to PHOTON

    from PHOTON to APP

    *** VERY IMPORTANT ****
        Blynk has a STRICT quota
        make sure that we do not send LOTS of data to App
        so any data going FROM PHOTON TO APP needs to either be
            1) with a millis timer (unplug after class or when done with
   assignment) 2) something infrequent like when we press a button

    Syntax is
    Blynk.virtualWrite(VIRTUAL_PIN, DATA)


    ----------------
    from APP to PHOTOH

    EVENT-DRIVEN PROGRAMMING
        when an EVENT happens, then our code does something (a fn is called)

        we write a function BUT WE DO NOT CALL IT!!
            --> when the photon detects the specific event
                    then  the photon ITSELF calls the function automatically

        syntax
        we create global function 
        BLYNK_WRITE(VIRTUAL_PIN) {
            //action that you want to happen data is sent on VIRTUAL_PIN
        }

        this functions are called EVENT HANDLERS


*/

//we want an EVENT HANDLER for datastream on V5
// anytime there is ANY change on pin V5, this function is called automatically

BLYNK_WRITE(V5) {
    //when virtual button is pressed, lets display a random color on our
    // physical LED
    
    //when an event happens, we get a param (variable)
    //we access the param with this syntax
    int buttonVal = param.asInt();  //this is value sent by our virtual button

    if(buttonVal == 1) {
        changeLedColor(random(0,256), random(0, 256), random(0, 256));
        Serial.println("virtual button press!");
    }
}


void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);

    delay(5000);
    Blynk.begin(BLYNK_AUTH_TOKEN);
}
void loop() {
    Blynk.run();
    int switchVal = digitalRead(PIN_SWITCH);

    unsigned long currMillis = millis();
    if(currMillis - prevMillis >= INTERVAL) {
        prevMillis = currMillis;
        int randNum = random(0, 265);
        //send num to blynk
        Blynk.virtualWrite(V6, randNum);
    }

    // know when opened and know when closed

    //we want to generate a random number and send it from PHOTON to APP
    // ---> we Blynk.virtualWrite
    // but what do we need to be careful with when using Blynk.virtualWrite?
    //------> vERY VERVERY VERY low quota
    //   when we use virtualWrite, we have
    //          1) use a long millis timer (and unplug photon when not using)
    //      or  2) only use this function occassionally (like below)
    //for random #, we need a millis timer

    // H --> L    falling edge
    if (switchVal == HIGH && prevSwitchVal == LOW) {
        Serial.println("Switch just opened");
        changeLedColor(255, 255, 255);
        Blynk.virtualWrite(V3, "open");
    }

    // L --> H    rising edge
    else if (switchVal == LOW && prevSwitchVal == HIGH) {
        Serial.println("Switch just closed");
        changeLedColor(255, 0, 0);
        Blynk.virtualWrite(V3, "closed");
    }
    // do we need to worry about the other 2 conditions?

    // don't forget
    prevSwitchVal = switchVal;
}
