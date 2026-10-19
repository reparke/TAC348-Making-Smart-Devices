/*
    Econ
        Idle (start on button press)
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
const int LED_BLUE_PIN = D15;  // aka MOSI pin, blue

const int SHORT_CYCLE = 2000;
const int LONG_CYCLE = 4000;

int counter = 0;  // debugging only

/*
build a state machine -- what are the steps / process?
    - way to identify state -- create enum states
    - track the current state
    - identify cycles -- enum
    - track OTHER relevant var about the system
    - design the next state logic
        - make sure to update output

what do we want to track
    - current state
    - current cycle
    - time (millis)

    (optional)
    - time remaining in state
    - switch val -
    - pot val
*/

// enum options to make changing color of RGB LED easier
enum Color { red, blue, orange, yellow, white, black };

// TODO: create enum State for states
enum State { idle, hotWash, coldWash, regularDry, extraDry };

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
    how do we turn the potVal into a Cycle?
        input: ADC 0-4095
        output: one of 3 cycles

        we are splitting 0-4095 into 3 ranges
        first range: 0 - 4095/3 (1365)
        2nd: 1365 - 2730  (4095/3   -   2 * 4095/3)
    */
    // int potVal = analogRead(POT_PIN);
    // if (potVal <= 1365) {
    //     currentCycle = economy;
    // }
    // else if (potVal > 1365 && potVal <= 2730) {
    //     currentCycle = deluxe;
    // }
    // else {
    //     currentCycle = superDeluxe;
    // }

    // alternative c++ trick
    //  input: 0-4095
    //  output: one of 3 values (0 1 2)
    int potVal = analogRead(POT_PIN);
    int mappedVal = map(potVal, 0, 4095, 0, 2);  // int that is 0 1 2

    currentCycle = Cycle(mappedVal);
}

// TODO: create void updateNextState()
// uses button inputs and current state to update global state variable
void updateNextState() {
    /*
    in general, what should happen in this function?
        - read / access / update any inputs (time, pot, switch)
        - use logic to determine our next state
        - update your outputs for for the next state (led)

        you will work in groups to implement the ECONOMY
                then finish DELUXE and SUPERDELUXE

        one note:
            beecause we have STATES and CYCLES, we can choose different way to
    build the logic

        switch on currentState          <-- this is what Rob will do
            switch on currentCycle

        OR

        swich on currentCycle
            switch on currentState
    */

    // step 1: update/access our state var
    getCyclePosition();  // update cycle -- or only do in idle?
    // update switch -- ?
    unsigned long currMillis = millis();

    switch (currentState) {
        case idle:
            int switchVal = digitalRead(SWITCH_PIN);
            if (switchVal == LOW) {
                prevMillis = currMillis;  // reset timer for next state
                switch (currentCycle) {
                    case economy:
                        currentState = coldWash;
                        setColor(blue);
                        break;
                    case deluxe:
                        currentState = hotWash;
                        setColor(red);
                        break;
                    case superDeluxe:
                        currentState = hotWash;
                        setColor(red);
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
                prevMillis = currMillis;  // reset
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
                // prevMillis = currMillis;  // do we need this?
                currentState = idle;
                setColor(white);
            }
            break;
        case extraDry:
            if (currMillis - prevMillis > LONG_CYCLE) {
                currentState = idle;
                setColor(white);
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
