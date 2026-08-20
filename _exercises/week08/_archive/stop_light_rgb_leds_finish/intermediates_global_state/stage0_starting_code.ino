// cf: http://siever.info/cse132/weeks/3/studio/
// this code is adapted from Bill Siever
// two lane stoplight and pedestrian walk light

// it uses a timing approach based on cur and prevMillis

const int PIN_NS_RED = D2;
const int PIN_NS_GREEN = D3;
const int PIN_NS_BLUE = D4;
const int PIN_WE_RED = A5;
const int PIN_WE_GREEN = A4;
const int PIN_WE_BLUE = A3;
const int PIN_DONT_WALK = D5;
const int PIN_WALK = D6;

const int LONG_LIGHT_DURATION = 5000;          // time for green, red, walk, don't walk
const int SHORT_LIGHT_DURATION = 2000;  // time for yellow
const int BLINK_RATE = 500;        // time for blinking don't walk light

// stage 1: NS state changes
unsigned long prevMillisState = 0;
unsigned long stateLength = 0;

// Create enum State for stoplight states

// create enum Color for signal light colors

// create num Light for distinguishing north-south light and west-east light

// for testing purposes only
int lights[] = {PIN_NS_RED,   PIN_NS_GREEN, PIN_NS_BLUE, PIN_WE_RED,
                PIN_WE_GREEN, PIN_WE_BLUE,  PIN_WALK,    PIN_DONT_WALK};

void setup() {
    Serial.begin(9600);
    pinMode(PIN_NS_RED, OUTPUT);
    pinMode(PIN_NS_GREEN, OUTPUT);
    pinMode(PIN_NS_BLUE, OUTPUT);
    pinMode(PIN_WE_RED, OUTPUT);
    pinMode(PIN_WE_GREEN, OUTPUT);
    pinMode(PIN_WE_BLUE, OUTPUT);
    pinMode(PIN_WALK, OUTPUT);
    pinMode(PIN_DONT_WALK, OUTPUT);
}

/* ======= FUNCTIONS =========== */

// TODO: COMPLETE updateNextState
void updateNextState() {}

// TODO: COMPLETE updateNextStateDuration
void updateNextStateDuration() {}

// TODO: COMPLETE setColor
void setColor() {}

// TODO: COMPLETE updateLights
void updateLights() {}

// LOOP
void loop() {
    // test all lights -- delete once wiring is verified
    turnAllLightsOn();
    delay(2000);
    turnAllLightsOff();
    cycleLights(500);
}

/* ======= FUNCTIONS FOR DEBUGGING LED WIRING ========= */
// functions used for testing only
void cycleLights(int delayMS) {
    for (int i = 0; i < arraySize(lights); i++) {
        digitalWrite(lights[i], HIGH);
        delay(delayMS);
        digitalWrite(lights[i], LOW);
    }
}

void turnAllLightsOn() {
    for (int i = 0; i < arraySize(lights); i++) {
        digitalWrite(lights[i], HIGH);
    }
}

void turnAllLightsOff() {
    for (int i = 0; i < arraySize(lights); i++) {
        digitalWrite(lights[i], LOW);
    }
}