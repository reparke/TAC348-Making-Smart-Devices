#include "Particle.h"
#include "SparkFunMicroOLED.h"
#include "bitmaps.h"

SYSTEM_THREAD(ENABLED);

//////////////////////////////////
// MicroOLED Object Declaration //
//////////////////////////////////
#define PIN_RESET 9
#define DC_JUMPER 1
MicroOLED oled(MODE_I2C, PIN_RESET, DC_JUMPER);

//////////////////////////
// Ultrasonic Sensor    //
//////////////////////////
const int TRIG_PIN = D6;
const int ECHO_PIN = D5;

const float SPEED_SOUND_CM = 0.03444;
const float CM_TO_IN = 0.393701;

// averaging
const int NUM_READINGS = 5;
float readings[NUM_READINGS];
int readIndex = 0;

// Distance thresholds in inches
const int FAR_THRESHOLD_IN = 24;  // beyond this → FAR zone
const int STOP_THRESHOLD_IN = 4;  // closer than this → STOP zone
const int MAX_RANGE_IN = 72;      // above this → treat as bad reading

/*
    part 1) clean up the sensor reading
        - ignore bad readings
        - collect sensor readings
        - smooth out good readings with an average (of last 5)

    part 2) display bitmaps and distance
        - for STOP, display X graphic and distance in inches
        - for NEAR, display warning graphic and distance in inches
        - for FAR,  display yes graphic

    part 3) display the bar
        - constrain the distance
        - convert inches to pixels
        - draw outer rectangle
        - draw fill rectangle
        - optional: draw tick line
*/

// TODO: Thresholds

// TODO: drawDisplay
void drawDisplay(float inches) {
    // not going to do oled.clear(PAGE) here
    if (inches >= FAR_THRESHOLD_IN) {
        oled.drawBitmap(yes_half_screen_bitmap);
    } else if (inches <= STOP_THRESHOLD_IN) {
        oled.drawBitmap(no_half_screen_bitmap);
        oled.setCursor(1, 30);
        oled.print(String(inches, 1) + " in");
    } else {
        oled.drawBitmap(warning_half_screen_bitmap);
        oled.setCursor(1, 30);
        oled.print(String(inches, 1) + " in");
    }
}

// TODO: drawBar
void drawBar(float inches) {
    //1) constrain the inches to be 0 - 24 inches
    // could use if...
    //or we can use constrain
    // result = constrain(value, min, max)
    int displayInches = constrain(inches, 0, 24);

    //2) convert/map our distance to pixel
    //one catch: map does NOT constrain a value
    //as the dist gets smaller, the bar width gets bigger--map inverse
    int fillWidth = map(displayInches, 0, 24, 60, 0);

    //draw the outer rect
    oled.rect(1, 40, 62, 6);

    //draw the filled rect
    oled.rectFill(2, 41, fillWidth, 4);
}

/* fn: readDistanceIn()
    returns float distance to object
    THIS FUNCTION IS ALREADY DONE FOR YOU
*/
float readDistanceIn() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    int sensorTime = pulseIn(ECHO_PIN, HIGH);

    float distanceCm = sensorTime * SPEED_SOUND_CM / 2;
    float distanceIn = distanceCm * CM_TO_IN;
    // reject bad input and smooth irregularities in readings
    if (distanceIn >= 0 && distanceIn < MAX_RANGE_IN) {
        readings[readIndex] = distanceIn;

        readIndex++;
        if (readIndex >= NUM_READINGS) {
            readIndex = 0;
        }
    }

    // averaging
    float total = 0;
    for (int i = 0; i < NUM_READINGS; i++) {
        total += readings[i];
    }

    // return distanceIn;
    return total / NUM_READINGS;
}

void setup() {
    Serial.begin(9600);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    oled.begin();
    delay(1000);  // Delay 1000 ms
}

void loop() {
    float inches = readDistanceIn();

    // we should probabaly use a millis here to slow screen redraw (30-50ms)
    oled.clear(PAGE);
    drawDisplay(inches);
    drawBar(inches);
    oled.display();
}
