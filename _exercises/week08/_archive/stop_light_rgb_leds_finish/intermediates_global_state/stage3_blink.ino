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

// enum State { stateNSG, stateNSY, stateNSR }; //stage 2: add pedestrians
enum State { stateNSG, stateNSY, statePED, statePEDDW };  //

State currentState = stateNSG;

enum Color { Red, Yellow, Green, Black };
enum Light { lightNS, lightWE };

// for testing purposes onle
int lights[] = {PIN_NS_RED,   PIN_NS_GREEN, PIN_NS_BLUE, PIN_WE_RED,
                PIN_WE_GREEN, PIN_WE_BLUE,  PIN_WALK,    PIN_DONT_WALK};

unsigned long prevMillisBlink = 0;  // stage 3: blinking
bool isDWLedOn = true;              // controls LED blinking for don't walk

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

    /* === DEBUGGING ONLY ====== */
    //     turnAllLightsOn();
    //     delay(2000);
    //     turnAllLightsOff();
    //     cycleLights(500);
}
void setColor(Light light, Color c) {
    int r, g, b;  // load pins
    switch (light) {
        case lightNS:
            r = PIN_NS_RED;
            b = PIN_NS_BLUE;
            g = PIN_NS_GREEN;
            break;
    }
    switch (c) {
        case Red:
            digitalWrite(r, HIGH);
            digitalWrite(g, LOW);
            digitalWrite(b, LOW);
            break;
        case Yellow:
            digitalWrite(r, HIGH);
            digitalWrite(g, HIGH);
            digitalWrite(b, LOW);
            break;
        case Green:
            digitalWrite(r, LOW);
            digitalWrite(g, HIGH);
            digitalWrite(b, LOW);
            break;
        case Black:
            digitalWrite(r, LOW);
            digitalWrite(g, LOW);
            digitalWrite(b, LOW);
            break;
    }
}
// stage 1:  add
void updateLights() {
    setColor(lightNS, Black);
    setColor(lightWE, Black);
    digitalWrite(PIN_WALK, LOW);
    digitalWrite(PIN_DONT_WALK, LOW);
    switch (currentState) {  // stage 1: add switch statement
        case stateNSY:
            setColor(lightNS, Yellow);
            digitalWrite(PIN_DONT_WALK, HIGH);  // stage 2
            break;
        // case NSR:                    //stage 2
        case statePED:
            setColor(lightNS, Red);
            digitalWrite(PIN_WALK, HIGH);
            break;
        case statePEDDW:
            setColor(lightNS, Red);
            digitalWrite(PIN_DONT_WALK, HIGH);
            break;
        case stateNSG:
            setColor(lightNS, Green);
            digitalWrite(PIN_DONT_WALK, HIGH);
            break;
    }
}
/* ======== FUNCTIONS =========== */
// stage 1: create function with NSY NSR NSG
void updateNextStateDuration() {
    switch (currentState) {
        case stateNSY:
        case statePEDDW:
            stateLength = SHORT_LIGHT_DURATION;
            break;
        default:
            stateLength = LONG_LIGHT_DURATION;
    }
}
void updateNextState() {
    switch (currentState) {
        case stateNSY:
            // currentState = stateNSR; //stage 2
            currentState = statePED;
            // currentState = stateWEG;
            break;
        // case stateNSR:  //stage 2
        case statePED:  // stage 2
            // Reset the blink rate when changing OUT of PED
            // isDWLedOn = true;        //commented out--why was this here?
            currentState = statePEDDW;
            break;
        case statePEDDW:
            currentState = stateNSG;
            break;
        case stateNSG:
            currentState = stateNSY;
            break;
    }
}
void loop() {
    // stage 1: NS state changes

    unsigned long curMillis = millis();  // current time

    if ((curMillis - prevMillisState) > stateLength) {
        prevMillisState = curMillis;
        // Serial.print("Changing State: " + String(currentState));
        updateNextState();
        updateNextStateDuration();
        updateLights();
        // Serial.println(" --> " + String(currentState));
    }

    // stage 3:
    if ((curMillis - prevMillisBlink) > BLINK_RATE &&
        currentState != statePED) {
        prevMillisBlink = curMillis;

        isDWLedOn = !isDWLedOn;
        digitalWrite(PIN_DONT_WALK, isDWLedOn);
    }
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