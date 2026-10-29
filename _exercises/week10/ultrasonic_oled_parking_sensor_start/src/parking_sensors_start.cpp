#include "Particle.h"
#include "SparkFunMicroOLED.h"

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
void drawDisplay(float inches) {}

// TODO: drawBar
void drawBar(float inches) {}

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

    return distanceIn;
}

void setup() {
    Serial.begin(9600);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    oled.begin();
    delay(1000);  // Delay 1000 ms
}

void loop() {}
