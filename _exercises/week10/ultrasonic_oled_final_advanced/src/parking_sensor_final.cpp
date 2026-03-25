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

// Averaging
const int NUM_READINGS = 5;
float readings[NUM_READINGS];
int readIndex = 0;

//////////////////////////
// Bar graph dimensions //
//   OLED is 64 x 48   //
//////////////////////////
const int BAR_X = 1;   // left edge of bar outline
const int BAR_Y = 40;  // top edge of bar outline
const int BAR_W = 62;  // total width of bar outline
const int BAR_H = 6;   // height of bar outline



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
    if (distanceIn != 0) {
        // if (distanceIn <= MAX_RANGE_IN) {
            readings[readIndex] = distanceIn;
        // } else {
            // readings[readIndex] = MAX_RANGE_IN;
        // }
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

// ─── Main display function
// ────────────────────────────────────────────────────
//
// Layout (64 x 48 px):
//
//   y= 0  │ FAR / NEAR / STOP!          ← zone label
//   y=14  │ 15.0 in                      ← distance (inches)
//          │
//   y=36  ┌──────────────────────────┐  ← bar outline
//   y=46  └──────────────────────────┘
//              ^-- tick mark at STOP threshold
//
// KEY IDEA: bar fill is computed continuously from distance,
// not chosen from a fixed set of values.
//
//   map(inches, 0, FAR_THRESHOLD_IN, BAR_W, 0)
//       inches=0   → barFill = BAR_W  (full — object is right here)
//       inches=FAR → barFill = 0      (empty — object is far away)

void drawDisplay(float inches) {
    // ── Zone label ─────────────────────────────────────────────────────────

    oled.setCursor(0, 0);
    if (inches >= FAR_THRESHOLD_IN) {  // far
        oled.drawBitmap(yes_half_screen_bitmap);
    } else if (inches <= STOP_THRESHOLD_IN) {  // stop
        oled.drawBitmap(no_half_screen_bitmap);
    } else {  // near
        oled.drawBitmap(warning_half_screen_bitmap);
    }
    oled.setCursor(0, 30);
    oled.print(String(inches, 1) + " in");

}

void drawBar(float inches) {
    // Clamp before mapping so the bar never overflows its outline.
    float displayIn = inches;
    if (displayIn > FAR_THRESHOLD_IN) {
        displayIn = FAR_THRESHOLD_IN;
    }

    int barFill = map(int(displayIn), 0, FAR_THRESHOLD_IN, BAR_W - 2, 0);

    // Outline
    oled.rect(BAR_X, BAR_Y, BAR_W, BAR_H);

    // Fill (1 px inset so it sits inside the outline)
    if (barFill > 0) {
        oled.rectFill(BAR_X + 1, BAR_Y + 1, barFill, BAR_H - 2);
    }

    // Tick mark at the STOP threshold position
    int stopTickX = BAR_X + 1 + map(STOP_THRESHOLD_IN, 0, FAR_THRESHOLD_IN, BAR_W - 2, 0);
    oled.line(stopTickX, BAR_Y - 2, stopTickX, BAR_Y + BAR_H + 1);
}

void setup() {
    Serial.begin(9600);
    delay(1000);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    oled.begin();
    oled.setColor(1);
    oled.setDrawMode(0);

    oled.clear(PAGE);
    oled.drawBitmap(trojan_full_screen_bitmap);
    oled.display();  // Display what's in the buffer (splashscreen)
    delay(1000);     // Delay 1000 ms
}

void loop() {
    float distanceIn = readDistanceIn();

    oled.clear(PAGE);
    drawDisplay(distanceIn);
    drawBar(distanceIn);
    oled.display();

    Serial.printlnf("Distance: %.1f in", distanceIn);
    delay(100);
}
