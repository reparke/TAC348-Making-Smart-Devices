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
// enum State { stateTrafficGo, stateTrafficSlow, stateTrafficStop };
enum State { stateTrafficGo, stateTrafficSlow, statePedWalk, statePedDontWalk };

// TODO: create enum Color for signal light colors
State currentState = statePedDontWalk;

// TODO: Create variables for state change and state length
unsigned long prevMillisState = 0;
unsigned long currentStateDuration = 0;  // how long am I in the current state

// enum for the colors we want
enum Color { Red, Yellow, Green, Black };

//track if DW light is on or OFF
bool isDWLedOn = true;
unsigned long prevMilllisBlink = 0; //last time we blinked on or off

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

// TODO: COMPLETE updateNextState
void updateNextState() {
    unsigned long curMillis = millis();

    // switch is just a sometimes easier way to have a bunch of ifs
    switch (currentState) {
        // if currentSTate == statetrafficGo
        case stateTrafficGo:  // currently light is green
            if (curMillis - prevMillisState > currentStateDuration) {
                prevMillisState = curMillis;
                // YAY! time to change states
                // update the state
                currentState = stateTrafficSlow;
                // updste the stateduration
                updateNextStateDuration();
                // update the LED
                updateLights();
                // update the OLED
                updateOLED();
            }
            break;
        case stateTrafficSlow:  // currently light is green
            if (curMillis - prevMillisState > currentStateDuration) {
                prevMillisState = curMillis;
                // YAY! time to change states
                // update the state
                currentState = statePedWalk;
                // updste the stateduration
                updateNextStateDuration();
                // update the LED
                updateLights();
                // update the OLED
                updateOLED();
            }
            break;
        case statePedWalk:  // currently light is green
            if (curMillis - prevMillisState > currentStateDuration) {
                prevMillisState = curMillis;
                // YAY! time to change states
                // update the state
                currentState = statePedDontWalk;
                // updste the stateduration
                updateNextStateDuration();
                // update the LED
                updateLights();
                // update the OLED
                updateOLED();
            }
            break;
        case statePedDontWalk:  // currently light is green
            if (curMillis - prevMillisState > currentStateDuration) {
                prevMillisState = curMillis;
                // YAY! time to change states
                // update the state
                currentState = stateTrafficGo;
                // updste the stateduration
                updateNextStateDuration();
                // update the LED
                updateLights();
                // update the OLED
                updateOLED();
            }
            break;
    }
    if (curMillis - prevMilllisBlink> BLINK_RATE && currentState == statePedDontWalk) {
        prevMilllisBlink = curMillis; //update timer
        if (isDWLedOn == true) {
            isDWLedOn = false;
            oled.clear(PAGE);
            oled.display(); //clears the screen
        }
        else  {
            isDWLedOn = true;
            updateOLED();       //show text
        }

    }

}

// TODO: COMPLETE updateNextStateDuration
void updateNextStateDuration() {
    switch (currentState) {
        case statePedDontWalk:
            currentStateDuration = SHORT_LIGHT_DURATION;
            break;
        case stateTrafficSlow:
            currentStateDuration = SHORT_LIGHT_DURATION;
            break;

        // if currentState == slow || currentState == dontwalk
        // case statePedDontWalk:
        // case stateTrafficSlow:
        //     currentStateDuration = SHORT_LIGHT_DURATION;
        //     break;
        // else
        default:
            currentStateDuration = LONG_LIGHT_DURATION;
            break;
    }
}

// TODO: COMPLETE setColor
// "helper" function to make change the lights easier
void setColor(Color c) {
    switch (c) {
        case Red:
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_BLUE, LOW);
            digitalWrite(PIN_GREEN, LOW);
            break;
        case Yellow:
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_BLUE, LOW);
            digitalWrite(PIN_GREEN, HIGH);
            break;
        case Green:
            digitalWrite(PIN_RED, LOW);
            digitalWrite(PIN_BLUE, LOW);
            digitalWrite(PIN_GREEN, HIGH);
            break;
        case Black:
            digitalWrite(PIN_RED, LOW);
            digitalWrite(PIN_BLUE, LOW);
            digitalWrite(PIN_GREEN, LOW);
            break;
    }
}

// TODO: COMPLETE updateLights
void updateLights() {
    switch (currentState) {
        case stateTrafficGo:
            setColor(Green);
            break;
        case stateTrafficSlow:
            setColor(Yellow);
            break;
        case statePedWalk:
            setColor(Red);
            break;
        case statePedDontWalk:
            setColor(Red);
            break;
    }
}

// TODO: COMPLETE updateOLED
void updateOLED() {
    String output = "";
    switch (currentState) {
        case statePedWalk:
            output = "Walk";
            break;
        // everything is don't walk
        default:
            output = "Don't\nWalk";
            break;
    }
    oled.clear(PAGE); //clear display
    oled.setCursor(0,0); //top left
    oled.setFontType(1);
    oled.print(output);
    oled.display();

}

void loop() {
    updateNextState();

    // TODO: comment out this function after verifying OLED and RGB LED work
    // testLightandOLED();
}

/* ======= FUNCTIONS FOR DEBUGGING LED WIRING ========= */
// functions used for testing only
void testLightandOLED() {
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

    //-----------------------

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
