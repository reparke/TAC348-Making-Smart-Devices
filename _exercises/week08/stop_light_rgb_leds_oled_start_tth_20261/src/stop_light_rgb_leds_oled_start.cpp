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

/*
to build state machine
- need to represent all the states of the system (ENUM)
- need to track current state and any other relevant var (GLOBAL VAR)
- need to track millis
- build the logic to decide what happens next (loop())
    - look at current and any inputs
    - determine logic for next state
    - update any outputs
*/

// TODO:  Create enum State for stoplight states
// we could do this
// const int TRAFFIC_GO = 0
// const int TRAFFIC_SLOW = 1
// enum State { TrafficStop, TrafficGo, TrafficSlow };
enum State { PedWalk, Hold, TrafficGo, TrafficSlow };
//on your own, implment PedW and Hold, and updateNextState fn


// TODO: Create variables for state change and millis timer
// track current state
State currentState = TrafficGo;
unsigned long prevMillis = 0;

// TODO: create enum Color for signal light colors
// enum Color {Red, Green, Blue}; // do it this way

enum Color {
    Red = 15,
    Green = 20,
    Yellow = 25
};  // if you need to change the int val

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
    oled.setCursor(0,0);
    oled.print(s);
    oled.display();
    Serial.println(s);
}

// // TODO: COMPLETE updateNextState
void updateNextState() {
    // where we implement the state transition diagram
    // look at current state and any inputs
    //  determine next state
    //  update outputs

    unsigned long currMillis = millis();

    // write logic for EVERY state
    // we could say if(currentState == TrafficGO)....
    // but instead, lets use a switch
    switch (currentState) {
        case TrafficGo:  // same as   if(currentState == TrafficGo) {...}
            // how do we go from Go to Slow? (under what conditions?)
            if (currMillis - prevMillis > LONG_LIGHT_DURATION) {
                // update current state
                currentState = TrafficSlow;
                // update timer
                prevMillis = currMillis;
                // set color to yellow
                setColor(Yellow);
                updateOLED("Don't\nWalk");
            }
            break;
        // case TrafficStop:
        case PedWalk:
            if (currMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = currMillis;
                // currentState = TrafficGo;
                currentState = Hold;
                setColor(Red);
                updateOLED("Don't\nWalk");
            }
            break;
        case TrafficSlow:
            if (currMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = currMillis;
                // currentState = TrafficStop;
                currentState = PedWalk;
                setColor(Red);
                updateOLED("Walk");
            }
            break;
        case Hold:
            if (currMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = currMillis;
                // currentState = TrafficStop;
                // currentState = PedWalk;
                currentState = TrafficGo;
                setColor(Green);
                updateOLED("Don't\nWalk");
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
