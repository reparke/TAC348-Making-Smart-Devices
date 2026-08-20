/*
    Econ
        Cold 2 min
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
    Cold,       blue
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
enum State { Idle, Hot, Cold, RegularDry, ExtraDry };

// create enum Cycle for cycles
enum Cycle { Economy, Deluxe, SuperDeluxe };

// create enum Color for light colors
enum Color { Red, Blue, Orange, White, Black };

// create state variables
State currentState = Idle;
Cycle currentCycle = Economy;
unsigned long stateDuration = 0;
Color currentColor = Black;

/* ===== FUNCTIONS ====== */
// TODO: create getCyclePosition
// reads potentiometer and returns current Cycle
void getCyclePosition() {
    int val = analogRead(POT_PIN);

    if (val >= 0 && val < 1365) {  // first 1/3
        currentCycle = Economy;
    } else if (val > 1365 && val < 2730) {  // second 1/3
        currentCycle = Deluxe;
    } else {
        currentCycle = SuperDeluxe;
    }
}

// TODO: create updateNextState
// uses button inputs and current state to update global state variable
void updateNextState() {
    unsigned long curMillis = millis();

    switch (currentState) {
        case Idle:
            // make sure that switch is closed; if is switch is open, do nothing
            if (digitalRead(SWITCH_PIN) == LOW) {
                getCyclePosition();  // update cycle read
                switch (currentCycle) {
                    case Economy:
                        currentState = Cold;
                        break;
                }
                updateNextDuration();
                updateOutputs();
            }
            break;
        case Cold:
            if (curMillis - prevMillisState > stateDuration) {
                prevMillisState = curMillis;
                currentState = RegularDry;
                updateNextDuration();
                updateOutputs();
            }
            break;
        case RegularDry:
            if (curMillis - prevMillisState > stateDuration) {
                prevMillisState = curMillis;
                currentState = Idle;
                updateNextDuration();
                updateOutputs();
            }
            break;

        default:
            break;
    }
}
// TODO: create updateNextDuration
// update global state duration variable based on the current state
void updateNextDuration() {
    switch (currentState) {
        case Idle:
            stateDuration = 0;
            break;
        case Hot:
            stateDuration = LONG_CYCLE;
            break;
        case Cold:
            stateDuration = SHORT_CYCLE;
            break;
        case RegularDry:
            stateDuration = SHORT_CYCLE;
            break;
        case ExtraDry:
            stateDuration = LONG_CYCLE;
            break;
    }
}
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
        case Black:
            digitalWrite(LED_RED_PIN, LOW);
            digitalWrite(LED_GREEN_PIN, LOW);
            digitalWrite(LED_BLUE_PIN, LOW);
            break;
    }
}
// TODO: create updateOutputs
// updates LEDs based on upcoming state
void updateOutputs() {
    switch (currentState) {
        case Idle:
            setColor(White);
            break;

        case Hot:  // red
            setColor(Red);
            break;

        case Cold:  // blue
            setColor(Blue);
            break;

        case RegularDry:  // orange
            setColor(Orange);
            break;

        case ExtraDry:  // orange
            setColor(Orange);
            break;
    }
}

// LOOP
void loop() {
    updateNextState();
    // testInitialSetup();
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
/*
String displayState(State s) {
    switch (s) {
        case Idle:
            return "idle";
        case Hot:
            return "hot";
        case ExtraDry:
            return "longdry";
        case Cold:
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
