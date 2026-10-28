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

/*
    part 1) clean up the sensor reading
        -ignore bad readings
        -smooth out good readings with an average (of last 5)

    part 2) display bitmaps and distance
        - for NEAR and STOP distance, display distance in inchess on oled
        - for STOP, display X graphic
        - for NEAR, display warning graphic
        - for FAR, display yes graphic
*/

// TODO: Thresholds
// Distance thresholds in inches
const int FAR_THRESHOLD_IN = 24;  // beyond this → FAR zone
const int STOP_THRESHOLD_IN = 4;  // closer than this → STOP zone
const int MAX_RANGE_IN = 72;

const int BAR_X = 1;  // left edge of outer rect
const int BAR_Y = 40;
const int BAR_HEIGHT = 4;      // height of the FILL
const int BAR_MAX_WIDTH = 60;  // max width of FILL

// TODO: drawDisplay
void drawDisplay(float inches) {
    // we're clearing screen
    oled.setCursor(0, 0);
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

// TODO: convertDdistanceToBarWidth
// This function is a helper function that isn't streicly necessary
// but makes the code easier to read
int convertDistanceToBarWidth(float inches) {
    // keep the distnce in the range representts by the bar
    // constrain(value, MIN, MAX) --> returns value constrained by range
    float constrainedInches = constrain(inches, 0, FAR_THRESHOLD_IN);

    int width =
        map(int(constrainedInches), 0, FAR_THRESHOLD_IN, BAR_MAX_WIDTH, 0);
    // inverse relationship--smaller distance to sensor means width of bar is
    // bigger

    return width;
}

// TODO: drawBar
void drawBar(float inches) {
    int fillWidth = convertDistanceToBarWidth(inches);

    // draw outer rect
    oled.rect(BAR_X, BAR_Y, BAR_MAX_WIDTH + 2, BAR_HEIGHT + 2);

    // draw filled rect
    oled.rectFill(BAR_X + 1, BAR_Y + 1, fillWidth, BAR_HEIGHT);

    // where is the stop line?
    int xStopLine = BAR_X + 1 + convertDistanceToBarWidth(STOP_THRESHOLD_IN);

    // draw line
    oled.line(xStopLine, BAR_Y - 2, xStopLine, BAR_Y + BAR_HEIGHT + 3);
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

    // reject bad data
    if (distanceIn > 0 && distanceIn < MAX_RANGE_IN) {
        // get good input
        readings[readIndex] = distanceIn;
        readIndex = readIndex + 1;
        if (readIndex >= NUM_READINGS) {
            readIndex = 0;
        }
    }

    // smoothing
    float total = 0;
    for (int i = 0; i < NUM_READINGS; i++) {
        total = total + readings[i];
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
    float distanceIn = readDistanceIn();

    oled.clear(PAGE);
    drawDisplay(distanceIn);
    drawBar(distanceIn);
    oled.display();

    // ideally, we would have a short millis timer ~ 100-500ms
}
