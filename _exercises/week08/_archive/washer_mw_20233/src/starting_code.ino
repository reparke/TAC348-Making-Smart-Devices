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

    TODO:
    X represents states and cycles with enums
    X variables to track state, cycle, and millis
    - updateNextState
        check what state we are in
        based on current conditions, decided next state
        "current conditions": current state, timer, cycle, "inputs" (pot and
switch) update to next state update any potential OUTPUTS (in our case, RGB LED)
*/

const int POT_PIN = A5;
const int SWITCH_PIN = D5;
const int LED_RED_PIN = D2;    // red
const int LED_GREEN_PIN = D3;  // green
const int LED_BLUE_PIN = D4;   // blue

const int SHORT_CYCLE = 2000;
const int LONG_CYCLE = 4000;

int counter = 0;  // debugging only

// enum options to make changing color of RGB LED easier
enum Color { Red, Blue, Orange, Yellow, White, Black };

// TODO: create enum State for states
enum State { Idle, ColdWash, HotWash, RegularDry, ExtraDry };

// TODO: create enum Cycle for cycles
enum Cycle { Economy, Deluxe, SuperDeluxe };

// TODO: create other state variables
unsigned long prevMillisState = 0;
unsigned long currMillisState = 0;
Cycle currentCycle = Economy;
State currentState = Idle;

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
    // calling this function should update our current cycle
    // pot goes 0-4095----0-1365 is econ, 1366-2730 is deluxe, and rest is
    // superdel
    int potVal = analogRead(POT_PIN);
    if (potVal >= 0 && potVal < 1366) {
        currentCycle = Economy;
    } else if (potVal >= 1366 && potVal < 2730) {
        currentCycle = Deluxe;
    } else {
        currentCycle = SuperDeluxe;
    }

    // int potVal = analogRead(POT_PIN);
    // int mappedPotVal = map(potVal, 0.0, 4095.0, 0.0, 2.0);  //test this
    // currentCycle = (Cycle)mappedPotVal;     //MINDBLOWN!
}

// TODO: create void updateNextState()
// uses button inputs and current state to update global state variable
void updateNextState() {
    //  checking current conditions (currentState, timer, inputs)
    // choosing new state and updating ouputs
    int switchVal = digitalRead(SWITCH_PIN);

    switch (currentState) {

        case Idle:  // write case for ColdWash and RegularDry
            // int switchVal = digitalRead(SWITCH_PIN);
            if ((switchVal) == LOW) {  // switch is closed!
                getCyclePosition();    // updates current cycle
                prevMillisState = millis();
                switch (currentCycle) {
                    case Economy:
                        currentState = ColdWash;
                        Serial.println("Entering Cold wash (Economy)");
                        setColor(Blue);
                        break;
                    case Deluxe:
                        currentState = HotWash;
                        Serial.println("Entering Hot wash (Deluxe)");
                        setColor(Red);
                        break;
                    case SuperDeluxe:
                        currentState = HotWash;
                        Serial.println("Entering Hot wash (Super Deluxe)");
                        setColor(Red);
                        break;
                }
            }
            break;
        case ColdWash:
            currMillisState = millis();
            if (currMillisState - prevMillisState > SHORT_CYCLE) {
                prevMillisState = currMillisState;
                currentState = RegularDry;
                Serial.println("Enter Regular Dry (Economy or Deluxe)");
                setColor(Blue);
            }

            break;
        case HotWash:
            currMillisState = millis();
            if (currMillisState - prevMillisState > SHORT_CYCLE) {
                prevMillisState = currMillisState;
                switch (currentCycle) {
                    case Deluxe:
                        currentState = RegularDry;
                        setColor(Orange);
                        Serial.println("Enter Regular Dry (Deluxe)");
                        break;
                    case SuperDeluxe:
                        currentState = ExtraDry;
                        setColor(Yellow);
                        Serial.println("Enter Extra Dry (Super Deluxe)");
                        break;
                }
            }
            break;
        case RegularDry:
            currMillisState = millis();
            if (currMillisState - prevMillisState > SHORT_CYCLE) {
                prevMillisState = currMillisState;
                currentState = Idle;
                Serial.println("Entering Idle (Economy)");
                setColor(White);
            }
            break;
        case ExtraDry:
            currMillisState = millis();
            if (currMillisState - prevMillisState > LONG_CYCLE) {
                prevMillisState = currMillisState;
                currentState = Idle;
                Serial.println("Entering idle (Super Deluxe)");
                setColor(White);
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