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

*/

#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int POT_PIN = A1;
const int SWITCH_PIN = D5;
const int LED_RED_PIN = A2;    // red
const int LED_GREEN_PIN = A5;  // green
const int LED_BLUE_PIN = D15;   // aka MOSI pin, blue

const int SHORT_CYCLE = 2000;
const int LONG_CYCLE = 4000;

int counter = 0;  // debugging only

// enum options to make changing color of RGB LED easier
enum Color { Red, Blue, Orange, Yellow, White, Black };

// TODO: create enum State for states
enum State { Idle, HotWash, ColdWash, RegularDry, ExtraDry };

// TODO: create enum Cycle for cycles
enum Cycle { Economy, Deluxe, SuperDeluxe };

// TODO: create other state variables
unsigned long prevMillisState = 0;
unsigned long currMillisState = 0;

State currentState = Idle;
Cycle currentCycle = Economy;

/* ===== FUNCTIONS ====== */
// changes the light color based on the enum Color value
// use this function inside of updateOutputs()
void setColor(Color c) {
    switch (c) {
        case Red:
            digitalWrite(LED_RED_PIN, HIGH);
            digitalWrite(LED_GREEN_PIN, LOW);
            digitalWrite(LED_BLUE_PIN, LOW);
            break;
        case White:
            digitalWrite(LED_RED_PIN, HIGH);
            digitalWrite(LED_GREEN_PIN, HIGH);
            digitalWrite(LED_BLUE_PIN, HIGH);
            break;
        case Blue:
            digitalWrite(LED_RED_PIN, LOW);
            digitalWrite(LED_GREEN_PIN, LOW);
            digitalWrite(LED_BLUE_PIN, HIGH);
            break;
        case Orange:
            analogWrite(LED_RED_PIN, 255);
            analogWrite(LED_GREEN_PIN, 165);
            digitalWrite(LED_BLUE_PIN, LOW);
            break;
        case Yellow:
            analogWrite(LED_RED_PIN, 0);
            analogWrite(LED_GREEN_PIN, 255);
            digitalWrite(LED_BLUE_PIN, LOW);
            break;
        case Black:
            digitalWrite(LED_RED_PIN, LOW);
            digitalWrite(LED_GREEN_PIN, LOW);
            digitalWrite(LED_BLUE_PIN, LOW);
            break;
    }
}
// TODO: create void getCyclePosition()
// reads potentiometer and updates current Cycle
void getCyclePosition() {
    // pot controls the cycle
    // int potValue =
    //     analogRead(POT_PIN);  // range: 0-4095--> divide into 3 0, 1365, 2730
    // // use conditionals
    // if (potValue >= 0 && potValue < 1365) {
    //     currentCycle = Economy;
    // } else if (potValue >= 1365 && potValue < 2730) {
    //     currentCycle = Deluxe;
    // } else {
    //     currentCycle = SuperDeluxe;
    // }

    int potValue = analogRead(POT_PIN);              // 0-4095
    int mappedValue = map(potValue, 0, 4095, 0, 2);  //  mapping to 0, 1, 2
    currentCycle = (Cycle)mappedValue;  // converts int --> enum Cycle
}

// TODO: create void update\NextState()
// uses button inputs and current state to update global state variable
void updateNextState() {
    /* what in general has to happen in this function?
        1) check your inputs to state changes
            switch -> check switch
            manage timer
            check pot -> to manage cycle
        2) figure out what is the next state we go to (logic) and update
       state variable 3) update any outputs you have (e.g. LEDs, OLEDs,
       Blynk status boxes)

        NOTE: Steps 1 and 2 are not always 100% sequential
    */
    getCyclePosition();  // this will update the current cycle
    currMillisState = millis();
    switch (currentState) {
        case Idle:
            if (digitalRead(SWITCH_PIN) == 0) {  // start cycle{
                switch (currentCycle) {
                    case Economy:
                        currentState = ColdWash;
                        setColor(Blue);
                        break;
                    case Deluxe:
                        currentState = HotWash;
                        setColor(Red);
                        break;
                    case SuperDeluxe:
                        currentState = HotWash;
                        setColor(Red);
                        break;
                }
                prevMillisState = currMillisState;
            }
            break;
        case ColdWash:  // only in Economy; swtich after 2 min
            if (currMillisState - prevMillisState > SHORT_CYCLE) {
                currentState = RegularDry;
                setColor(Orange);
                prevMillisState = currMillisState;
            }
            break;
        case HotWash:
            // use IF just to show that you can
            if (currMillisState - prevMillisState > SHORT_CYCLE) {
                prevMillisState = currMillisState;
                if (currentCycle == Deluxe) {
                    currentState = RegularDry;
                    setColor(Orange);
                } else {
                    currentState = ExtraDry;
                    setColor(Yellow);
                }
            }

            break;
        case RegularDry:  // in Econ and Dxl; switch after 2 min either way
            if (currMillisState - prevMillisState > SHORT_CYCLE) {
                currentState = Idle;
                setColor(White);
                // millis doesn't matter in Idle, so it doesn't what we do to it
                // here
                prevMillisState = currMillisState;
            }
            break;
        case ExtraDry:
            if (currMillisState - prevMillisState > LONG_CYCLE) {
                currentState = Idle;
                setColor(White);
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
    Serial.printlnf(output, counter, stateString.c_str(),
cycleString.c_str(), stateDuration, valPot, currentState, currentCycle);
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
