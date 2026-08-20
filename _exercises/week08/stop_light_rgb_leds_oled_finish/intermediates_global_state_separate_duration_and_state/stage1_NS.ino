// cf: http://siever.info/cse132/weeks/3/studio/
// this code is adapted from Bill Siever
// two lane stoplight and pedestrian walk light

// it uses a timing approach based on cur and prevMillis
#include "SparkFunMicroOLED.h"   // Include MicroOLED library
MicroOLED oled(MODE_I2C, 9, 1);  // Example I2C declaration RST=D7, DC=LOW

const int PIN_RED = D2;
const int PIN_GREEN = D3;
const int PIN_BLUE = D4;

const int LONG_LIGHT_DURATION = 5000;   // time for green, red, walk, don't walk
const int SHORT_LIGHT_DURATION = 2000;  // time for yellow
const int BLINK_RATE = 500;             // time for blinking don't walk light

// stage 1: NS state changes
unsigned long prevMillisState = 0;
unsigned long stateDuration = 0;

enum State {
    stateTrafficGo,
    stateTrafficSlow,
    stateTrafficStop
};  // stage 2: add pedestrians

// stage 1: NS state changes
State currentState = stateTrafficGo;

enum Color { Red, Yellow, Green, Black };

void updateOLED() {
    String output = "";
    output = "Don't\nWalk";
    oled.clear(PAGE);      // Clear the display
    oled.setCursor(0, 0);  // Set cursor to top-left
    oled.setFontType(1);   // 7-segment font
    oled.print(output);    // Print "A0"
    oled.display();

    // Serial.println(output);
}

void setup() {
    Serial.begin(9600);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);

    oled.begin();     // Initialize the OLED
    oled.clear(ALL);  // Clear the display's internal memory
    oled.display();   // Display what's in the buffer (splashscreen)
    delay(1000);      // Delay 1000 ms
    oled.clear(PAGE);
    oled.display();
    /* === DEBUGGING ONLY ====== */
    //     turnAllLightsOn();
    //     delay(2000);
    //     turnAllLightsOff();
    //     cycleLights(500);
}
// stage 1: NS state changes

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
// stage 1:  add
void updateLights() {
    setColor(Black);

    switch (currentState) {  // stage 1: add switch statement
        case stateTrafficSlow:
            setColor(Yellow);
            break;
        case stateTrafficStop:
            setColor(Red);
            break;
        case stateTrafficGo:
            setColor(Green);
            break;
    }
}
/* ======== FUNCTIONS =========== */
// stage 1: create function with NSY NSR NSG
void updateNextStateDuration() {
    switch (currentState) {
        case stateTrafficSlow:
            stateDuration = SHORT_LIGHT_DURATION;
            break;
        default:
            stateDuration = LONG_LIGHT_DURATION;
    }
}
void updateNextState() {
    unsigned long curMillis = millis();
    switch (currentState) {
        case stateTrafficSlow:
            if (curMillis - prevMillisState > stateDuration) {
                prevMillisState = curMillis;

                currentState = stateTrafficStop;  // stage 1
                updateNextStateDuration();
                updateLights();
                updateOLED();
            }
            break;
        case stateTrafficStop:  // stage 1
            if (curMillis - prevMillisState > stateDuration) {
                prevMillisState = curMillis;

                currentState = stateTrafficGo;
                updateNextStateDuration();
                updateLights();
                updateOLED();
            }
            break;
        case stateTrafficGo:
            if (curMillis - prevMillisState > stateDuration) {
                prevMillisState = curMillis;

                currentState = stateTrafficSlow;
                updateNextStateDuration();
                updateLights();
                updateOLED();
            }
            break;
    }
}

void loop() {
    // have student write this because we'll need this later
    updateNextState();
}
/* ======= FUNCTIONS FOR DEBUGGING LED WIRING ========= */
// functions used for testing only
void testLightandOLED() {
    // test R, G, B LEDs individually
    int lights[] = {PIN_RED, PIN_GREEN, PIN_BLUE};

    for (int i = 0; i < arraySize(lights); i++) {
        digitalWrite(lights[i], HIGH);
        delay(1000);
        digitalWrite(lights[i], LOW);
        delay(500);
    }

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
