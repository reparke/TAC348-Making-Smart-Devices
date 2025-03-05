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
building State Machines
    - need a way to represent all different states (ENUM)
    - need a way to track current and other key var (global var)
    - need a way to track timing (millis)
    - logic to decide what happens next ( loop() )
        - look at current state and any inputs to the system
        - determine the logic that lets you go to a new state
        - update any outputs that should change based on the state

IMPLEMENT STAGE 2
*/

// TODO:  Create enum State for stoplight states
// enum State { TrafficGo, TrafficSlow, TrafficStop };
enum State { TrafficGo, TrafficSlow, PedWalk, PedDontWalk };

// TODO: Create variables for state change and state length
State currentState = TrafficGo;
unsigned long prevMillis = 0;

// TODO: create enum Color for signal light colors
enum Colors { Red, Green, Yellow };

/* ======= FUNCTIONS =========== */
// TODO: COMPLETE setColor
void setColor(Colors c) {
    switch (c) {
        case Red:
            digitalWrite(PIN_RED, 255);
            digitalWrite(PIN_GREEN, 0);
            digitalWrite(PIN_BLUE, 0);
            break;
        case Green:
            digitalWrite(PIN_RED, 0);
            digitalWrite(PIN_GREEN, 255);
            digitalWrite(PIN_BLUE, 0);
            break;
        case Yellow:
            digitalWrite(PIN_RED, 255);
            digitalWrite(PIN_GREEN, 255);
            digitalWrite(PIN_BLUE, 0);
            break;
    }
}

// if ( A || B ) OR
void updateOLED() {
    String output = "";
    switch (currentState) {
        case TrafficGo:
        case TrafficSlow:  // same as if (TrafficGo OR TrafficSlow)
        case PedDontWalk:
            output = "Don't Walk";
            break;
        // case TrafficStop:
        case PedWalk:
            output = "Walk";
            break;
    }

    // switch (currentState) {
    //     case TrafficGo:
    //         output = "Don't Walk";
    //         break;
    //     case TrafficSlow:
    //         output = "Don't Walk";
    //         break;
    //     case TrafficStop:
    //         output = "Walk";
    //         break;
    // }
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.print(output);
    oled.display();
}

// TODO: COMPLETE updateNextState

/*
    - logic to decide what happens next ( loop() )
        - look at current state and any inputs to the system
        - determine the logic that lets you go to a new state
        - update any outputs that should change based on the state*/
void updateNextState() {
    unsigned long curMillis = millis();

    /*
        lets handle each state separately
        we could say if(currentState == TrafficGo)...
        INSTEAD lets try a SWITCH
            switch is basicallly a mutually exclusive if...else if for INTERGRAL
       values
    */
    switch (currentState) {
        case TrafficGo:  // the same as    if(currentState == TrafficGo) { ...}
            // code
            if (curMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = curMillis;
                currentState = TrafficSlow;  // update to new state
                // update outputs -- RGB LED and OLED
                setColor(Yellow);
                updateOLED();
            }
            break;
        case TrafficSlow:  // the same as    if(currentState == TrafficGo) {
                           // ...}
            // code
            if (curMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = curMillis;
                // currentState = TrafficStop;  // update to new state
                currentState = PedWalk;  // update to new state
                // update outputs -- RGB LED and OLED
                setColor(Red);
                updateOLED();
            }
            break;
        // case TrafficStop:
        case PedWalk:
            if (curMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = curMillis;
                // currentState = TrafficGo;  // update to new state
                currentState = PedDontWalk;  // update to new state
                // update outputs -- RGB LED and OLED
                // setColor(Green);
                setColor(Red);
                updateOLED();
            }
            break;
        case PedDontWalk:
            if (curMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = curMillis;
                // currentState = TrafficGo;  // update to new state
                currentState = TrafficGo;  // update to new state
                // update outputs -- RGB LED and OLED
                // setColor(Green);
                setColor(Green);
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
    updateNextState();  // this fn handles state transition
}
