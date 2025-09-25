
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

int counter = 0;
const int PIN_LED1 = D3;
const int PIN_LED2 = D4;
const int PIN_BUTTON = D2;

/*
    1) Blink LED1 every 300 ms WITHOUT delay()
        -global var for the LAST time some event occured
        -local var for the CURRENT TIME NOW
        -global constant for the INTERVAL between event

    2) Blink LED2 every 146 ms without delay()
    3) Create a latch(button) and track the number of buttons presss
        show on serial each time button is pressed
    4) Publish the number of button pressed every 2000s again without delay
*/

//variables for timer 1
unsigned long prevMillisLed1 = 0; // always start these at zero
const unsigned long INTERVAL_LED1 = 300;

//variables for timer 2
unsigned long prevMillisLed2 = 0;
const unsigned long INTERVAL_LED2 = 146;

//variable for publish
unsigned long prevMillisPublish = 0;
const unsigned long INTERVAL_PUBLISH = 2000;

//var for latch
int prevButtonState = HIGH;

// we want to track if LED is ON or OFF so we can switch it back and forth
int stateLed1 = LOW;
int stateLed2 = LOW;

void setup() {
    Serial.begin(9600);
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
}

void loop() {
    // from earlier
    // increase counter and send a publish message once every 2 sec
    //  counter = counter + 1;  //counter++;
    //  Particle.publish("counter", String(counter));
    // super important! make sure that we never publish more than 1 per sec
    //  and don't leave device publishing constantly over the weekend
    //  delay(2000);

    //get the CURRENT RELATIVE time
    unsigned long currMillis = millis();

    //led 1 timer
    //check if the INTERVAL since the LAST event has elapsed
    if (currMillis - prevMillisLed1 > INTERVAL_LED1) {
        //if we get here, we KNOW that it's been at least 300ms or more
        //ALWAYS! first update your prevMilllis
        prevMillisLed1 = currMillis;
        //do whatever else you want to do when the timer goes off
        if (stateLed1 == LOW) { // led is off so turn it on
            stateLed1 = HIGH;
            digitalWrite(PIN_LED1, HIGH);
        }
        else {      // led on so turn off
            stateLed1 = LOW;
            digitalWrite(PIN_LED1, LOW);
        }
    }

    // led 2 timer
    if (currMillis - prevMillisLed2 > INTERVAL_LED2) {
        prevMillisLed2 = currMillis;
        //c++ shortcut
        stateLed2 = !stateLed2; //flip L-H or H-L
        digitalWrite(PIN_LED2, stateLed2);
    }

    //publish timer
    if (currMillis - prevMillisPublish > INTERVAL_PUBLISH) {
        prevMillisPublish = currMillis;
        Particle.publish("Num Presses", String(counter));
    }

    //latch
    //what var do we need?
    //prevButton (global) and currButton
    int currButtonState = digitalRead(PIN_BUTTON);
    if (currButtonState == LOW && prevButtonState == HIGH) {
        counter = counter + 1;
        Serial.println("Counter = " + String(counter));
    }
    prevButtonState = currButtonState; // IMPORTANT! update happens OUTSIDE the IF
}