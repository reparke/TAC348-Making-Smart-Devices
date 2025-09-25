#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
    1) Blink LED1 every 300ms without using DELAY
        - global constant which the length of time between events
        - global var for the last time the event occurred (ref point)
        - local var in LOOP for the CURRENT time NOW

   2) Blink LED2 every 146 ms

    3) Create toggle button (latch) and  Track the number of times the button is
   pressed and show in Ser Monitor

   4) Publish the number of button presses to
   cloud every 10000 ms

    Extra Challenge
        Change LED1 to be on for 300 ms and off for 700 ms
        Change code so that when the toggle button is pressed, LED2 starts
   blinking every 146 milliseconds, and when the toggle button is pressed again,
   LED2 stops blinking
*/

const int PIN_LED1 = D3;
const int PIN_LED2 = D4;
const int PIN_BUTTON = D2;

const unsigned long INTERVAL_LED1 = 300;  // interval timer
unsigned long prevMillisLed1 = 0;

// led 2
const unsigned long INTERVAL_LED2 = 146;
unsigned long prevMillisLed2 = 0;

// publish
const unsigned long INTERVAL_PUBLISH = 10000;
unsigned long prevMillisPublish = 0;

// states
int stateLed1 = LOW;  // starts off
int stateLed2 = LOW;

int counter = 0;

//button
int prevButtonVal = HIGH;

void setup() {
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}

void loop() {
    /* Thought experiment
        delay of 10 s
        use latch for button
        track button presses with counter

        flash code and press the button 10 times
        what is the value of the counter?
            is it 10? less than 10? more than 10?

        DELAY STOPS OUR PHOTON!
    */
    // get current time
    unsigned long currMillis = millis();

    // led 1 block
    //  check if the interval for LED1 has elapsed
    if (currMillis - prevMillisLed1 > INTERVAL_LED1) {
        // our timer has elapsed so we should do something
        // IMPORTANT! as soon as we are here, we need to update the timer
        prevMillisLed1 = currMillis;
        // do stuff!
        if (stateLed1 == LOW) {  // led off
            stateLed1 = HIGH;
            digitalWrite(PIN_LED1, stateLed1);
        } else {  // led is on
            stateLed1 = LOW;
            digitalWrite(PIN_LED1, stateLed1);
        }
    }

    // led 2 block
    if (currMillis - prevMillisLed2 > INTERVAL_LED2) {
        prevMillisLed2 = currMillis;
        stateLed2 = !stateLed2;  // H -> L, L->H
        digitalWrite(PIN_LED2, stateLed2);
    }

    // publish block - timer
    if (currMillis - prevMillisPublish > INTERVAL_PUBLISH) {
        prevMillisPublish = currMillis;
        Particle.publish("Counter", String(counter));
    }

    // button latch
    int currButtonVal = digitalRead(PIN_BUTTON);
    if (currButtonVal == HIGH && prevButtonVal == LOW) {
        counter = counter + 1;
    }
    prevButtonVal = currButtonVal; //outside the IF
}

