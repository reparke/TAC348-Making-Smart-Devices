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
// enum State { TrafficGo, TrafficSlow, TrafficStop };
enum State { TrafficGo, TrafficSlow, PedWalk, PedDontWalk };

// TODO: Create variables for state change and state length
unsigned long prevMillis = 0;
unsigned long currMillis = 0;
// State currentState = TrafficStop;
State currentState = PedDontWalk;

// TODO: create enum Color for signal light colors
enum Color { Red, Green, Yellow, Black };

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
        case Black:
            digitalWrite(PIN_RED, LOW);
            digitalWrite(PIN_GREEN, LOW);
            digitalWrite(PIN_BLUE, LOW);
            break;
    }
}

// TODO: COMPLETE updateNextState
void updateNextState() {
    // checks current state decides what to do next and does
    //      checks time, if statement
    //      how we determine what to do next is based
    //                  currentState, time, and possible inputs like buttons,
    //                  etc
    currMillis = millis();
    switch (currentState) {  // if statement using current
        case TrafficGo:      // same as if (currentState == TrafficGO) { }
            if (currMillis - prevMillis > LONG_LIGHT_DURATION) {
                // update timer, update state, change RGB color
                prevMillis = currMillis;
                currentState = TrafficSlow;
                setColor(Yellow);
                Serial.println("Entering TrafficSlow");
                // show oled
                oled.clear(PAGE);
                oled.setCursor(0, 0);
                oled.print("Don't Walk");
                oled.display();
            }
            break;
        case TrafficSlow:
            if (currMillis - prevMillis > SHORT_LIGHT_DURATION) {
                // update timer, update state, change RGB color
                prevMillis = currMillis;
                // currentState = TrafficStop;
                currentState = PedWalk;
                setColor(Red);
                // Serial.println("Enter TrafficStop");
                Serial.println("Enter PedWalk");
                oled.clear(PAGE);
                oled.setCursor(0, 0);
                oled.print("Walk");
                oled.display();
            }
            break;
        case PedWalk:
            if (currMillis - prevMillis > LONG_LIGHT_DURATION) {
                // update timer, update state, change RGB color
                prevMillis = currMillis;
                currentState = PedDontWalk;
                setColor(Red);
                Serial.println("Enter PedDontWalk");
                oled.clear(PAGE);
                oled.setCursor(0, 0);
                oled.print("Don't Walk");
                oled.display();
            }
            break;
        case PedDontWalk:
            if (currMillis - prevMillis > SHORT_LIGHT_DURATION) {
                // update timer, update state, change RGB color
                prevMillis = currMillis;
                currentState = TrafficGo;
                setColor(Green);
                Serial.println("Enter TrafficGo");
                oled.clear(PAGE);
                oled.setCursor(0, 0);
                oled.print("Don't Walk");
                oled.display();
            }
            break;
            // case TrafficStop:
            //     if (currMillis - prevMillis > LONG_LIGHT_DURATION) {
            //         // update timer, update state, change RGB color
            //         prevMillis = currMillis;
            //         currentState = TrafficGo;
            //         setColor(Green);
            //         Serial.println("Enter TrafficGo");
            //         oled.clear(PAGE);
            //         oled.setCursor(0, 0);
            //         oled.print("Don't Walk");
            //         oled.display();
            //     }
            //     break;
    }
}

void loop() { updateNextState(); }

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
