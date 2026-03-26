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

// Distance thresholds in inches
const int FAR_THRESHOLD_IN = 24;  // beyond this → FAR zone
const int STOP_THRESHOLD_IN = 4;  // closer than this → STOP zone
const int MAX_RANGE_IN = 60;      // above this → treat as bad reading

// array for averaging
float readings[5];  // array of floats that is 5 items long
int readIndex = 0;

// bar chart values
const int BAR_X = 1; // 1 pixel
const int BAR_W = 62; //width
const int BAR_Y = 40;
const int BAR_H = 6;



// TODO: readDistance
float readDistanceIn() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    int sensorTime = pulseIn(ECHO_PIN, HIGH);

    float distanceCm = sensorTime * SPEED_SOUND_CM / 2;
    float distanceIn = distanceCm * CM_TO_IN;

    // v2 is to average out fluctuations -- create an array
    // v3 eliminate bad data
    if (distanceIn >= 0 && distanceIn <= MAX_RANGE_IN) {
        readings[readIndex] = distanceIn;  // store cur val in array
        readIndex = readIndex + 1;         // update index
        if (readIndex >= arraySize(readings)) {
            readIndex = 0;
        }
    }
    // at this point, we have an array of 5 readings
    // but we need to calc an average to return

    // use for loop to calc average
    float total = 0;
    for (int i = 0; i < arraySize(readings); i++) {
        total = total + readings[i];
    }

    return total / arraySize(readings);
    // return distanceIn;
}

// TODO: drawDisplay
void drawDisplay(float inches) {}

// TODO: drawBar
void drawBar(float inches) {
    //goal is show values from ~0 to 24 in on our bar graph
    //beyond 24 in, we don't want to display
    //--> we need to something called "CLAMPING"
    // clamping is restricting a value to set range
    //clamping is necessary because otherwise we would draw pixels outside the graph

    float clampDist = inches;
    if (clampDist > FAR_THRESHOLD_IN) { //largest value we want to display
        clampDist = FAR_THRESHOLD_IN;
    }

    // draw the outline of the bar graph    
    oled.rect(BAR_X, BAR_Y, BAR_W, BAR_H);

    //we need to calculate how much of the bar should be filled
    //let's use map
    //we are working in opposite directions
    //--> as the distance gets smaller, the barfillamt gets bigger
    int barFillAmt = map(int(clampDist), 0, FAR_THRESHOLD_IN, BAR_W - 2, 0);

    if (barFillAmt > 0) {
        oled.rectFill(BAR_X+1, BAR_Y+1, barFillAmt, BAR_H-2);
    }

}

void setup() {
    Serial.begin(9600);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    oled.begin();
    delay(1000);  // Delay 1000 ms
}

void loop() {
    float distanceIn = readDistanceIn();

    oled.clear(PAGE);
    drawBar(distanceIn);
    oled.display();

    //for ultrasonic, we need a short delay
    delay(100);
}
