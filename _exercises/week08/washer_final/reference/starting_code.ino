/*
    Econ
        ColdWash 2 min
        RegularDry 2 min
        Idle
    Deluxe
        Hot 4 min
        RegularDry 2 min
        Idle
    Super
        Hot 4 min
        ExtraDry 4 min
        Idle
    Consider pressing button to go back to idle
    Consider using switch to be either lock (extra), or replace the button

Colors:
    Idle,       white
    Hot,        red
    ColdWash,       blue
    ExtraDry,    yellow
    RegularDry    yellow
*/

const int POT_PIN = A5;
const int SWITCH_PIN = D5;
const int LED_RED_PIN = D2;    // red
const int LED_GREEN_PIN = D3;  // green
const int LED_BLUE_PIN = D4;   // blue

const int SHORT_CYCLE = 2000;
const int LONG_CYCLE = 4000;

unsigned long prevMillisState = 0;

// create enum State for states

// create enum Cycle for cycles

// create enum Color for light colors

// create state variables

/* ===== FUNCTIONS ====== */
// TODO: create getCyclePotion
// reads potentiometer and update current Cycle

// TODO: create updateNextState
// uses button inputs and current state to update global state variable

// TODO: create updateNextDuration
// update global state duration variable based on the current state

// TODO: create updateOutputs
// updates LEDs based on upcoming state

// LOOP
void loop() { testInitialSetup(); }

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
/*
String displayState(State s) {
    switch (s) {
        case Idle:
            return "idle";
        case HotWash:
            return "hot";
        case ExtraDry:
            return "longdry";
        case ColdWash:
            return "cold";
        case RegularDry:
            return "shortdry";
    }
}

String displayCycle(Cycle c) {
    switch (c) {
        case Economy:
            return "economy";
        case Deluxe:
            return "deluxe";
        case SuperDeluxe:
            return "superdeluxe";
    }
}
*/
