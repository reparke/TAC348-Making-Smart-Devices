
//at very top, we need to setup our Blynk access (like api key)
#define BLYNK_TEMPLATE_ID "TMPL2qVcHF4gR"
#define BLYNK_AUTH_TOKEN "_SAYGrcuk2aJthK4RCSrvIKuNJgLI - xm"


// need to add the library
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
const unsigned long INTERVAL = 5000;

/*
    when the switch is closed, print one message that says "Switch was closed"

    when the switch is open, print one message that says "switch was opened"

    hint: we need some kind of latch
    hint2: switch is a digital input device

    curSWitch           prevSwitch      Means what?
    L                   L               --> no change; swtich still closed
    L                   H               --> was closed
    H                   L               --> was open
    H                   H               --> still open
*/

/*
how to connect Blynk App to our firmware code
1) need to include the two #define tokens at the tp
2) include <blynk.h> underneath those two tokens
3) in setup, we have a short delay and Blynk.begin()
4) in loop, we have Blynk.run()

with Blynk, we can send from PHOTON to APP, and from APP to PHOTON

    from PHOTON to APP

    *** VERY IMPORTANT! ***
    Blynk has a strict quote
    make sure that we do not send LOTS of data to app
    --> any data going from PHOTON to APP needs to either
        1) use millis timer (and unplug after class)
        2) only send infrequently (e.g. button)

    Syntax for this is REALLY easy
    Blynk.virtualWrite(VIRTUAL_PIN, DATA)
*/

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
    //need a short delay for Blynk to start
    delay(5000);
    Blynk.begin(BLYNK_AUTH_TOKEN);  // start communication with the Blynk server
}

void loop() {
    Blynk.run();

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL) {
        prevMillis = currMillis;
        int randNum = random(0,256);    //rand number from [0-255]
        //send to blynk
        Blynk.virtualWrite(V6, randNum);

    }
    int currSwitchVal = digitalRead(PIN_SWITCH);

    //H -> LOW (falling edge)
    if (currSwitchVal == HIGH && prevSwitchVal == LOW) {
        Serial.println("Switch was just opened");
    }
    else if (currSwitchVal == LOW && prevSwitchVal == HIGH) {
        Serial.println("Switch was closed");
    }
    //dont forget
    prevSwitchVal = currSwitchVal;

}