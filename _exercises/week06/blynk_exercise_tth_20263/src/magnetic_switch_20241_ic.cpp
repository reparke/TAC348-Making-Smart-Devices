// #define BLYNK_TEMPLATE_ID "ADD_YOUR_OWN"
// #define BLYNK_TEMPLATE_NAME "ADD_YOUR_OWN"

#define BLYNK_TEMPLATE_ID "TMPL2F6y8kccu"
#define BLYNK_TEMPLATE_NAME "Week 6 TTh"
#define BLYNK_AUTH_TOKEN "vuuv4EVRY0Wt_k1zCgBR4FCHnJj4yYMh"

#include <blynk.h>

#include "Particle.h"

/* Steps to adding blynk
1) Add the three API tokens
2) include blynk.
3) in setup, we begin the blynk communication
4) in looop, we run Blynk.run()
*/

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
mag switch is normally open

exercise
    when the switch is closed, print ONE message saying "switch was closed"
    when the switch is opened, print ONE message saying "switch was opened"

    --> hint: switch is basically a button...so what does that make you think?

    currVal             prevVal                 Meaning
    L                   H                       --> closed - falling edge
    H                   L                       --> open - rising edge
    L                   L                       --> closed
    H                   H                       --> open

*/
/*
with Blynk, we cansend data from PHOTON to the APP, and from APP to PHOTON

start PHOTON to APP

**VERY IMPORTANT**
    -Blynk has a strict quote
    make sure that we do not send lots of data to app
    --> so data going  to the app needs to either
    1) have a millis timer and then unplug your device after
    or
    2) send data infrequent like on a button (latch)
    syntax to send data to blynk is

    Blynk.virtualWrite(VIRTUAL_PIN, DATA)


from APP to PHOTON <--- this is different
    EVENT DRIVEN PROGRAMMING

    we write a func ("event handler") but WE DO NOT EVER CALL the func
    --> when the event happens, the photon will AUTOMAGICALLY call the func for
us

    syntax: create this func (aka event handler)
    BLYNK_WRITE( VIRTUAL_PIN ) {
    }

    ex:
    BLYNK_WRITE(V5) {       //this is the func that will get call automatically
                            //when some data is received on V5
    }
*/
int counter = 0;
// V5 is the Button value
//  imagine that this is actually BLYNK_WRITE(V5, param) {
BLYNK_WRITE(V5) {
    // this func is called when button is PRESSED and RELEASED
    // every BLYNK_WRITE get a "hidden" param called param
    int buttonVal = param.asInt();  // or asString() or asFloat()
    if (buttonVal == 1) {
        counter = counter + 1;
        Serial.println("Button activity: counter " + String(counter));
    }
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);

    delay(5000);  // need short delay
    Blynk.begin(BLYNK_AUTH_TOKEN);
}
void loop() {
    Blynk.run();  // blynk.run should NOT be in millis timer

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL) {
        prevMillis = currMillis;

        int randNum = random(0, 256);  // generate a random number from 0-255
        Blynk.virtualWrite(V6, randNum);
    }

    int currSwitchVal = digitalRead(PIN_SWITCH);
    if (currSwitchVal == LOW && prevSwitchVal == HIGH) {
        Serial.println("switch was closed");
        Blynk.virtualWrite(V3, "closed");
    } else if (currSwitchVal == HIGH && prevSwitchVal == LOW) {
        Serial.println("Switch was opened");
        Blynk.virtualWrite(V3, "opened");
    }
    // important!
    prevSwitchVal = currSwitchVal;
}