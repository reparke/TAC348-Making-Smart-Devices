/*
    Econ
        ColdWash 2 min
        RegularDry 2 min
        Idle
    Deluxe
        HotWash 2 min
        RegularDry 2 min
        Idle
    Super
        HotWash 2 min
        ExtraDry 4 min
        Idle


Colors:
    Idle        white
    HotWash     red
    ColdWash    blue
    RegularDry  orange
    ExtraDry    yellow


 green check - breakout rooms
 red x - together
*/

/*
    x way  to track states and cycles
    x way to track time
    - track state variables
    - state transition logic (updateNextState)
*/

#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int POT_PIN = A1;
const int SWITCH_PIN = D5;
const int LED_RED_PIN = A2;    // red
const int LED_GREEN_PIN = A5;  // green
const int LED_BLUE_PIN = D15;  // aka MOSI pin, blue

const int SHORT_CYCLE = 2000;
const int LONG_CYCLE = 4000;

int counter = 0;  // debugging only

// enum options to make changing color of RGB LED easier
enum Color { red, blue, orange, yellow, white, black };

// TODO: create enum State for states
enum State { idle, coldWash, hotWash, regularDry, extraDry };

// TODO: create enum Cycle for cycles
enum Cycle { economy, deluxe, superDeluxe };

// TODO: create other state variables
unsigned long prevMillis = 0;
State currentState = idle;
Cycle currentCycle = economy;

/* ===== FUNCTIONS ====== */
// changes the light color based on the enum Color value
// use this function inside of updateOutputs()
void setColor(Color c) {
    switch (c) {
        case red:
            digitalWrite(LED_RED_PIN, HIGH);
            digitalWrite(LED_GREEN_PIN, LOW);
            digitalWrite(LED_BLUE_PIN, LOW);
            break;
        case white:
            digitalWrite(LED_RED_PIN, HIGH);
            digitalWrite(LED_GREEN_PIN, HIGH);
            digitalWrite(LED_BLUE_PIN, HIGH);
            break;
        case blue:
            digitalWrite(LED_RED_PIN, LOW);
            digitalWrite(LED_GREEN_PIN, LOW);
            digitalWrite(LED_BLUE_PIN, HIGH);
            break;
        case orange:
            analogWrite(LED_RED_PIN, 255);
            analogWrite(LED_GREEN_PIN, 165);
            digitalWrite(LED_BLUE_PIN, LOW);
            break;
        case yellow:
            analogWrite(LED_RED_PIN, 255);
            analogWrite(LED_GREEN_PIN, 255);
            digitalWrite(LED_BLUE_PIN, LOW);
            break;
        case black:
            digitalWrite(LED_RED_PIN, LOW);
            digitalWrite(LED_GREEN_PIN, LOW);
            digitalWrite(LED_BLUE_PIN, LOW);
            break;
    }
}
// TODO: create void getCyclePosition()
// reads potentiometer and updates current Cycle
void getCyclePosition() {
    /*
        how do we convert from pot to cycle?
    */
    //    int potVal = analogRead(POT_PIN); // 0-4095

    //     if (potVal >= 0 && potVal < 1365) {
    //         currentCycle = economy;
    //     }
    //     else if (potVal >= 1365 && potVal < 2730) {
    //         currentCycle = deluxe;
    //     }
    //     else {
    //         currentCycle = superDeluxe;
    //     }
    int potVal = analogRead(POT_PIN);
    int mappedVal = map(potVal, 0, 4095, 0, 2);
    // currentCycle = (Cycle) mappedVal;
    currentCycle = Cycle(mappedVal);
}

