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
    - need to represent all the different possible states (ENUM)
    - a way to track the current state and other key data (global var)
    - way to handle timing (millis)
    - logic to decide what happens next (loop)
        - look at current state and inputs
        - determine logic to go to a new state
        - update any outputs (LED and OLED)
*/

// TODO:  Create enum State for stoplight states
enum State {
    trafficGo,
    trafficSlow,
    // trafficStop
    pedWalk,
    pedDontWalk
};

// TODO: Create variables for state change and state length
State currentState = trafficGo;
unsigned long prevMillis = 0;

// TODO: create enum Color for signal light colors
enum Color { red, yellow, green, black };

/* ======= FUNCTIONS =========== */
// TODO: COMPLETE setColor
void setColor(Color c) {
    switch (c) {
        case red:
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_GREEN, LOW);
            digitalWrite(PIN_BLUE, LOW);
            break;
        case yellow:
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_GREEN, HIGH);
            digitalWrite(PIN_BLUE, LOW);
            break;
        case green:
            digitalWrite(PIN_RED, LOW);
            digitalWrite(PIN_GREEN, HIGH);
            digitalWrite(PIN_BLUE, LOW);
            break;
        case black:
            digitalWrite(PIN_RED, LOW);
            digitalWrite(PIN_GREEN, LOW);
            digitalWrite(PIN_BLUE, LOW);
            break;
    }
}

//if (A || B)

void updateOLED() {
    String output = "";
    switch (currentState) {
        case trafficGo:
        case trafficSlow:     // like if(currentState == trafficGo || trafficSlow
        case pedDontWalk:
            output = "Don't Walk";
            break;
        case pedWalk:
            output = "Walk";
            break;
    }
    oled.clear(PAGE);
    oled.setCursor(0,0);
    oled.print(output);
    oled.display();
    
}

// TODO: COMPLETE updateNextState

void updateNextState() {
    /*
        what do we do here?
        - determine the next state (where we should go)
        - make changes to the outputs to reflect the next state

        what determines IF we go to a new state?
        - time
        what determines WHICH state we go to next?
        - current state
    */

    unsigned long currMillis = millis();
    // lets handle each state separately
    /*
     we could say if (currentState == trafficGo)...
     INSTEAD we will use a SWITCH
             switch is basically a mutually excl if else if else
    */
    switch (currentState) {
        case trafficGo:  // the same as    if(currentState == trafficGo)
            if (currMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = currMillis;
                currentState = trafficSlow;
                setColor(yellow);
                updateOLED();
            }
            break;
        case trafficSlow:
            if (currMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = currMillis;
                currentState = pedWalk;
                setColor(red);
                updateOLED();
            }
            break;
        case pedWalk:
            if (currMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = currMillis;
                currentState = pedDontWalk;
                setColor(red);
                updateOLED();
            }
            break;
        case pedDontWalk:
            if (currMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = currMillis;
                currentState = trafficGo;
                setColor(green);
                updateOLED();
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
    updateNextState();
}
