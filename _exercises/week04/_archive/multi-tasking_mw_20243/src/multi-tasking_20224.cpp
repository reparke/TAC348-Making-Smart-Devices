#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_LED1 = D3;
const int PIN_LED2 = D4;
const int PIN_BUTTON = D2;
/*
    1) Blink LED 1 every 300 ms WITHOUT using delay
        - global variable for the LAST TIME the event occured
        - local variable for the CURRENT TIME NOW
        - global variable for the INTERVAL between events

    2) Blink LED2 every 146 ms
    3) Create toggle button (latch) and  Track the number of times the button is
   pressed and show in Ser Monitor 4) Publish the number of button presses to
   cloud every 10000 ms

    Extra Challenge
        Change LED1 to be on for 300 ms and off for 700 ms
        Change code so that when the toggle button is pressed, LED2 starts
   blinking every 146 milliseconds, and when the toggle button is pressed again,
   LED2 stops blinking
*/

const unsigned long INTERVAL_LED1 = 300;  // 300 ms
const unsigned long INTERVAL_LED2 = 146;
const unsigned long INTERVAL_PUBLISH = 10000;
unsigned long prevMillisLed1 = 0;  // start at 0
unsigned long prevMillisLed2 = 0;
unsigned long prevMillisPublish = 0;

// state of LED
int led1State = LOW;
int led2State = LOW;

int counter = 0;

// button
int prevButtonVal = HIGH;  // button is unpressed

void setup() {
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}

void loop() {
    // get current "relative" time
    unsigned long currMillis = millis();

    // led 1 timer
    // check if the INTERVAL since the last event has elapsed
    if (currMillis - prevMillisLed1 > INTERVAL_LED1) {
        // this means the timer has elapsed!
        // in this IF, always update our timer
        prevMillisLed1 = currMillis;
        if (led1State == LOW) {
            led1State = HIGH;
            digitalWrite(PIN_LED1, led1State);
        } else {  // LED 1 is currently HIGH
            led1State = LOW;
            digitalWrite(PIN_LED1, led1State);
        }

        // put whatever code you want to happen when the timer goes off
    }

    // led 2 timer
    if (currMillis - prevMillisLed2 > INTERVAL_LED2) {
        prevMillisLed2 = currMillis;
        led2State = !led2State;  // switches HIGH to LOW or LOW to HIGH
        digitalWrite(PIN_LED2, led2State);
    }

    // publish timer
    if (currMillis - prevMillisPublish > INTERVAL_PUBLISH) {
        prevMillisPublish = currMillis;
        Particle.publish("Counter", String(counter));
    }

    // button latch
    // what var do we need?
    // global prevButtonVal and local currButtonVal
    int currButtonVal = digitalRead(PIN_BUTTON);
    if (prevButtonVal == HIGH &&
        currButtonVal == LOW) {  // button was just pressed
        counter = counter + 1;
        Serial.println("Counter = " + String(counter));
    }
    prevButtonVal = currButtonVal;  //really important!
}