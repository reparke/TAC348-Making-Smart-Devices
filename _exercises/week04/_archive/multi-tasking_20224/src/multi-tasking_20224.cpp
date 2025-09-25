#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

/*

    Blink LED1 every 300 ms
    Blink LED2 every 146 ms
    Create toggle button (latch) to turn ON BOARD on at rising edge and off
   again at the rising edge Track the number of times the button is pressed
    Publish the number of button presses to cloud every 10000 ms
    Extra Challenge
        Change LED1 to be on for 300 ms and off for 700 ms
        Change code so that when the toggle button is pressed, LED2 starts
   blinking every 146 milliseconds, and when the toggle button is pressed again,
   LED2 stops blinking

*/

const int PIN_BUTTON = D2;
const int PIN_LED1 = D3;
const int PIN_LED2 = D4;
const int PIN_ONBOARD_LED = D7;

// build a variable to track the last time LED1 blinked on or off
unsigned long prevMillisLed1 = 0;
unsigned long prevMillisLed2 = 0;

const unsigned long INTERVAL_LED_1 = 300; //LED1 blink time
const unsigned long INTERVAL_LED_2 = 146;

// state of the LED1
int led1State = LOW;
int led2State = LOW;

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    pinMode(PIN_ONBOARD_LED, OUTPUT);

    Serial.begin(9600);
}

void loop() {
    // version with millis


    // what is current time?
    unsigned long currMillis = millis();
    
    // LED1 block
    //  we want the LED1 to change (on/off) every 300 milliseconds
    if (currMillis - prevMillisLed1 > INTERVAL_LED_1) {
        // change the LED
        if (led1State == LOW) {  // light is off now
            led1State = HIGH;
            digitalWrite(PIN_LED1, led1State);
        } else {
            led1State = LOW;
            digitalWrite(PIN_LED1, led1State);
        }
        // important-- inside this IF  make sure to update prevMillis
        prevMillisLed1 = currMillis;
    }

    //LED 2 block
    if (currMillis - prevMillisLed2 > INTERVAL_LED_2) {
        // change the LED
        // if (led1State == LOW) {  // light is off now
        //     led1State = HIGH;
        //     digitalWrite(PIN_LED2, led2State);
        // } else {
        //     led1State = LOW;
        //     digitalWrite(PIN_LED2, led2State);
        // }
        led2State = !led2State;   //changes low to high or high to low
        digitalWrite(PIN_LED2, led2State);

        // important-- inside this IF  make sure to update prevMillis
        prevMillisLed2 = currMillis;
    }

    // latch
    

    // // version with delay - blocking
    // digitalWrite(PIN_LED1, HIGH);
    // delay(300);
    // digitalWrite(PIN_LED1, LOW);
    // delay(300);

    // int currButtonVal = digitalRead(PIN_BUTTON);
    // if (currButtonVal == LOW) {
    //     Serial.println("Button press");
    // }
}
