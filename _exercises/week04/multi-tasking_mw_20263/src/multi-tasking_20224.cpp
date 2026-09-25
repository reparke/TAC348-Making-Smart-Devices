#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/* LAB
1) blink LED 1 every 300 ms w/o delay
2) blink LED 2 every 800 ms w/o delay
3) publish num button presses to cloud every 10 sec w/o delay
4) create button latch and track num presses
    -print out each time button is pressed
challenge
5) led1 ON for 300ms anD OFF for 2000ms
6) make button latch enable/disable LED2 from blinking
*/

const int PIN_LED1 = D3;
const int PIN_LED2 = D4;
const int PIN_BUTTON = D2;

/*
how do we implement these timers?
    global var to track LAST TIME the event happened
    global CONSTANT for the interval length
    local var to track current time right now

    global var for the state of what we are tracking
*/
//led1
unsigned long prevMillisLed1 = 0;         // the last time LED1 changed on/off
const unsigned long INTERVAL_LED1 = 300;  // led1 on/off timer is 300 ms
bool led1State = false;                   // led1 starts OFF

//led2 -- which var do we need?
unsigned long prevMillisLed2 = 0;
const unsigned long INTERVAL_LED2 = 8000;
bool led2State = false;

//publish
unsigned long prevMillisPublish = 0;
const unsigned long INTERVAL_PUBLISH = 10000;
//dp we a state var? No
int buttonPresses = 0;

//latch - what var do we need?
int prevButtonVal = HIGH;   //global (currButtonVal is local)


void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    Serial.begin(9600);
}
void loop() {
    // quick example of how delya in BLOCKING (which is bad :( )
    //  int currButtonVal = digitalRead(PIN_BUTTON);
    //  digitalWrite(PIN_LED1, HIGH);
    //  delay(5000);
    //  digitalWrite(PIN_LED1, LOW);
    //  delay(5000);
    //  Serial.println("buttonVal = " + String(currButtonVal));

    unsigned long currMillis = millis();  // current relative time NOW

    // led1 timer
    // check if the timer for led1 has elapsed
    if (currMillis - prevMillisLed1 > INTERVAL_LED1) {
        // inside here, we know that timer has elapsed
        // SUPER IMPORTANT!!! update prevMilli
        prevMillisLed1 = currMillis;
        // if led1state is true, switch led1state and turn led off
        // if led1state is false, switch led1state and turn led on
        if (led1State == true) {  // led1 is on, so turn off
            digitalWrite(PIN_LED1, LOW);
            led1State = false;
        } else {  // led is off, so turn on
            digitalWrite(PIN_LED1, HIGH);
            led1State = true;
        }
    }

    //led2 timer
    //do we need a new currMillis? -- no
    if(currMillis - prevMillisLed2 > INTERVAL_LED2) {
        prevMillisLed2 = currMillis;    //IMPORTANT!
        //same as led1, but here is an alternative C++ shortcut   
        led2State = !led2State;     //flip T -> F,  F -> T
        digitalWrite(PIN_LED2, led2State);
    }

    //publish
    if(currMillis - prevMillisPublish > INTERVAL_PUBLISH) {
        prevMillisPublish = currMillis;
        Particle.publish("button presses = " + String(buttonPresses));
    }

    //latch
    int currButtonVal = digitalRead(PIN_BUTTON);
    if(prevButtonVal == HIGH && currButtonVal == LOW) {
        //this means button was pressed ONCE!
        buttonPresses = buttonPresses + 1;
        Serial.println("button presses = " + String(buttonPresses));
    }
    prevButtonVal = currButtonVal;
}











