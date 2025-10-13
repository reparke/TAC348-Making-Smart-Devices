/* after adding template,
1) install library
2) add our specific template #define from Blynk website
3) add your pin labels and pinMode to start project

*/

// #define BLYNK_TEMPLATE_ID "TMPL2DjDqQPQy"
// #define BLYNK_TEMPLATE_NAME "Week 6 Lab"
// #define BLYNK_AUTH_TOKEN "vRVkQMgZuFaijvqsHcCNW06KA9jdEm_z"

#define BLYNK_TEMPLATE_ID "TMPL8pRjLGSG"
#define BLYNK_TEMPLATE_NAME "Week 6 Lab"
#define BLYNK_AUTH_TOKEN "CXGdYkgREo9JvRwFIZ4d8y9WCZ83Zr2b"

#define BLYNK_PRINT Serial  // this is optional
#include <blynk.h>

const int PIN_LED = D7;
const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15; // aka MOSI pin
const int PIN_SWITCH = D2;

// From Argon to App: Blynk.virtualWrite
// but be careful not to send too often
int prevSwitchState = HIGH;
int currSwitchState = HIGH;

unsigned long prevMillis = 0;
unsigned long currMillis = 0;
const unsigned long INTERVAL_BLYNK = 1000;

// FROM APP to ARGON
// BLYNK_WRITE
void changeLedColor(int r, int g, int b) {
    // theoretical "recipe" or algorithm using these input
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}
BLYNK_WRITE(V0)  // red -- THIS IS A FUNCTION
{
    int r = param.asInt();
    analogWrite(PIN_RED, r);
    Serial.println("Red: " + String(r));
}
BLYNK_WRITE(V1)  // green
{
    int g = param.asInt();
    analogWrite(PIN_GREEN, g);
}
BLYNK_WRITE(V2)  // blue
{
    int b = param.asInt();
    analogWrite(PIN_BLUE, b);
}
BLYNK_WRITE(V4) {
    int buttonVal = param.asInt();  // 0 and 1

    if (buttonVal == 1) {
        int randNum = random(0, 4);  // 0 1 2 3
        if (randNum == 0) {          // white
            changeLedColor(255, 255, 255);
            Blynk.virtualWrite(V7, "white");
            Serial.print("Showing white");

        } else if (randNum == 1) {  // yellow
            changeLedColor(255, 255, 0);
            Blynk.virtualWrite(V7, "yellow");
            Serial.print("Showing white");

        } else if (randNum == 2) {  // magenta
            changeLedColor(255, 0, 255);
            Blynk.virtualWrite(V7, "magenta");
            Serial.print("Showing magenta");
        } else if (randNum == 3) {  // yellow
            changeLedColor(255, 0, 0);
            Blynk.virtualWrite(V7, "red");
            Serial.print("Showing red");
        }
    }
}
/*
    user presses Blynk button, which causes argon to do the following
        - randomly pick a color white, yellow, magenta, or red
        - display that color on the RGB
        - send the string of that color back to the app
*/

void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);

    delay(5000);
    Blynk.begin(BLYNK_AUTH_TOKEN);
}

void loop() {
    Blynk.run();

    currMillis = millis();
    if (currMillis - prevMillis > INTERVAL_BLYNK) {
        prevMillis = currMillis;
    }

    currSwitchState = digitalRead(PIN_SWITCH);

    if (currSwitchState == LOW && prevSwitchState == HIGH) {
        Serial.println("Door closed");
        Blynk.virtualWrite(V3, "closed");

    } else if (currSwitchState == HIGH && prevSwitchState == LOW) {
        // switch open
        Serial.println("Door opened");
        Blynk.virtualWrite(V3, "opened");
    } else {
        // HIGH HIGH or LOW LOW
        // we ignore this
    }

    prevSwitchState = currSwitchState;

    // currSwitchState = digitalRead(PIN_SWITCH);
    // if (currSwitchState == HIGH) {
    //     Blynk.virtualWrite(V3, "closed");
    // }
    // else {
    //     Blynk.virtualWrite(V3, "opened");
    // }
}
