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
const int LED_BLUE_PIN = D15;  // aka MOSI pin, blue

const int SHORT_CYCLE = 2000;
const int LONG_CYCLE = 4000;

int counter = 0;  // debugging only

/*
    X track states and cycles
    x track timing
    - track any state variables
    - build state transition logic
*/

// enum options to make changing color of RGB LED easier
enum Color { red, blue, orange, yellow, white, black };

// TODO: create enum State for states
enum State { idle, hotWash, coldWash, regularyDry, extraDry };

// TODO: create enum Cycle for cycles
enum Cycle { economy, deluxe, superDeluxe };

// TODO: create other state variables
unsigned long prevMillis = 0;
// what other variables do we need to represent our system at any given moment?
State currentState = idle;
Cycle currentCycle = economy;
int switchVal = HIGH;

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
        converts from pot value to Cycle

        how do we convert pot value to Cycle?

        --> break up range of pot value into cycles
        pot: 0-4095
        three cycles
    */
    // int potVal = analogRead(POT_PIN);
    // if (potVal >= 0 && potVal < 1365) {
    //     currentCycle = economy;
    // } else if (potVal >= 1365 && potVal < 2730) {
    //     currentCycle = deluxe;
    // } else {
    //     currentCycle = superDeluxe;
    // }

    // alternate way
    //? is there another way to convert one range to another?
    // map!
    int potVal = analogRead(POT_PIN);
    int mappedVal = map(potVal, 0, 4095, 0, 2);  // mappedVal is 0  1  2
    currentCycle = Cycle(mappedVal);
}

// TODO: create void updateNextState()
// uses button inputs and current state to update global state variable
void updateNextState() {
    /*
    in general, what kinds of things should we be doing here in this function
        1 check current time and check switch and pot (cycle)
        2 use logic (switch) to determine the next state; and update the next
    state 3 update any outputs (led)
    */

    switchVal = digitalRead(SWITCH_PIN);
    getCyclePosition();  // read pot and update Cycle
    unsigned long currMillis = millis();

    // transition logic
    // implement the economy cycle
    // hint: SWITCH
    //      use currentState for outer/first switch

    switch (currentState) {
        case idle:
            if (switchVal == 0) {
                switch (currentCycle) {
                    case economy:
                        currentState = coldWash;
                        setColor(blue);
                        prevMillis = currMillis;
                        break;
                    case deluxe:
                        currentState = hotWash;
                        setColor(red);
                        prevMillis = currMillis;
                        break;
                    case superDeluxe:
                        setColor(red);
                        currentState = hotWash;
                        prevMillis = currMillis;
                        break;
                }
            }
            break;
        case coldWash:
            if (currMillis - prevMillis > SHORT_CYCLE) {
                currentState = regularyDry;
                setColor(orange);
                prevMillis = currMillis;
            }
            break;
        case hotWash:
            if (currMillis - prevMillis > SHORT_CYCLE) {
                prevMillis = currMillis;
                switch (currentCycle) {
                    case deluxe:
                        currentState = regularyDry;
                        setColor(orange);
                        break;
                    case superDeluxe:
                        currentState = extraDry;
                        setColor(yellow);
                        break;
                }
            }
            break;
        case regularyDry:
            if (currMillis - prevMillis > SHORT_CYCLE) {
                currentState = idle;
                setColor(white);
                // prevMillis = currMillis; //don't need to do this
            }
            break;
        case extraDry:
            if (currMillis - prevMillis > LONG_CYCLE) {
                setColor(white);
                currentState = idle;
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

// enum Food { tacos, chips, pizza, broccoli };

// enum Food { tacos = 9, chips = 2, pizza = 1, broccoli = -5000 };

// enum Food { tacos = -10, chips, pizza, broccoli };
