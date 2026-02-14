
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/* LAB

1) Blink LED 1 on/off every 300 ms WITHOUT delay
    -global var which is the LAST TIME the event happened
    -GLOBAL CONST which the INTERVAL between
    -local var which the current time

2) blink led2 every 146 ms WITHOUT delay
3) create button latch and track the numbers of presses (serial monitor)
4) publish the particle cloud the counter every 10 s WITHOUT DELAY

Challenge
- led1 on for 300 ms and off for 500ms
- led2 keeps blinking at 146ms, but it can be enabled/disabled by pressing
button

*/

const int PIN_LED1 = D3;
const int PIN_LED2 = D4;
const int PIN_BUTTON = D2;

// led1 variable
unsigned long prevMillisLed1 = 0;         // last time led1 changed on/off
const unsigned long INTERVAL_LED1 = 300;  //"timer" is 300 ms
bool led1State = false;                   // led starts OFF

// led2 var
unsigned long prevMillisLed2 = 0;
const unsigned long INTERVAL_LED2 = 146;
bool led2State = false;

// publish var
unsigned long prevMillisPublish = 0;
const unsigned long INTERVAL_PUBLISH = 10000;
// no state var needed

// latch
//  we need currentButtonval (local), and prevButtonVal (global)
int counter = 0;
int prevButtonVal = HIGH;

void setup() {
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}
void loop() {
    //     // here is the problem with delay
    // digitalWrite(PIN_LED1, HIGH);
    // delay(5000);
    // int currButtonVal = digitalRead(PIN_BUTTON);
    // if (currButtonVal == LOW) {  // for quick example, we won't use a latch
    //     counter = counter + 1;
    //     Serial.println("Counter =  " + String(counter));
    // }
    // digitalWrite(PIN_LED1, LOW);
    // delay(5000);

    // we need the current tiem
    unsigned long currMillis = millis();
    // lets see if our led1 timer is up yet
    if (currMillis - prevMillisLed1 >= INTERVAL_LED1) {
        // we know our "timer" went off!
        // SUPER IMPORTANT! since timer elapsed, we must update INSIDE the IF
        prevMillisLed1 = currMillis;

        // now we do whatever we want to happen when timer goes off

        // if LED is on --> switch state, update timer, turn off led
        // if led is off --> switch state, update timer, turn on led
        if (led1State == HIGH) {
            led1State = LOW;
            digitalWrite(PIN_LED1, LOW);
        } else {  // led1state is LOW
            led1State = HIGH;
            digitalWrite(PIN_LED1, HIGH);
        }
    }

    // calling mlllis() again is optional
    if (currMillis - prevMillisLed2 >= INTERVAL_LED2) {
        prevMillisLed2 = currMillis;
        // OK to use logic from blink 1, but here's a condensed c++ approach
        led2State = !led2State;
        digitalWrite(PIN_LED2, led2State);
    }

    // publish
    if (currMillis - prevMillisPublish >= INTERVAL_PUBLISH) {
        prevMillisPublish = currMillis;
        Particle.publish("Counter = " + String(counter));

        // in c++,    counter++;   is the same as counter = counter + 1;
    }

    // latch
    int currButtonVal = digitalRead(PIN_BUTTON);
    if (currButtonVal == LOW && prevButtonVal == HIGH) {
        counter++;
        // or counter = counter + 1;
        Serial.println("Counter = " + String(counter));
    }
    //IMPORTANT!
    prevButtonVal = currButtonVal;
}

/*

long a bIIIIIIG int
-2billion to +2billion --> ~23 days

we know millis will ALWAYS be positive

unsigned long
0 to +4 billion --> ~46 days

*/