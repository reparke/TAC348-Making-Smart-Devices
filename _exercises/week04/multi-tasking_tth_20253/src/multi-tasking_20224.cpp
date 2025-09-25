
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

int counter = 0;

const int PIN_LED1 = D3;
const int PIN_LED2 = D4;
const int PIN_BUTTON = D2;

/*
    1) Blink Led 1 every 300 ms WITHOUT delay
        - global var which is the LAST TIME the event happened
        - GLOBAL CONSTANT which is the INTERVAL between events
        - local var which is the CURRENT TIME

    2) Blink Led 2 every 146 ms WITHOUT delay
    3) Create button latch and track the number of buttons presses (serial
   monitor) 
   4) Publish the counter every 10 s WITHOUT delay

    Bonus challenge
    - led 1 on for 300 ms and off for 500 ms
    - led 2 keeps blinking at 146 ms BUT make the button latch enable or disable
   led 2
*/
// led1 variables
unsigned long prevMillisLed1 = 0;
const unsigned long INTERVAL_LED1 = 300;  // 300ms
int stateLed1 = LOW;                      // led1 starts OFF initially

//led2 variables
unsigned long prevMillisLed2 = 0;
const unsigned long INTERVAL_LED2 = 146;
int stateLed2 = LOW;

//publish variables
unsigned long prevMillisPublish = 0;
const unsigned long INTERVAL_PUBLISH = 10000;

//button var
int prevButtonState = HIGH;

void setup() {
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}

void loop() {
    // get the current time
    unsigned long currMillis = millis();

    // led 1 timer
    // check if the INTERVAL since the last event has elapsed
    if (currMillis - prevMillisLed1 > INTERVAL_LED1) {
        // inside this if, we KNOW that the timer has elapsed so update timer
        prevMillisLed1 = currMillis;

        // do whatever is supposed happen when timer goes off
        // if LED is on -> switch state, update timer, turn off led
        // if led is off -> swtich state, update timer, turn on led
        if (stateLed1 == LOW) {
            stateLed1 = HIGH;
            // timer already updated above
            digitalWrite(PIN_LED1, HIGH);
        } else {  // led is currently on
            stateLed1 = LOW;
            digitalWrite(PIN_LED1, LOW);
        }
    }

    //led2 timer
    if (currMillis - prevMillisLed2 > INTERVAL_LED2) {
        prevMillisLed2 = currMillis;
        //we can use the same logic for led2 as above
        //but! I'll show a more concise way to do it
        stateLed2 = !stateLed2; // flip HIGH to LOW, and LOW to HIGH
        digitalWrite(PIN_LED2, stateLed2);
    }

    //publish timer
    if (currMillis - prevMillisPublish > INTERVAL_PUBLISH) {
        prevMillisPublish = currMillis;
        Particle.publish("Num Button Presses", String(counter));
    }

    //latch
    int currButtonState = digitalRead(PIN_BUTTON);
    //prevButton needs to be global
    if (prevButtonState == HIGH && currButtonState == LOW) {
        counter = counter + 1;

        //fun fact!
        //counter = counter + 1;  ----->   counter++;
    }
    prevButtonState = currButtonState;
    //IMPORTANT!
    //for latch, ALWAYS update prevButton EVERY TIME in loop (not in the IF)
    //for millis, ALWAYS update prevMillis ONLY INSIDE THE IF




    // counter = counter + 1;

    // Particle.publish("Counter", String(counter));

    // //IMPORTANT! make sure not to publish too often
    // //too often: at minimum, more than once per sec
    // //      -->
    // delay(5000);
}