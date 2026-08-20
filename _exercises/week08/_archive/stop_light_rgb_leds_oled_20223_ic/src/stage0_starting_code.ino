/*
Lab Stages
    1. Create cycle with only traffic (North-South) stop lights
    2. Add Pedestrian Walk / Don't Walk (East-West) message to OLED
        New states: PedWalk PedDontWalk
        OLED: walk during PedWalk, don't walk during everythign else
    3. Make Don't Walk light blink when it is on (if time)

Approach
    1. we need a way to reprsesent what state the stop light is
    2. we need a way to track state transitions with a variable
    3. we need to monitor the timing with millis
    4. what does loop do? (this is what happens EVERY PROJECT THAT YOU USE A
STATE MACHINE) a. figure out what is the new / next state b. update my outputs
(LED, and the OLED)

*/

// cf: http://siever.info/cse132/weeks/3/studio/
// this code is adapted from Bill Siever
// North-South traffic stoplight and East-West pedestrian walk light

// it uses a timing approach based on cur and prevMillis
#include "SparkFunMicroOLED.h"   // Include MicroOLED library
MicroOLED oled(MODE_I2C, 9, 1);  // Example I2C declaration RST=D7, DC=LOW

const int PIN_RED = D2;
const int PIN_GREEN = D3;
const int PIN_BLUE = D4;

const int LONG_LIGHT_DURATION = 5000;   // time for green, red, walk, don't walk
const int SHORT_LIGHT_DURATION = 2000;  // time for yellow
const int BLINK_RATE = 500;             // time for blinking don't walk light

// TODO:  Create enum State for stoplight states
// enum State { trafficGo, trafficSlow, trafficStop };
enum State { trafficGo, trafficSlow, pedWalk, pedDontWalk };

// TODO: create enum Color for signal light colors
enum Color { Red, Yellow, Green, Black };

// TODO: Create variables for state change and state length
State currentState = trafficGo;
unsigned long prevMillisState = 0;
unsigned long stateDuration =
    0;  // how long are we supposed to in the currentState

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

/* ======= FUNCTIONS =========== */

// TODO: COMPLETE updateNextState
void updateNextState() {
    unsigned long currentMillis = millis();
    switch (currentState) {  // lets examine the var currentState and have
                             // condition / cases for its value
        case trafficGo:
            if (currentMillis - prevMillisState > LONG_LIGHT_DURATION) {
                // we have passed 5 sec
                prevMillisState = currentMillis;
                currentState =
                    trafficSlow;  // this is how was transition to a new state
                updateLights();
                updateOLED();
            }
            break;
        case trafficSlow:
            if (currentMillis - prevMillisState > SHORT_LIGHT_DURATION) {
                // we have passed 5 sec
                prevMillisState = currentMillis;
                currentState =
                    pedWalk;  // this is how was transition to a new state
                updateLights();
                updateOLED();
            }
            break;
        case pedWalk:
            if (currentMillis - prevMillisState > LONG_LIGHT_DURATION) {
                // we have passed 5 sec
                prevMillisState = currentMillis;
                currentState =
                    pedDontWalk;  // this is how was transition to a new state
                updateLights();
                updateOLED();
            }
            break;
        case pedDontWalk:
            if (currentMillis - prevMillisState > SHORT_LIGHT_DURATION) {
                // we have passed 5 sec
                prevMillisState = currentMillis;
                currentState =
                    trafficGo;  // this is how was transition to a new state
                updateLights();
                updateOLED();
            }
            break;
    }
}

// TODO: COMPLETE updateNextStateDuration
void updateNextStateDuration() {}

// TODO: COMPLETE setColor
void setColor(Color c) {
    switch (c) {
        case Green:
            digitalWrite(PIN_RED, LOW);
            digitalWrite(PIN_GREEN, HIGH);
            digitalWrite(PIN_BLUE, LOW);
            break;
        case Red:
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_GREEN, LOW);
            digitalWrite(PIN_BLUE, LOW);
            break;
        case Yellow:
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_GREEN, HIGH);
            digitalWrite(PIN_BLUE, LOW);
            break;
        case Black:
            digitalWrite(PIN_RED, LOW);
            digitalWrite(PIN_GREEN, LOW);
            digitalWrite(PIN_BLUE, LOW);
            break;
    }
}

// TODO: COMPLETE updateLights
void updateLights() {
    switch (currentState) {
        case trafficGo:  // if currentState == trafficGo
            // make RGB LED green with digitalWrite
            setColor(Green);
            break;
        case trafficSlow:  // if currentState == trafficGo
            // make RGB LED green with digitalWrite
            setColor(Yellow);
            break;
        case pedWalk:  // if currentState == trafficGo
            // make RGB LED green with digitalWrite
            setColor(Red);
            break;
        case pedDontWalk:  // if currentState == trafficGo
            // make RGB LED green with digitalWrite
            setColor(Red);
            break;
    }
}

// TODO: COMPLETE updateOLED
void updateOLED() {
    String output = "";
    switch (currentState) {
        case trafficGo:
        case trafficSlow:
        case pedDontWalk:
            output = "Don't walk";
            break;

        case pedWalk:
            output = "Walk";
            break;
    }
    oled.clear(PAGE);
    oled.setCursor(0,0);
    oled.setFontType(1);
    oled.print(output);
    oled.display();

}

void loop() {
    // TODO: comment out this function after verifying OLED and RGB LED work
    // testLightandOLED();
    /*
        update the currentState to whatever we are going into next
        update the outputs (LED and OLED)
        update how long we are supposed in the next state
    */
    updateNextState();
}

/* ======= FUNCTIONS FOR DEBUGGING LED WIRING ========= */
// functions used for testing only
void testLightandOLED() {
    // test R, G, B LEDs individually; then white
    int lights[] = {PIN_RED, PIN_GREEN, PIN_BLUE};

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

    //-----------------------

    // test OLED screen
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.setFontType(0);
    oled.println("Testing OLED");
    oled.display();

    oled.setFontType(0);  // 7-segment font
    for (int i = 0; i < 20; i++) {
        oled.print(".");
        oled.display();
        delay(10);
    }
    oled.clear(PAGE);  // Clear the display
    oled.display();
}
