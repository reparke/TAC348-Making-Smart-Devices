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
      X create variables to track conditions / state
      X create enums for states
        updateNextState
            look at currentState and any inputs (ex: timer, button, pot, etc)
            uses logic to then make decision about next state
                changes state variable
            modify timer (if necesary) and any outputs (ex leds, or OLED output)
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
// reads potentiometer and updates currentCycle
void getCyclePosition() {
    int potVal = analogRead(POT_PIN);  // 0-4095
    if (potVal >= 0 && potVal < 1366) {
        currentCycle = Economy;
    } else if (potVal >= 1366 && potVal < 2730) {
        currentCycle = Deluxe;
    } else {
        currentCycle = SuperDeluxe;
    }
    // alternative
    // use map() to map to 0, 1, 2

    // int potVal = analogRead(POT_PIN); //0-4095
    // int mappedVal = map(potVal, 0, 4096, 0, 3);

    // int mappedVal = round(map(potVal, 0.0, 4095.0, 0.0, 2.0));

    // currentCycle = (Cycle) mappedVal;
}

// TODO: create void updateNextState()
// uses button inputs and current state to update global state variable
// look at currentState and any inputs(ex : timer, button, pot, etc)
// uses logic to then make decision about next state changes state variable
// modify
//     timer(if necesary) and
//     any outputs(ex leds, or OLED output)

void updateNextState() {
    currMillisState = millis();
    int switchVal = digitalRead(SWITCH_PIN);

    switch (currentState) {
        case Idle:
            if (switchVal == LOW) {  // switch is closed so let's start
                // read pot!
                getCyclePosition();
                prevMillisState = currMillisState;  // reset the timer
                switch (currentCycle) {
                    case Economy:
                        currentState = ColdWash;
                        Serial.println("Entering cold wash...");
                        setColor(Blue);
                        break;
                    // case Deluxe:
                    //     currentState = HotWash;
                    //     Serial.println("Enter hot wash...");
                    //     setColor(Red);
                    //     break;
                    // case SuperDeluxe:
                    //     currentState = HotWash;
                    //     Serial.println("Enter hot wash...");
                    //     setColor(Red);
                    //     break;
                    case Deluxe:
                    case SuperDeluxe:  // this is sort of like if (DELUXE OR
                                       // SUPERDELUXE)
                        currentState = HotWash;
                        Serial.println("Enter hot wash...");
                        setColor(Red);
                        break;
                }
            }
            break;
        case HotWash:
            if (currMillisState - prevMillisState > SHORT_CYCLE) {
                prevMillisState = currMillisState;
                switch (currentCycle) {
                    case Deluxe:
                        currentState = RegularDry;
                        Serial.println("Entering regular dry...");
                        setColor(Orange);
                        break;
                    case SuperDeluxe:
                        currentState = ExtraDry;
                        Serial.println("Entering extra dry...");
                        setColor(Yellow);
                        break;
                }
            }
            break;
        case ColdWash:
            if (currMillisState - prevMillisState > SHORT_CYCLE) {
                prevMillisState = currMillisState;
                currentState = RegularDry;
                Serial.println("Entering regular dry...");
                setColor(Orange);
            }
            break;
        case RegularDry:
            if (currMillisState - prevMillisState > SHORT_CYCLE) {
                // prevMillisState = currMillisState;
                currentState = Idle;
                Serial.println("Entering idle...");
                setColor(White);
            }
            break;
        case ExtraDry:
            if (currMillisState - prevMillisState > LONG_CYCLE) {
                // prevMillisState = currMillisState;
                currentState = Idle;
                Serial.println("Entering idle...");
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