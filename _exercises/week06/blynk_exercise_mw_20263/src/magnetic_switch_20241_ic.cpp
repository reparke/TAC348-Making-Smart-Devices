
// at very top, we need to setup our Blynk access (like api key)
#define BLYNK_TEMPLATE_ID "TMPL2YNk7BNmD"
#define BLYNK_TEMPLATE_NAME "Week 6 MW Exercise"
#define BLYNK_AUTH_TOKEN "WWeuPK5Ccjt25w3n4WRrise92RYcUaGJ"

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


data from APP to PHOTON --> this is different!!!
    EVENT DRIVEN PROGRAMMING

    We write a funct ("event handler") but we DO NOT EVER CALL THE FUNCTION
    --> instead
    when the photon detect the specific "event", the PHOTON will call
        the function
                        AUTOMAGICALLY!!!

    syntax: we create this specific function
    BLYNK_WRITE(VIRTUAL_PIN)

    ex
    BLYNK_WRITE(V9) {
        //this func is called automaticlaly when data is set from APP to PHOTON
on virtual pin V9
    }


*/

// when user presses button on blynk app, let's show a random LED color
void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

// the event handler for when button is pressed on app
BLYNK_WRITE(V5) {
//pretend that the function looks like this    BLYNK_WRITE(V5, param)
    // fn is called EVERY TIME the button on app is pressed OR released
    Serial.println("Button Activity");

    // hidden in this func is a var called param
    // param contains whatever value was sent from the app
    // lets get the hidden value sent from
    int buttonVal = param.asInt();  // or .asString() or .asFloat()
    if (buttonVal == 0) {
        changeLedColor(random(0, 256), random(0, 256), random(0, 265));
    }
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
    // need a short delay for Blynk to start
    delay(5000);
    Blynk.begin(BLYNK_AUTH_TOKEN);  // start communication with the Blynk server
}

void loop() {
    Blynk.run();

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL) {
        prevMillis = currMillis;
        int randNum = random(0, 256);  // rand number from [0-255]
        // send to blynk
        Blynk.virtualWrite(V6, randNum);
    }
    int currSwitchVal = digitalRead(PIN_SWITCH);

    // H -> LOW (falling edge)
    if (currSwitchVal == HIGH && prevSwitchVal == LOW) {
        Blynk.virtualWrite(V3, "opened");
        Serial.println("Switch was just opened");
    } else if (currSwitchVal == LOW && prevSwitchVal == HIGH) {
        Serial.println("Switch was closed");
        Blynk.virtualWrite(V3, "closed");
    }
    // dont forget
    prevSwitchVal = currSwitchVal;
}