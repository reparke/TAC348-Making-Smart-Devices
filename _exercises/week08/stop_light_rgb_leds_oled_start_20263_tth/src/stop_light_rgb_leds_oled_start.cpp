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
why do we we even care about or need state machines?
or  what are the benefits?
    - to simplify our code
    - think at a higher level
    - reduces error --> easier to code and think
    - easier to modify and to translate our design into code

to build a state machine
    - need to represent all the states of our system (ENUM)
    - need to track the current state and other relevant var (global var)
    - track millis
    - build the nextState logic
*/

/*
we could say
const int Traffic = 0  for each state
but instead, let's group together as enum
*/
// TODO:  Create enum State for stoplight states
// enum State { TrafficGo, TrafficSlow, TrafficStop };
enum State { TrafficGo, TrafficSlow, PedWalk, Hold };

// TODO: Create variables for state change and millis timer
unsigned long prevMillis = 0;
State currentState = TrafficGo;

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
void updateOled(String s) {
    oled.clear(PAGE);
    oled.setCursor(0,0);
    oled.print(s);
    oled.display();
}

// // TODO: COMPLETE updateNextState
void updateNextState() {
    /*
        where we implement the state transitions
        1) look at your current state and any inputs
        2) use logic to determine the next state to go to
        3) update your outputs based on the next state
    */

    unsigned long currMillis = millis();

    // we could is IF statements, but we'll use switch
    switch (currentState) {
        case TrafficGo:  // the same as if(currentState == TrafficGo) {...}
            // how do we go from Go to Slow (under what conditions)?
            if (currMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = currMillis;  // update timer
                currentState = TrafficSlow;
                setColor(Yellow);
                // change LED color to yellow
                updateOled("Don't Walk");
            }
            break;
        case TrafficSlow:
            if (currMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = currMillis;
                // currentState = TrafficStop;
                currentState = PedWalk;
                setColor(Red);
                // change led to red
                updateOled("Walk");
            }
            break;
        // case TrafficStop:
        case PedWalk:
            if (currMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = currMillis;
                currentState = Hold;
                setColor(Red);  // why have this is light is already Red?
                // change LED to green
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
