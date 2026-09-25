
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
LAB
1) blink led1 every 300 ms WITHOUT delay


2) blink led2 every 146ms WITHOUT delay

3) create a button latch and track the number of button presses
    -print out each time button is pressed

4) publish the num button presses to particle cloud every 10 sec

challenge
5) led1 on for 300 ms but OFF for 500 ms
6) make button latch enable/disable led2 from blinking

---
Implementing a timer (multitasking)
--> Goal is to "schedule" events to happen at certain time in the future
    -we need to track what time it is NOW, and what time it was LAST TIME the
event -how long is our timer/alarm/interval

    global var which is prevMillis (last time event happened)
    GLOBAL CONSTANT which is our interval
    local var which is currMillis which is time RIGHT NOW

    global var to track the state of what we interested in (ex. led)


*/
const int PIN_BUTTON = D2;
const int PIN_LED1 = D3;
const int PIN_LED2 = D4;

// led 1 var
unsigned long prevMillisLed1 = 0;  // last time event happened
const unsigned long INTERVAL_LED1 = 300;
bool led1State = false;  // led1 starts OFF

// led2 var
unsigned long prevMillisLed2 = 0;
const unsigned long INTERVAL_LED2 = 146;
bool led2State = false;

// publish var
unsigned long prevMillisPublish = 0;
const unsigned long INTERVAL_PUBLISH = 1000;
// no state / boolean need

// button latch
int buttonPresses = 0;
int prevButtonVal = HIGH;

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    Serial.begin(9600);
}
void loop() {
    // // quick example of why delay is blocking (and bad :) )
    // int currButtonVal = digitalRead(PIN_BUTTON);
    // digitalWrite(PIN_LED1, HIGH);
    // delay(5000);
    // Serial.println("buttonVal = " + String(currButtonVal));
    // digitalWrite(PIN_LED1, LOW);

    // get the current time
    unsigned long currMillis = millis();  // time since photon turned on

    // led 1 timer
    // check if led 1 timer/interval has elapsed
    if (currMillis - prevMillisLed1 >= INTERVAL_LED1) {
        // inside here, we KNOW that the timer has elapsed
        // SUPER IMPORTANT! update prevMillis
        prevMillisLed1 = currMillis;

        // if led1STate is false, then change state and turn on LED
        // if led1state is true, then change state and turn off led
        if (led1State == false) {  // led is currently OFF
            led1State = true;
            digitalWrite(PIN_LED1, HIGH);
        } else {  // led is currently ON
            led1State = false;
            digitalWrite(PIN_LED1, LOW);
        }
    }

    // led 2 timer
    if (currMillis - prevMillisLed2 >= INTERVAL_LED2) {
        prevMillisLed2 = currMillis;
        // alternate C++ shortcut
        led2State = !led2State;  // swittch true --> false, false --> true
        digitalWrite(PIN_LED2, led2State);
    }

    // button latch
    int currButtonVal = digitalRead(PIN_BUTTON);  // button state NOW
    if (prevButtonVal == HIGH && currButtonVal == LOW) {
        //"falling edge"--> ONE SINGLE PRESS
        buttonPresses = buttonPresses + 1;
        Serial.println("buttonPresses = " + String(buttonPresses));
    }
    prevButtonVal = currButtonVal;

    // publish
    if (currMillis - prevMillisPublish >= INTERVAL_PUBLISH) {
        prevMillisPublish = currMillis;

        Particle.publish("NumPresses", String(buttonPresses));
    }
}
