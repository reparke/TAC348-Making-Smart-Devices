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
build state machine
-
- need to represent all the states of the system (ENUM)
- need to track current state and relevant var (GLOBAL VAR)
- need to track millis
- build logic to decide what happens next (IF and loop())
    - look at current state and any inputs to system
    - determine the logic for which new state I go to
    - update any outputs for the next state
*/

// TODO:  Create enum State for stoplight states
// const int TRAFFIC_GO = 0;
// const int TRAFFIC_SLOW = 1;
// enum State { TrafficGo, TrafficSlow, TrafficStop };
enum State { TrafficGo, TrafficSlow, PedWalk, PedDontWalk };

// TODO: Create variables for state change and millis timer
State currentState = TrafficGo;
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

//   if (A || B)    --> we can the same with SWITCH
// swtich: if we remove BREAK; we have basically created an OR
void updateOLED() {
    String output = "";
    switch (currentState) {
        case TrafficGo:    // don't walk
        case TrafficSlow:  // don't walk
        case PedDontWalk:  // don't walk
            output = "Don't Walk";
            break;

        case PedWalk:  // walk
            output = "Walk";
            break;
        default:        //like else--not required by Workbench
            break;
    }
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.print(output);
    oled.display();
}

// // TODO: COMPLETE updateNextState
/*
- build logic to decide what happens next (IF and loop())
    - look at current state and any inputs to system
    - determine the logic for which new state I go to
    - update any outputs for the next state
    */
void updateNextState() {
    /*
        lets update each state separate
        we could say if(currentState == TRAFFIC_GO)
        INSTEAD lets use a switch
            switch is basically an IF for limited values
    */
    unsigned long curMillis = millis();
    switch (currentState) {
        case TrafficGo:  // same as     if(currentState == TrafficGo)
            if (curMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = curMillis;
                currentState = TrafficSlow;  // update state
                // change light
                setColor(Yellow);
                updateOLED();
            }
            break;
        case TrafficSlow:
            if (curMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = curMillis;
                // currentState = TrafficStop;  // update state
                currentState = PedWalk;  // update state
                // change light
                setColor(Red);
                updateOLED();
            }
            break;
        // case TrafficStop:
        case PedWalk:
            if (curMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = curMillis;
                currentState = PedDontWalk;  // update state
                // change light
                // setColor(Green);
                setColor(Red);
                updateOLED();
            }
            break;
        case PedDontWalk:
            if (curMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = curMillis;
                currentState = TrafficGo;  // update state
                // change light
                // setColor(Green);
                setColor(Green);
                updateOLED();
            }
            break;
    }
}

// green - BR and you work on ped walk
// red  -  we do together

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

    // TODO: uncomment to start state machine
    updateNextState();
}
