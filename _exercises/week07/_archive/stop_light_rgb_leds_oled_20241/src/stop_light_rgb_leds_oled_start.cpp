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
const int PIN_BLUE = D15; // aka MOSI pin

const int LONG_LIGHT_DURATION = 5000;   // time for green, red, walk, don't walk
const int SHORT_LIGHT_DURATION = 2000;  // time for yellow
const int BLINK_RATE = 500;             // time for blinking don't walk light

/*
    1) set up states with ENUM
*/

// TODO:  Create enum State for stoplight states
enum State {
    trafficGo,
    trafficSlow,
    trafficStop
    // later we have to add pedestrians
};

// TODO: Create variables for state change and state length
unsigned long prevMillis = 0;
unsigned long currentStateDuration =
    0;  // how long are we in the current state for

// a var to track what state we are in NOW
State currentState = trafficStop;

// TODO: create enum Color for signal light colors
enum Color { Red, Yellow, Green, Black };

/* ======= FUNCTIONS =========== */
// TODO: COMPLETE setColor
void setColor(Color c) {
    switch (c) {
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
        case Green:
            digitalWrite(PIN_RED, LOW);
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

// TODO: COMPLETE updateNextState

void updateNextState() {
    // what are we supposed to do here?
    // takes into account the current and the timer
    //      tracks how long we are in a state, and then decides next state
    unsigned long curMillis = millis();

    switch (currentState) {
        case trafficStop:  // same as if (currentState == trafficStope)
            if (curMillis - prevMillis > LONG_LIGHT_DURATION) {
                // we have been the stop state for 5 sec
                currentState = trafficGo;  // change state
                prevMillis = curMillis;    // update timer
                setColor(Green);           // update LED
                oled.clear(PAGE);
                oled.setCursor(0, 0);
                oled.print("Traffic Go");
                oled.display();
                Serial.println("Traffic Go");
            }
            break;
        case trafficSlow:
            if (curMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = curMillis;
                currentState = trafficStop;
                setColor(Red);
                oled.clear(PAGE);
                oled.setCursor(0, 0);
                oled.print("Traffic Stop");
                oled.display();
                Serial.println("Traffic Stop");
            }
            break;
        case trafficGo:
            if (curMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = curMillis;
                currentState = trafficSlow;
                setColor(Yellow);
                oled.clear(PAGE);
                oled.setCursor(0, 0);
                oled.print("Traffic Slow");
                oled.display();
                Serial.println("Traffic Slow");
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
