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

// Averaging
// float readings[5];  //create an array with 5 items
const int NUM_READINGS = 5;
float readings[NUM_READINGS];  //create an array with 5 items
int readIndex = 0;  //rotating index for the next dist value

/*
    Thought experiment:
        what is the effect of making the array bigger or smaller?
            -computation time
            -larger does more smoother but takes longer to see change (more lag)

*/

// bar graph
const int BAR_X = 1; //left edge of the rect outline
const int BAR_Y = 40; //top edge of the rect outline
const int BAR_H = 6; //height of bar
const int BAR_W = 62; //width of bar

// TODO: Thresholds
const int STOP_THRESHOLD = 4; //closer than 4 in --> stop
const int FAR_THRESHOLD = 24; //greater than this we call FAR
const int MAX_RANGE = 72;   //semi arbitrary--anything beyond is "bad data"

// TODO: drawDisplay
// draw the graphic, and the inch display

/*
    display a graphic and the distance
    if range is far away,
        just display yes_half_screen
    if range in stop / danger zone
        display no_half_screen bitmap
        AND print the distance
    otherwise
        display warning_half_screen
        AND the distance\

    bitmaps will always show up at 0,0  coordinates
    distance will show up at 1,30 coordinate

    go back to https://javl.github.io/image2cpp/ and convert these three images
*/
void drawDisplay(float inches) {
    if(inches >= FAR_THRESHOLD) {
        oled.drawBitmap(yes_half_screen_bitmap);
    }
    else if (inches <= STOP_THRESHOLD) {
        oled.drawBitmap(no_half_screen_bitmap);
        oled.setCursor(1,30);
        oled.print(String(inches, 1) + " in");
    } 
    else {
        oled.drawBitmap(warning_half_screen_bitmap);
        oled.setCursor(1, 30);
        oled.print(String(inches, 1) + " in");
    }
}

// TODO: drawBar
void drawBar(float inches) {
    // step draw rect outline
    // step calc how full the bar should be
    // step draw fill rect

    //draw outline rect
    oled.rect(BAR_X, BAR_Y, BAR_W, BAR_H);

    // figure out how full the rect should be
    // first we need to CLAMP the distance --> force dist to be [0, FAR_THRESHOLD]
    if (inches > FAR_THRESHOLD) {
        inches = FAR_THRESHOLD;
        //we could also clamp to zero, but dist will never be less than 0 anyways
    }

    int barFill = map(int(inches), 0, FAR_THRESHOLD, BAR_W-2, 0);

    //draw the inner rect
    if (barFill > 0) {
        oled.rectFill(BAR_X+1, BAR_Y+1, barFill, BAR_H-2);
    }

}

/* fn: readDistanceIn
    returns float distance to object
*/
// part 1: how to implement averaging / smoothing for sensor data
float readDistanceIn() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    int sensorTime = pulseIn(ECHO_PIN, HIGH);

    float distanceCm = sensorTime * SPEED_SOUND_CM / 2;
    float distanceIn = distanceCm * CM_TO_IN;

    // step: reject bad data
    if (distanceIn >=0 && distanceIn <= MAX_RANGE)  {
        // step: store a value in array each time through
        readings[readIndex] = distanceIn;
        readIndex++;   // readIndex = readIndex + 1; or increment
        if (readIndex >= arraySize(readings)){
            readIndex = 0;
        }
    }

    //step: calculate average
    float total = 0;
    for (int i = 0; i < arraySize(readings); i++) {
        total = total + readings[i];
    }

    return total / arraySize(readings);
    // return distanceIn;
}



void setup() {
    Serial.begin(9600);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    oled.begin();
    oled.clear(PAGE);
    oled.drawBitmap(usc_full_screen);
    oled.display();
    delay(100);  // Delay 1000 ms
}

void loop() {
    float distanceIn = readDistanceIn(); 
    Serial.println("Distance: " + String(distanceIn, 2));

    oled.clear(PAGE);
    drawDisplay(distanceIn);
    drawBar(distanceIn);
    oled.display()

    delay(100); //millis would be ideal
}
