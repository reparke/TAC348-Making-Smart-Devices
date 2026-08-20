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
    - need to represent the states (ENUM)
    - way to track the state variables
    - need a way to handle timing (millis)
    - what does loop do?
        - determine the next state (logic)
        - change the outputs based on the next state (LED and OLED)

*/

// TODO:  Create enum State for stoplight states
enum State {
    trafficGo,
    trafficSlow,
    // trafficStop,
    pedWalk,
    pedDontWalk
    // later we account for pedestrians
};

// TODO: Create variables for state change and state length
// var to track the current
State currentState = pedDontWalk;
unsigned long currentStateDuration = 0;

unsigned long prevMillis = 0;

// TODO: create enum Color for signal light colors
enum Color { red, green, yellow, black };

/* ======= FUNCTIONS =========== */
// TODO: COMPLETE setColor
void setColor(Color c) {
    switch (c) {
        case red:
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_GREEN, LOW);
            digitalWrite(PIN_BLUE, LOW);
            break;  // IMPORTANT! always have break at end of case statement
        case green:
            digitalWrite(PIN_RED, LOW);
            digitalWrite(PIN_GREEN, HIGH);
            digitalWrite(PIN_BLUE, LOW);
            break;  // IMPORTANT! always have break at end of case statement
        case yellow:
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_GREEN, HIGH);
            digitalWrite(PIN_BLUE, LOW);
            break;  // IMPORTANT! always have break at end of case statement
        case black:
            digitalWrite(PIN_RED, LOW);
            digitalWrite(PIN_GREEN, LOW);
            digitalWrite(PIN_BLUE, LOW);
            break;  // IMPORTANT! always have break
                    // at end of case statement
    }
}

// TODO: COMPLETE updateNextState

void updateNextState() {
    /*
        what do we do here?
        - determine what is the next state we should go to
        - what changes should we make to the outputs (LED and OLED)

        what determines IF we got a new state?
            - the only input we care about is timer
        what determines WHICH state we go to?
            - the only input that matters is the current state
    */

    unsigned long currMillis = millis();

    // lets handle each state separately
    // we could say
    //  if (currentState == trafficGo)...
    //  a SWITCH statement in C++ is basically mutually excl if ..else if ..else
    switch (currentState) {
        case pedWalk:  // equivalent to if (currentSTate == trafficStop)
            if (currMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = currMillis;   /// update timer
                currentState = pedDontWalk;  // changes state
                Serial.println("Ped Don't Walk");
                setColor(red);
                oled.clear(PAGE);
                oled.setCursor(0,0);
                oled.print("Don't Walk");
                oled.display();
            }
            break;
        case pedDontWalk:  // equivalent to if (currentSTate == trafficStop)
            if (currMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = currMillis;     /// update timer
                currentState = trafficGo;  // changes state
                Serial.println("Traffic Go");
                setColor(green);
                oled.clear(PAGE);
                oled.setCursor(0, 0);
                oled.print("Don't Walk");
                oled.display();
            }
            break;
        case trafficGo:  // equivalent to if (currentSTate ==
                         // trafficStop)
            if (currMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = currMillis;     /// update timer
                currentState = trafficSlow;  // changes state
                Serial.println("Traffic Slow");
                setColor(yellow);
                oled.clear(PAGE);
                oled.setCursor(0, 0);
                oled.print("Don't Walk");
                oled.display();
            }
            break;
        case trafficSlow:  // equivalent to if (currentSTate ==
                           // trafficStop)
            if (currMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = currMillis;     /// update timer
                currentState = pedWalk;  // changes state
                Serial.println("Ped Walk");
                setColor(red);
                oled.clear(PAGE);
                oled.setCursor(0, 0);
                oled.print("Walk");
                oled.display();
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
    // testLightandOLED();      //just for initial testing
    updateNextState();
}
