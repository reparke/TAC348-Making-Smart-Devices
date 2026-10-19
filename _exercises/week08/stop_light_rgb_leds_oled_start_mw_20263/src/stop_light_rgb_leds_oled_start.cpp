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
to build state machine:
    - need to represent all the states of the system (ENUM)
    - need to track current state and any other relevant var (global var)
    - need to track millis
    - build the logic to decide what happens next (loop)
        - look at current state and current inputs
        - use conditional logic to choose next state
        - update any outputs

** why are we even doing this? why do we need state machines?
    - simplifies the code
    - makes more concise and readable
    - bugs and error more traceable
    - more predictable behavior
    - makes it easier to think what is supposed to happen
*/

// TODO:  Create enum State for stoplight states
/*
    we could do this
    const int TRAFFIC_GO = 0;
    const int TRAFFIC_SLOW = 1;
    instead...lets use enum
*/
// enum State { TrafficStop, TrafficGo, TrafficSlow };
enum State { TrafficGo, TrafficSlow, PedWalk, Hold };
// HOLD means don't walk and traffic stopped

// TODO: Create variables for state change and millis timer
// what var do we need to track in order to represent our system?
// we need curent state we are in and we need a millis timer
unsigned long prevMillis = 0;
State currentState = TrafficGo;

// TODO: create enum Color for signal light colors
enum Color { Red, Green, Yellow };

// optional
//  enum Color {Red = 15, Yellow = 25, Green=100};

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
void updateOled(String s) {
    oled.clear(PAGE);
    oled.setCursor(0,0);
    oled.print(s);
    oled.display();
}

// // TODO: COMPLETE updateNextState
void updateNextState() {
    // this is where we implment our state transition diagram
    //  look at current state and current inputs and current time
    //  use logic  to determine next state
    //  update any outputs for  the next state

    unsigned long currMillis = millis();
    // create the logic for EVERY state transition
    // we would write  if (currentState == TrafficGo)....
    // but instead, lets use a switch
    switch (currentState) {
        case TrafficGo:  // same as    if(currentState == TrafficGo) {...}
            // how do we move from Go to Slow (aka under what conditions?)
            if (currMillis - prevMillis > LONG_LIGHT_DURATION) {
                // update timer
                prevMillis = currMillis;
                currentState = TrafficSlow;  // update the state
                // change LED color
                setColor(Yellow);
                updateOled("Don't Walk");
            }
            break;

        case TrafficSlow:
            // how do we move from slow to stop?
            if (currMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = currMillis;
                // currentState = TrafficStop;
                currentState = PedWalk;
                setColor(Red);
                updateOled("Walk");
            }
            break;

        // case TrafficStop:
        case PedWalk:
            if (currMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = currMillis;
                currentState = Hold;
                setColor(Red);
                updateOled("Don't Walk");
            }
            break;
        case Hold:
            if (currMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = currMillis;
                currentState = TrafficGo;
                setColor(Green);
                updateOled("Don't Walk");
            }
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
