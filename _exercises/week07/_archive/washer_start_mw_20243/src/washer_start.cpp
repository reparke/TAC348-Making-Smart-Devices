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

/*
    - way to represent states and cycles
    - way to track timing
    - track state variables
    - updateNextState fn
        -logic for next state
        -update timing
        -update outputs
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
enum Color { Red, Blue, Orange, Yellow, White, Black };

// TODO: create enum State for states
enum State { idle, hotWash, coldWash, regularDry, extraDry };

// TODO: create enum Cycle for cycles
enum Cycle { economy, deluxe, superDeluxe };

// TODO: create other state variables
unsigned long prevMillisState = 0;
unsigned long currMillisState = 0;
// what var do we need to represent what is happening currently in our system /
// device?
//  time for each state
//  switch open or closed -
State currentState = idle;
// Cycle currentCycle = economy;
Cycle currentCycle;

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
            analogWrite(LED_RED_PIN, 255);
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
    // how to convert pot value to cycle?
    //  divide 4095 / 3 and break into 3 intervals
    //  int potVal = analogRead(POT_PIN);

    // if (potVal >= 0 && potVal < 1365) {
    //     currentCycle = economy;
    // }
    // else if (potVal >= 1365 && potVal < 2730) {
    //     currentCycle = deluxe;
    // }
    // else {
    //     currentCycle = superDeluxe;
    // }

    int potVal = analogRead(POT_PIN);
    int mappedVal = map(potVal, 0, 4095, 0, 2);
    currentCycle = (Cycle)mappedVal;  // poof! convert potVal to Cycle
}

// TODO: create void updateNextState()
// uses button inputs and current state to update global state variable
void updateNextState() {
    /*
        what (in general) has to happen in this function?
        - check the pot -> determine cycle
        - check the switch / door -> determine if we start
        - check the timer
    */
    getCyclePosition();  // update the global var for cycle
    int switchVal = digitalRead(SWITCH_PIN);
    currMillisState = millis();

    // inputs: time, switch, and cycle
    switch (currentState) {
        case idle:
            if (switchVal == 0) {  // if door closed, then start cycle
                switch (currentCycle) {
                    case economy:
                        currentState = coldWash;
                        setColor(Blue);
                        break;
                    case deluxe:
                        currentState = hotWash;
                        setColor(Red);
                        break;
                    case superDeluxe:
                        currentState = hotWash;
                        setColor(Red);
                        break;
                }
                prevMillisState =
                    currMillisState;  // update timer when we finally leave idle
            }
            break;
        case coldWash:
            if (currMillisState - prevMillisState > SHORT_CYCLE) {
                prevMillisState = currMillisState;
                currentState = regularDry;
                setColor(Orange);
            }
            break;
        case hotWash:
            if (currMillisState - prevMillisState > SHORT_CYCLE) {
                prevMillisState = currMillisState;
                switch (currentCycle) {
                    case deluxe:
                        currentState = regularDry;
                        setColor(Orange);
                        break;
                    case superDeluxe:
                        currentState = extraDry;
                        setColor(Yellow);
                        break;
                }
            }
            break;
        case regularDry:
            if (currMillisState - prevMillisState > SHORT_CYCLE) {
                prevMillisState = currMillisState;
                currentState = idle;
                setColor(White);
            }
            break;
        case extraDry:
            if (currMillisState - prevMillisState > LONG_CYCLE) {
                prevMillisState = currMillisState;
                currentState = idle;
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
