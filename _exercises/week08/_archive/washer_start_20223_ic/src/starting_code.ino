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
enum State { Idle, HotWash, ColdWash, RegularDry, ExtraDry };

// TODO: create enum Cycle for cycles
enum Cycle { Economy, Deluxe, SuperDeluxe };

// TODO: create other state variables
unsigned long prevMillisState = 0;
Cycle currentCycle = Economy;
State currentState = Idle;
unsigned long currentStateDuration = 0;

/* ===== FUNCTIONS ====== */
// TODO: create void getCyclePosition()
// reads potentiometer and updates current Cycle
void getCyclePosition() {
    int value = analogRead(POT_PIN);
    if (value >= 0 && value < 1365) {  // economy
        currentCycle = Economy;
    } else if (value >= 1365 && value < 2730) {  // deluxe
        currentCycle = Deluxe;
    } else {
        currentCycle = SuperDeluxe;
    }
    // use map to potentiometer to 0,1,2
}

// TODO: create void updateNextDuration()
// update global state duration variable based on the current state
void updateStateDuration() {
    switch (currentState) {
        case Idle:
            currentStateDuration = 0;
            break;
        case ColdWash:
        case RegularDry:  // this is an OR operation for switch
            currentStateDuration = SHORT_CYCLE;
            break;
        case HotWash:
            if (currentCycle == Deluxe) {
                currentStateDuration = SHORT_CYCLE;
            }
            break;
    }
}

// TODO: create void updateNextState()
// uses button inputs and current state to update global state variable

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
// TODO: create void updateOutputs()
// updates LEDs based on upcoming state
void updateOutputs() {
    switch (currentState) {
        case Idle:
            setColor(White);
            break;
        case ColdWash:
            setColor(Blue);
            break;
        case RegularDry:
            setColor(Orange);
            break;
        case HotWash:
            setColor(Red);
            break;
    }
}

// use button input and the cycle value to determine our states and outputs

void updateNextState() {
    // use state in the outer swtich
    // just focus on economy cycle
    // build updateNextStaet for Economy
    // every time you transition to a new state, you should update your outputs
    // (LED)
    //      and you update your stateDuration

    unsigned long currMillis = millis();

    // start with state
    switch (currentState) {
        case Idle:
            if (digitalRead(SWITCH_PIN) == LOW) {
                // second swtich to distinguish cycle
                getCyclePosition();  // read cycle
                switch (currentCycle) {
                    case Economy:
                        currentState = ColdWash;
                        // displayAllStateInfo();
                        updateOutputs();
                        updateStateDuration();
                        break;
                    case Deluxe:
                        currentState = HotWash;
                        updateOutputs();
                        updateStateDuration();
                        break;
                }
            }

            break;
        case ColdWash:
            if (currMillis - prevMillisState > currentStateDuration) {
                prevMillisState = currMillis;
                currentState = RegularDry;
                updateOutputs();
                updateStateDuration();
            }
            break;
        case HotWash:
            if (currMillis - prevMillisState > currentStateDuration) {
                prevMillisState = currMillis;
                currentState = RegularDry;
                updateOutputs();
                updateStateDuration();
            }
            break;
        case RegularDry:
            if (currMillis - prevMillisState > currentStateDuration) {
                prevMillisState = currMillis;
                currentState = Idle;
                displayAllStateInfo();

                updateOutputs();
                updateStateDuration();
            }
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
        "%d: Cycle = %s; Pot = %d, EnumState = %d, "
        "EnumCycle = %d";
    Serial.printlnf(output, stateString.c_str(), cycleString.c_str(), valPot,
                    currentState, currentCycle);
}
