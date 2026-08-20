// cf: http://siever.info/cse132/weeks/3/studio/
// this code is adapted from Bill Siever
// North-South traffic stoplight and East-West pedestrian walk light

// it uses a timing approach based on cur and prevMillis
#include "SparkFunMicroOLED.h"   // Include MicroOLED library
MicroOLED oled(MODE_I2C, 9, 1);  // Example I2C declaration RST=D7, DC=LOW

const int PIN_RED = D2;
const int PIN_GREEN = D3;
const int PIN_BLUE = D4;

const int LONG_LIGHT_DURATION = 5000;   // time for green, red, walk, don't walk
const int SHORT_LIGHT_DURATION = 2000;  // time for yellow
const int BLINK_RATE = 500;             // time for blinking don't walk light

// TODO:  Create enum State for stoplight states
// we need a variable which says are we in GO, SLOW, OR STOP state
// we like integers because it make it easy to "add 1" to next state
// we also reallly like constants because they are easy to remember
// it would also be nice if all the states were sort of grouped together
enum State { TrafficGo, TrafficSlow, TrafficStop };

// TODO: create enum Color for signal light colors
enum Color { Red, Green, Yellow, Black };

// TODO: Create variables for state change and state length
unsigned long prevMillis = 0;
unsigned long currMillis = 0;
State currentState = TrafficGo;
// because each state has a different lenght
unsigned long currentStateDuration =
    LONG_LIGHT_DURATION;  // how long are suppoed in the current state

void setup() {
    Serial.begin(9600);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);

    oled.begin();      // Initialize the OLED
    oled.clear(ALL);   // Clear the display's internal memory
    oled.display();    // Display what's in the buffer (splashscreen)
    delay(1000);       // Delay 1000 ms
    oled.clear(PAGE);  // Clear the display's internal memory
    oled.display();
}

/* ======= FUNCTIONS =========== */
// TODO: COMPLETE setColor
void setColor(Color c) {
    switch (c) {
        case Red:
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 0);
            analogWrite(PIN_BLUE, 0);
            break;
        case Green:
            analogWrite(PIN_RED, 0);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 0);
            break;
        case Yellow:
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 0);
            break;
        case Black:
            analogWrite(PIN_RED, 0);
            analogWrite(PIN_GREEN, 0);
            analogWrite(PIN_BLUE, 0);
            break;print("Welcome to TMSPC Employee Dashboard")
employees = ["pam", "vikram", "ryan", "michael"]
name = int(input("Enter employee name: "))
while name.lower() not in employees
    input("Employee not found.","\nEnter employee name: ")
if name.upper() = "VIKRAM":
    print("\t", name.Title() + ": Resigned and returned to telemarketing")
elif name.upper() == "MICHAEL":
    print("\t", name.title + ": President")
else:
    print(\t + name.title() + : " The Dream Team")
    }
}  // int x

// TODO: COMPLETE updateNextState
void updateNextState() {
    /*
    what goes into a function like this?
        will know current state
        check if the confiditon of moving to next state is met (e.g. timer)
        update any "OUTPUTS" for the next state
    */
    currMillis = millis();
    // we could use if statements...
    switch (currentState) {  // if (currentState ==)
        case TrafficGo:      // this basicallly if (currentState == TrafficGo)
            if (currMillis - prevMillis > currentStateDuration) {
                // we go from TrafficGo to TrafficSlwo
                currentState = TrafficSlow;
                Serial.println("Moving to TrafficSlow");
                currentStateDuration = SHORT_LIGHT_DURATION;
                prevMillis = currMillis;
                setColor(Yellow);

                oled.clear(PAGE);
                oled.setCursor(0, 0);
                oled.print("Don't Walk");
                oled.display();
            }
            break;
        case TrafficSlow:  // this basicallly if (currentState == TrafficGo)
            if (currMillis - prevMillis > currentStateDuration) {
                // we go from TrafficGo to TrafficSlwo
                currentState = TrafficStop;
                Serial.println("Moving to TrafficStop");
                currentStateDuration = LONG_LIGHT_DURATION;
                prevMillis = currMillis;
                setColor(Red);
                oled.clear(PAGE);
                oled.setCursor(0, 0);
                oled.print("Don't Walk");
                oled.display();
                // update OLEDSCREEN
            }
            break;
        case TrafficStop:  // this basicallly if (currentState == TrafficGo)
            if (currMillis - prevMillis > currentStateDuration) {
                // we go from TrafficGo to TrafficSlwo
                currentState = TrafficGo;
                Serial.println("Moving to TrafficGo");
                currentStateDuration = LONG_LIGHT_DURATION;
                prevMillis = currMillis;
                setColor(Green);
                oled.clear(PAGE);
                oled.setCursor(0, 0);
                oled.print("Don't Walk");
                oled.display();
                // update OLEDSCREEN
            }
            break;
    }
}

// TODO: COMPLETE updateNextStateDuration
// void updateNextStateDuration() {}

// TODO: COMPLETE updateLights
void updateLights() {}

// TODO: COMPLETE updateOLED
void updateOLED() {}

void loop() {
    // TODO: comment out this function after verifying OLED and RGB LED work
    // testLightandOLED();
    updateNextState();
}

/* ======= FUNCTIONS FOR DEBUGGING LED WIRING ========= */
// functions used for testing only
void testLightandOLED() {
    // test R, G, B LEDs individually; then white
    // int lights[] = {PIN_RED, PIN_GREEN, PIN_BLUE};

    // // turn off LED
    // for (int i = 0; i < arraySize(lights); i++) {
    //     digitalWrite(lights[i], LOW);
    // }

    // // test R G B
    // for (int i = 0; i < arraySize(lights); i++) {
    //     digitalWrite(lights[i], HIGH);
    //     delay(1000);
    //     digitalWrite(lights[i], LOW);
    //     delay(500);
    // }

    // // show white
    // for (int i = 0; i < arraySize(lights); i++) {
    //     digitalWrite(lights[i], HIGH);
    // }

    // //-----------------------

    // test OLED screen
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.setFontType(0);
    oled.println("Testing OLED");
    Serial.println("Testing oled");
    oled.display();

    oled.setFontType(0);  // 7-segment font
    for (int i = 0; i < 20; i++) {
        oled.print(".");
        oled.display();
        delay(10);
    }
    oled.clear(PAGE);  // Clear the display
    oled.display();
    delay(500);
}
