/*

Building state machines
    - need to represent all states of the system (ENUM)
    - need to track current state and relevant var (GLOBAL VAR)
    - need to track millis
    - build logic to decide what happens next (IF/ SWITCH)
        -look at current state and any inputs
        -determine the logic for which new state to go to
        -update any outputs and new state

*/
// cf: http://siever.info/cse132/weeks/3/studio/
// this code is adapted from Bill Siever
// North-South traffic stoplight and East-West pedestrian walk light

#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// it uses a timing approach based on cur and prevMillis
#include "SparkFunMicroOLED.h"   // Include MicroOLED library
MicroOLED oled(MODE_I2C, 9, 1);  // Example I2C declaration RST=D7, DC=LOW

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;  // aka MOSI pin

const int LONG_LIGHT_DURATION = 5000;   // time for green, red, walk, don't walk
const int SHORT_LIGHT_DURATION = 2000;  // time for yellow
const int BLINK_RATE = 500;             // time for blinking don't walk light

// TODO:  Create enum State for stoplight states
/* we could just use regular const for state
const int TrafficGo = 0
const int TrafficSlow = 1
instead, lets use enum
*/

// state 2: implement PedW and PedDW
//  enum State { TrafficGo, TrafficSlow, TrafficStop };
enum State { TrafficGo, TrafficSlow, PedW, PedDW };

// TODO: Create variables for state change and millis timer
// State currentState = TrafficStop;
State currentState = PedDW;
unsigned long prevMillis = 0;

// TODO: create enum Color for signal light colors
enum Color { Red, Green, Yellow };

/* ======= FUNCTIONS =========== */
// TODO: COMPLETE setColor
void setColor(Color c) {
    switch (c) {
        case Red:
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_GREEN, LOW);
            digitalWrite(PIN_BLUE, LOW);
            break;
        case Green:
            digitalWrite(PIN_RED, LOW);
            digitalWrite(PIN_GREEN, HIGH);
            digitalWrite(PIN_BLUE, LOW);
            break;
        case Yellow:
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_GREEN, HIGH);
            digitalWrite(PIN_BLUE, LOW);
            break;
    }
}

// // TODO: COMPLETE updateOLED
void updateOLED(String s) {
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.print(s);
    oled.display();
}

// // TODO: COMPLETE updateNextState
void updateNextState() {
    // this is our state transition logic function
    /*
        update each state separately
        look at inputs to system and timer
        use logic to decide next state
        update next state and any output

        we COULD say if (current == TrafficGo)
        but! instead lets use a switch statement
            switch is basically an IF for a limited set of values
    */
    unsigned long curMillis = millis();

    switch (currentState) {
        case TrafficGo:  // same as     if(currentState == TrafficGo)
            if (curMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = curMillis;
                // update state
                currentState = TrafficSlow;
                // update our outputs -- RGB color and OLED --come back in  sec
                setColor(Yellow);
                updateOLED("Don't Walk");
            }
            break;  // break is like "closing the IF curly brace"
        case TrafficSlow:
            if (curMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = curMillis;
                // currentState = TrafficStop;
                currentState = PedW;
                setColor(Red);
                updateOLED("Walk");
            }
            break;
        // add new state
        case PedW:
            if (curMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = curMillis;
                currentState = PedDW;
                setColor(Red);  // not necessary but good for safety
                updateOLED("Don't Walk");
            }
            break;
        // case TrafficStop:
        case PedDW:
            if (curMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = curMillis;
                currentState = TrafficGo;
                setColor(Green);
                updateOLED("Don't Walk");
            }
            break;
    }
}

/* ======= FUNCTIONS FOR DEBUGGING LED WIRING ========= */
// functions used for testing only
void testLightandOLED() {
    // test OLED screen
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.setFontType(0);
    oled.println("Testing\nOLED");
    Serial.println("Testing OLED");
    oled.display();
    oled.setFontType(0);  // 7-segment font
    for (int i = 0; i < 20; i++) {
        oled.print(".");
        oled.display();
        delay(10);
    }
    //-----------------------
    // test R, G, B LEDs individually; then white
    int lights[] = {PIN_RED, PIN_GREEN, PIN_BLUE};
    Serial.println("Testing RGB");
    // turn off LED
    for (int i = 0; i < arraySize(lights); i++) {
        digitalWrite(lights[i], LOW);
    }
    // test R G B
    for (int i = 0; i < arraySize(lights); i++) {
        digitalWrite(lights[i], HIGH);
        delay(1000);
        digitalWrite(lights[i], LOW);
        delay(500);
    }
    // show white
    for (int i = 0; i < arraySize(lights); i++) {
        digitalWrite(lights[i], HIGH);
    }
}
/* ============================================== */

void setup() {
    Serial.begin(9600);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);

    oled.begin();      // Initialize the OLED
    oled.clear(ALL);   // Clear the display's internal memory
    oled.display();    // Display what's in the buffer (splashscreen)
    delay(1000);       // Delay 1000 ms
    oled.clear(PAGE);  // Clear the display's internal memory
    oled.display();
}

void loop() {
    // TODO: comment out this function after verifying OLED and RGB LED work
    // testLightandOLED();

    // TODO: uncomment to start state machine
    updateNextState();
}
