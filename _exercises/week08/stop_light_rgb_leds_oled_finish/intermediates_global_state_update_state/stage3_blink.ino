
// it uses a timing approach based on cur and prevMillis
#include "SparkFunMicroOLED.h"   // Include MicroOLED library
MicroOLED oled(MODE_I2C, 9, 1);  // Example I2C declaration RST=D7, DC=LOW

const int PIN_RED = D2;
const int PIN_GREEN = D3;
const int PIN_BLUE = D4;

const int LONG_LIGHT_DURATION = 5000;   // time for green, red, walk, don't walk
const int SHORT_LIGHT_DURATION = 2000;  // time for yellow
const int BLINK_RATE = 500;             // time for blinking don't walk light

// stage 1: NS state changes
unsigned long prevMillisState = 0;
unsigned long stateDuration = 0;

// enum State { stateNSG, stateNSY, stateNSR }; //stage 2: add pedestrians
enum State { stateTrafficGo, stateTrafficSlow, statePedWalk, statePedDontWalk };

State currentState = stateTrafficGo;

enum Color { Red, Yellow, Green, Black };
void updateOLED() {
    String output = "";
    switch (currentState) {  // stage 1: add switch statement
        case stateTrafficSlow:
        case statePedDontWalk:
        case stateTrafficGo:
            output = "Don't\nWalk";
            break;
        // case NSR:                    //stage 2
        case statePedWalk:
            output = "Walk";
            break;
    }
    oled.clear(PAGE);      // Clear the display
    oled.setCursor(0, 0);  // Set cursor to top-left
    oled.setFontType(1);   // 7-segment font
    oled.print(output);    // Print "A0"
    oled.display();

    Serial.println(output);
}
unsigned long prevMillisBlink = 0;  // stage 3: blinking
bool isDWLedOn = true;              // controls LED blinking for don't walk

void setup() {
    Serial.begin(9600);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);

    oled.begin();      // Initialize the OLED
    oled.clear(ALL);   // Clear the display's internal memory
    oled.display();    // Display what's in the buffer (splashscreen)
    delay(1000);       // Delay 1000 ms
    oled.clear(PAGE);  // Clear the display
    oled.display();
}
void setColor(Color c) {
    switch (c) {
        case Red:
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_GREEN, LOW);
            digitalWrite(PIN_BLUE, LOW);
            break;
        case Yellow:
            digitalWrite(PIN_RED, HIGH);
            digitalWrite(PIN_GREEN, HIGH);
            digitalWrite(PIN_BLUE, LOW);
            break;
        case Green:
            digitalWrite(PIN_RED, LOW);
            digitalWrite(PIN_GREEN, HIGH);
            digitalWrite(PIN_BLUE, LOW);
            break;
    }
}
// stage 1:  add
void updateLights() {
    switch (currentState) {  // stage 1: add switch statement
        case stateTrafficSlow:
            setColor(Yellow);
            break;
        // case NSR:                    //stage 2
        case statePedWalk:
            setColor(Red);
            break;
        case statePedDontWalk:
            setColor(Red);
            break;
        case stateTrafficGo:
            setColor(Green);
            break;
    }
}
/* ======== FUNCTIONS =========== */
// stage 1: create function with NSY NSR NSG
void updateNextStateDuration() {
    switch (currentState) {
        case stateTrafficSlow:
        case statePedDontWalk:
            stateDuration = SHORT_LIGHT_DURATION;
            break;
        default:
            stateDuration = LONG_LIGHT_DURATION;
    }
}
void updateNextState() {
    switch (currentState) {
        case stateTrafficSlow:
            // currentState = stateNSR; //stage 2
            currentState = statePedWalk;
            // currentState = stateWEG;
            break;
        // case stateNSR:  //stage 2
        case statePedWalk:  // stage 2
            // Reset the blink rate when changing OUT of PED
            // isDWLedOn = true;        //commented out--why was this here?
            currentState = statePedDontWalk;
            break;
        case statePedDontWalk:
            currentState = stateTrafficGo;
            break;
        case stateTrafficGo:
            currentState = stateTrafficSlow;
            break;
    }
}
void loop() {
    // stage 1: NS state changes

    unsigned long curMillis = millis();  // current time

    if ((curMillis - prevMillisState) > stateDuration) {
        prevMillisState = curMillis;
        // Serial.print("Changing State: " + String(currentState));
        updateNextState();
        updateNextStateDuration();
        updateLights();
        updateOLED();

        // Serial.println(" --> " + String(currentState));
    }

    // stage 3:
    if ((curMillis - prevMillisBlink) > BLINK_RATE &&
        currentState == statePedDontWalk) {
        prevMillisBlink = curMillis;

        isDWLedOn = !isDWLedOn;
        if (isDWLedOn == false) {
            oled.clear(PAGE);  // Clear the display
            oled.display();
        } else {
            updateOLED();
        }
    }
}

/* ======= FUNCTIONS FOR DEBUGGING LED WIRING ========= */
// functions used for testing only
void testLightandOLED() {
    // test R, G, B LEDs individually
    int lights[] = {PIN_RED, PIN_GREEN, PIN_BLUE};

    for (int i = 0; i < arraySize(lights); i++) {
        digitalWrite(lights[i], HIGH);
        delay(1000);
        digitalWrite(lights[i], LOW);
        delay(500);
    }

    // test OLED screen
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.setFontType(0);
    oled.println("Testing OLED");
    oled.display();

    oled.setFontType(0);  // 7-segment font
    for (int i = 0; i < 20; i++) {
        oled.print(".");
        oled.display();
        delay(10);
    }
    oled.clear(PAGE);  // Clear the display
    oled.display();
}