// TODO: create void updateNextState()
// uses button inputs and current state to update global state variable
void updateNextState() {
    /*
        in general, what kind of things happen in state transition fn?
        1 check any inputs that are relevant to the transition logic
        2 use logic to determine the next state and update the next state var
        3 update any outputs (RGB)
    */

    int switchVal = digitalRead(SWITCH_PIN);
    getCyclePosition();  // read the current cycle
    unsigned long currMillis = millis();

    switch (currentState) {
        case idle:
            if (switchVal == 0) {
                switch (currentCycle) {
                    case economy:
                        currentState = coldWash;
                        prevMillis = currMillis;  // reset timer
                        setColor(blue);
                        break;
                    case deluxe:
                        currentState = hotWash;
                        setColor(red);
                        prevMillis = currMillis;
                        break;
                    case superDeluxe:
                        currentState = hotWash;
                        setColor(red);
                        prevMillis = currMillis;
                        break;
                }
            }
            break;
        case coldWash:
            if (currMillis - prevMillis > SHORT_CYCLE) {
                prevMillis = currMillis;
                currentState = regularDry;
                setColor(orange);
            }
            break;
        case hotWash:
            if (currMillis - prevMillis > SHORT_CYCLE) {
                prevMillis = currMillis;
                switch (currentCycle) {
                    case deluxe:
                        currentState = regularDry;
                        setColor(orange);
                        break;
                    case superDeluxe:
                        currentState = extraDry;
                        setColor(yellow);
                        break;
                }
            }
            break;
        case regularDry:
            if (currMillis - prevMillis > SHORT_CYCLE) {
                // prevmillis = currmillis; BUT no needed
                currentState = idle;
                setColor(white);
            }
            break;
        case extraDry:
            if (currMillis - prevMillis > LONG_CYCLE) {
                currentState = idle;
                setColor(white);
                // no need to reset timer
            }
            break;
    }
}

/* ============= DEBUGGING FUNCTIONS ONLY ============= */
// functions used for testing only
void testInputs() {
    String valSwitchString = digitalRead(SWITCH_PIN) ? "open" : "closed";
    int valPot = analogRead(POT_PIN);
    Serial.printlnf("Switch: %s, Pot: %d", valSwitchString.c_str(), valPot);
}
void testInitialSetup() {
    // test R, G, B LEDs individually; then white
    int lights[] = {LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN};
    // test R G B
    for (int i = 0; i < arraySize(lights); i++) {
        testInputs();
        digitalWrite(lights[i], HIGH);
        delay(1000);
        testInputs();
        digitalWrite(lights[i], LOW);
        delay(500);
    }
    // show white
    for (int i = 0; i < arraySize(lights); i++) {
        testInputs();
        digitalWrite(lights[i], HIGH);
    }
    delay(1000);
    // show black
    for (int i = 0; i < arraySize(lights); i++) {
        testInputs();
        digitalWrite(lights[i], LOW);
    }
    delay(500);
}
/*
String getStateString() {
    String output = "";
    switch (currentState) {
        case Idle:
            output = "Idle";
            break;
        case HotWash:
            output = "Hot Wash";
            break;
        case ExtraDry:
            output = "Extra Dry";
            break;
        case ColdWash:
            output = "Cold Wash";
            break;
        case RegularDry:
            output = "Regular Dry";
            break;
    }
    return output;
}

String getCycleString() {
    String output = "";
    switch (currentCycle) {
        case Economy:
            output = "Economy";
            break;

        case Deluxe:
            output = "Deluxe";
            break;

        case SuperDeluxe:
            output = "Super Deluxe";
            break;
    }
    return output;
}
void displayAllStateInfo() {
    int valPot = analogRead(POT_PIN);
    String stateString = getStateString();
    String cycleString = getCycleString();
    String output =
        "%d: %s; Cycle = %s; Duration = %d, Pot = %d, EnumState = %d, "
        "EnumCycle = %d";
    Serial.printlnf(output, counter, stateString.c_str(), cycleString.c_str(),
                    stateDuration, valPot, currentState, currentCycle);
}
*/
/* ============================================== */

void loop() {
    // this function is just for debugging
    // delete when you start to code the transitions
    // testInitialSetup();

    updateNextState();
}

void setup() {
    Serial.begin(9600);
    pinMode(SWITCH_PIN, INPUT);
    pinMode(POT_PIN, INPUT);
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_BLUE_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
}
