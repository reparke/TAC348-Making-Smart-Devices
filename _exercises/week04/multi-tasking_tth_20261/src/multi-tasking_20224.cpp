
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_LED1 = D3;
const int PIN_LED2 = D4;
const int PIN_BUTTON = D2;

/*
1) blink led1 every 300 ms WITHOUT delay
    - global var which is the LAST TIME the event happened
    - GLOBAL CONSTANT which is the INTERVAL for the event
    - local var which is the CURRENT TIME
    - hint: to turn led on / off, we probably need a state var

2) blink led2 every 146ms WITHOUT delay

3) create a button latch and track the number of button presses
    -print out each time button is pressed

4) publish the num button presses to particle cloud every 10 sec

challenge
5) led1 on for 300 ms but OFF for 500 ms
6) make button latch enable/disable led2 from blinking
*/

// led1 var
unsigned long prevMillisLed1 = 0;  // last time the event happened
const unsigned long INTERVAL_LED1 = 300;
bool led1State = false;

//led 2 var
unsigned long prevMillisLed2 = 0;
const unsigned long INTERVAL_LED2 = 146;
bool led2State = false;

//publish
unsigned long prevMillisPublish = 0;
const unsigned long INTERVAL_PUBLISH = 10000;
int numPresses = 0;

//latch
int prevButtonVal = HIGH;

void setup() {
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}

void loop() {
    // //experiment
    // digitalWrite(PIN_LED1, HIGH);
    // delay(5000);
    // //check button--no latch
    // int currButtonVal = digitalRead(PIN_BUTTON);
    // if (currButtonVal == LOW) {
    //     Serial.println("Button is pressed!");
    //     //in theory, this is going print out A LOT!
    // }
    // digitalWrite(PIN_LED1, LOW);
    // delay(5000);

    unsigned long currMillis = millis();  // what is time NOW

    // led1 timer
    // check if INTERVAL has elapsed yet
    if (currMillis - prevMillisLed1 >= INTERVAL_LED1) {
        // inside here, we KNOW that timer has elapsed
        // SUPER IMPORTANT! update prevMillis INSIDE IF
        prevMillisLed1 = currMillis;

        // do whatever you want to happen every 300 ms...
        if (led1State == true) {  // led is on
            digitalWrite(PIN_LED1, LOW);
            led1State = false;
        } else {  // led is off
            digitalWrite(PIN_LED1, HIGH);
            led1State = true;
        }
    }

    //led 2
    if(currMillis - prevMillisLed2 >= INTERVAL_LED2) {
        prevMillisLed2 = currMillis;
        //here is fancier way to do the same thing
        led2State = !led2State;  // true --> false,    false --> true
        
        digitalWrite(PIN_LED2, led2State);

    }

    //publish timer
    if(currMillis - prevMillisPublish >= INTERVAL_PUBLISH) {
        prevMillisPublish = currMillis;
        Particle.publish("Button presses", String(numPresses));
    }

    //latch
    int currButtonVal = digitalRead(PIN_BUTTON);
    if (currButtonVal == LOW && prevButtonVal == HIGH) {
        numPresses = numPresses + 1; // numPresses++;
        Serial.println("Presses = " + String(numPresses));
    }
    prevButtonVal = currButtonVal;

    /*
    IMPORTANT!
    for latch, ALWAYS update prevButton EVERYTIME in loop (not in IF)
    for millis timer, ONLY update prevMillis when timer goes off (INSIDE the IF)
    */

}