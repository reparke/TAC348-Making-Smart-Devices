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

unsigned long prevMillis = 0;
const unsigned long INTERVAL = 100;

// Distance thresholds in inches
const int FAR_THRESHOLD_IN = 24;  // beyond this → FAR zone
const int STOP_THRESHOLD_IN = 4;  // closer than this → STOP zone
const int MAX_RANGE_IN = 72;      // above this → treat as bad reading

// Averaging
const int NUM_READINGS = 5;
float readings[NUM_READINGS];
int readIndex = 0;

//////////////////////////
// Bar graph dimensions //
//   OLED is 64 x 48   //
//////////////////////////
const int BAR_X = 1;           // left edge of bar outline
const int BAR_Y = 40;          // top edge of bar outline
const int BAR_MAX_WIDTH = 60;  // maximum width of the fill
const int BAR_HEIGHT = 4;      // height of the fill

float readDistanceIn() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    int sensorTime = pulseIn(ECHO_PIN, HIGH);

    float distanceCm = sensorTime * SPEED_SOUND_CM / 2;
    float distanceIn = distanceCm * CM_TO_IN;

    // // v1 - simple sensor reading
    // return distanceIn;

    // // v2 - smoothing sensor reading
    // readIndex = readIndex + 1;
    // if (readIndex >= NUM_READINGS) {
    //     readIndex = 0;
    // }
    // readings[readIndex] = distanceIn;

    // float total = 0;
    // for (int i = 0; i < NUM_READINGS; i++) {
    //     total = total + readings[i];
    // }
    // return total / NUM_READINGS;

    // v3 - smoothing and rejecting of spurious or our of range
    if (distanceIn != 0 && distanceIn < MAX_RANGE_IN) {
        readings[readIndex] = distanceIn;

        readIndex = readIndex + 1;
        if (readIndex >= NUM_READINGS) {
            readIndex = 0;
        }
    }

    float total = 0;
    for (int i = 0; i < NUM_READINGS; i++) {
        total = total + readings[i];
    }
    return total / NUM_READINGS;
}

void drawDisplay(float inches) {
    oled.setCursor(0, 0);
    if (inches >= FAR_THRESHOLD_IN) {  // far
        oled.drawBitmap(yes_half_screen_bitmap);
    } else if (inches <= STOP_THRESHOLD_IN) {  // stop
        oled.drawBitmap(no_half_screen_bitmap);
        oled.setCursor(1, 30);
        oled.print(String(inches, 1) + " in");
    } else {  // near
        oled.drawBitmap(warning_half_screen_bitmap);
        oled.setCursor(1, 30);
        oled.print(String(inches, 1) + " in");
    }
}

int convertDdistanceToBarWidth(float inches) {
    // Keep the distance in the range represented by the bar.
    inches = constrain(inches, 0, FAR_THRESHOLD_IN);

    // Close object = wide bar; far object = narrow bar.
    return map(int(inches), 0, FAR_THRESHOLD_IN, BAR_MAX_WIDTH, 0);
}

void drawBar(float inches) {
    int fillWidth = convertDdistanceToBarWidth(inches);

    // BAR_X/Y place it; +2 adds a 1-pixel border on each side of the fill.
    oled.rect(BAR_X, BAR_Y, BAR_MAX_WIDTH + 2, BAR_HEIGHT + 2);

    // +1 moves inside the border; fillWidth is mapped; BAR_HEIGHT is 4 px.
    oled.rectFill(BAR_X + 1, BAR_Y + 1, fillWidth, BAR_HEIGHT);

    // Start at the fill's left edge, then move to the mapped STOP position.
    int stopX = BAR_X + 1 + convertDdistanceToBarWidth(STOP_THRESHOLD_IN);

    // line(x1, y1, x2, y2): same x makes it vertical; y extends 2 px past the bar.
    oled.line(stopX, BAR_Y - 2, stopX, BAR_Y + BAR_HEIGHT + 3);
}

void setup() {
    Serial.begin(9600);
    delay(1000);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    oled.begin();

    oled.clear(PAGE);
    oled.drawBitmap(trojan_full_screen_bitmap);
    oled.display();  // Display what's in the buffer (splashscreen)
    delay(1000);     // Delay 1000 ms
}

void loop() {
    unsigned long currMillis = millis();

    if (currMillis - prevMillis >= INTERVAL) {
        prevMillis = currMillis;

        float distanceIn = readDistanceIn();

        oled.clear(PAGE);
        drawDisplay(distanceIn);
        drawBar(distanceIn);
        oled.display();

        Serial.printlnf("Distance: %.1f in", distanceIn);
    }
}
