/*


    We will need to create a way to represent the states using enum
    We will need to track state transitions with variables for state

    We will need to control timing with millis()
    What does loop() do
        calculate new state
        output traffic signal LEDs based on state
        independently flash walk signal (later)


states
    TrafficGo, TrafficSlow, TrafficStop
    const int TRAFFIC_GO = 0
    const int TRAFFIC_SLOW = 1
    --> instead of creating a whole bunch of INT constant, lets an enum
        which is a grouped of constants


    on your own in groups, implement the new PedWalk and PedDontWalk states 
            --> add in the East/West walking

    What changes do we need to make?
        - updateNextState
        - enum
        - updateOLED
*/

// cf: http://siever.info/cse132/weeks/3/studio/
// this code is adapted from Bill Siever
// North-South traffic stoplight and East-West pedestrian walk light

#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// it uses a timing approach based on cur and prevMillis
#include "SparkFunMicroOLED.h"   // Include MicroOLED library
MicroOLED oled(MODE_I2C, 9, 1);  // Example I2C declaration RST=D7, DC=LOW

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;  // aka MOSI pin

const int LONG_LIGHT_DURATION = 5000;   // time for green, red, walk, don't walk
const int SHORT_LIGHT_DURATION = 2000;  // time for yellow
const int BLINK_RATE = 500;             // time for blinking don't walk light

// TODO:  Create enum State for stoplight states
// enum State { TrafficGo, TrafficSlow, TrafficStop };
enum State { TrafficGo, TrafficSlow, PedWalk, PedDontWalk};

// TODO: Create variables for state change and state length
State currentState = TrafficGo;
unsigned long prevMillis = 0;

// TODO: create enum Color for signal light colors
enum Color { Red, Yellow, Green, Black };

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

/* ======= FUNCTIONS =========== */
// TODO: COMPLETE setColor
void setColor(Color c) {
    switch (c) {
        case Red:
            changeLedColor(255, 0, 0);
            break;
        case Yellow:
            changeLedColor(255, 255, 0);
            break;
        case Green:
            changeLedColor(0, 255, 0);
            break;
        case Black:
            changeLedColor(0, 0, 0);
            break;
    }
}

void updateOLED() {
    String msg = "";

    // if (A || B)  or statement
    switch (currentState) {
        case TrafficGo:  // if trafficGo OR trafficSlow
        case TrafficSlow:
        case PedDontWalk:       //added
            msg = "Don't Walk";
            break;
        // case TrafficStop:
        case PedWalk:
            msg = "Walk";
            break;
    }

    // switch (currentState) {
    //     case TrafficGo:  // if trafficGo OR trafficSlow
    //         msg = "Don't Walk";
    //         break;
    //     case TrafficSlow:
    //         msg = "Don't Walk";
    //         break;
    //     case TrafficStop:
    //         msg = "Walk";
    //         break;
    // }

    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.print(msg);
    oled.display();
}
// TODO: COMPLETE updateNextState

/*
what happens in updateNextState?
    - look at current state and any inputs and millis
    - use logic (IF/switch) to determine next state
    - update next state
    - update any outputs to reflect this new state (LED and OLED)

*/
void updateNextState() {
    // reminder: we have no inputs here, but everything is timing based

    unsigned long curMillis = millis();

    /*
    lets handle each state separately
    we COULD use if statements like
        if(currentState == TrafficGo)...
    INSTEAD, lets us a switch
        SWITCH is basically and if..else if...else
    */

    switch (currentState) {
        case TrafficGo:  // same as   if(currentState == TrafficGo)
            // what causes us to change states?
            if (curMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = curMillis;
                currentState = TrafficSlow;
                setColor(Yellow);
                updateOLED();
            }

            break;  // end of this case section
        case TrafficSlow:
            if (curMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = curMillis;
                // currentState = TrafficStop;
                currentState = PedWalk;
                setColor(Red);
                updateOLED();
            }
            break;
        // case TrafficStop:
        case PedWalk:
            if (curMillis - prevMillis > LONG_LIGHT_DURATION) {
                prevMillis = curMillis;
                currentState = PedDontWalk;
                setColor(Red);
                updateOLED();
            }
            break;
        case PedDontWalk:
            if (curMillis - prevMillis > SHORT_LIGHT_DURATION) {
                prevMillis = curMillis;
                currentState = TrafficGo;
                setColor(Green);
                updateOLED();
            }
            break;
    }
}

/* ======= FUNCTIONS FOR DEBUGGING LED WIRING ========= */
// functions used for testing only
void testLightandOLED() {
    // test OLED screen
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.setFontType(0);
    oled.println("Testing\nOLED");
    oled.display();
    oled.setFontType(0);  // 7-segment font
    for (int i = 0; i < 20; i++) {
        oled.print(".");
        oled.display();
        delay(10);
    }
    //-----------------------
    // test R, G, B LEDs individually; then white
    int lights[] = {PIN_RED, PIN_GREEN, PIN_BLUE};
    // turn off LED
    for (int i = 0; i < arraySize(lights); i++) {
        digitalWrite(lights[i], LOW);
    }
    // test R G B
    for (int i = 0; i < arraySize(lights); i++) {
        digitalWrite(lights[i], HIGH);
        delay(1000);
        digitalWrite(lights[i], LOW);
        delay(500);
    }
    // show white
    for (int i = 0; i < arraySize(lights); i++) {
        digitalWrite(lights[i], HIGH);
    }
}
/* ============================================== */

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

void loop() {
    // TODO: comment out this function after verifying OLED and RGB LED work
    // testLightandOLED();
    updateNextState();
}
