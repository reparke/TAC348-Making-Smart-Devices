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
        HotWash 4 min
        ExtraDry 4 min
        Idle


Colors:
    Idle        white
    HotWash     red
    ColdWash    blue
    RegularDry  orange
    ExtraDry    yellow

*/

const int POT_PIN = A5;
const int SWITCH_PIN = D5;
const int LED_RED_PIN = D2;    // red
const int LED_GREEN_PIN = D3;  // green
const int LED_BLUE_PIN = D4;   // blue

const int SHORT_CYCLE = 2000;
const int LONG_CYCLE = 4000;

// enum options to make changing color of RGB LED easier
enum Color { Red, Blue, Orange, Yellow, White, Black };

// TODO: create enum State for states
enum State { Idle, HotWash, ColdWash, ExtraDry, RegularDry };

// TODO: create enum Cycle for cycles
enum Cycle { Economy, Deluxe, SuperDeluxe };

// TODO: create other state variables
unsigned long prevMillisState = 0;
unsigned long currentStateDuration = 0;
Cycle currentCycle = Economy;
State currentState = Idle;

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

/* ===== FUNCTIONS ====== */
// TODO: create void getCyclePosition()
// reads potentiometer and updates current Cycle
void getCyclePosition() {
    int value = analogRead(POT_PIN);
    if (value < 1365 && value >= 0)
        currentCycle = Economy;
    else if (value >= 1365 && value < 2730)
        currentCycle = Deluxe;
    else
        currentCycle = SuperDeluxe;
}

// TODO: create void updateNextDuration()
// update global state duration variable based on the current state
void updateStateDuration() {
    switch (currentState) {
        case Idle:
            currentStateDuration = 0;  // optionaal
            break;
        case HotWash:
            switch (currentCycle) {
                case Deluxe:
                    currentStateDuration = SHORT_CYCLE;
                    break;
                case SuperDeluxe:
                    currentStateDuration = LONG_CYCLE;
                    break;
            }
            break;
        case ColdWash:
            currentStateDuration = SHORT_CYCLE;  // optionaal
            break;
        case RegularDry:
            currentStateDuration = SHORT_CYCLE;  // optionaal
            break;
        case ExtraDry:
            currentStateDuration = LONG_CYCLE;  // optionaal
            break;
    }
}

// TODO: create void updateOutputs()
// updates LEDs based on upcoming state

void updateOutputs() {
    switch (currentState) {
        case Idle:
            setColor(White);
            break;
        case HotWash:
            setColor(Red);
            break;
        case ColdWash:
            setColor(Blue);
            break;
        case RegularDry:
            setColor(Orange);
            break;
        case ExtraDry:
            setColor(Yellow);
            break;
    }
}

// TODO: create void updateNextState()
// uses button inputs and current state to update global state variable
void updateNextState() {
    unsigned long curMillis = millis();

    switch (currentState) {
        case Idle:
            if (digitalRead(SWITCH_PIN) == 0) {
                getCyclePosition();  // update global
                displayAllStateInfo();

                switch (currentCycle) {
                    case Economy:
                        currentState = ColdWash;
                        break;
                    case Deluxe:
                        currentState = HotWash;
                        break;
                    case SuperDeluxe:
                        currentState = HotWash;
                        break;
                }
                updateStateDuration();
                updateOutputs();
            }
            break;
        case HotWash:  // timed state
            if (curMillis - prevMillisState > currentStateDuration) {
                prevMillisState = curMillis;
                displayAllStateInfo();
                getCyclePosition();  // update global
                switch (currentCycle) {
                        // economy cycle is never in HotWash
                    case Deluxe:
                        currentState = RegularDry;
                        break;
                    case SuperDeluxe:
                        currentState = ExtraDry;
                        break;
                }
                updateStateDuration();
                updateOutputs();
            }
            break;
        case ColdWash:
            displayAllStateInfo();

            break;
        case RegularDry:
            if (curMillis - prevMillisState > currentStateDuration) {
                displayAllStateInfo();

                prevMillisState = curMillis;
                getCyclePosition();  // update global

                currentState = Idle;

                updateStateDuration();
                updateOutputs();
            }
            break;
        case ExtraDry:
            displayAllStateInfo();

            break;
    }
}

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

/* DEBUGGING FUNCTIONS ONLY - uncomment if you need to use them
   ========================
*/

// functions used for testing only
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

    //-----------------------
}
void testInputs() {
    String valSwitchString = digitalRead(SWITCH_PIN) ? "open" : "closed";
    int valPot = analogRead(POT_PIN);
    Serial.printlnf("Switch: %s, Pot: %d", valSwitchString.c_str(), valPot);
}
/* DEBUGGING FUNCTIONS ONLY
   ========================
*/

void displayAllStateInfo() {
    int valPot = analogRead(POT_PIN);
    String stateString = getStateString();
    String cycleString = getCycleString();

    String output =
        "%s; Cycle = %s; Duration = %d, Pot = %d, EnumState = %d, "
        "EnumCycle = %d";
    Serial.printlnf(output, stateString.c_str(), cycleString.c_str(),
                    currentStateDuration, valPot, currentState, currentCycle);
}
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
