#define BLYNK_TEMPLATE_ID "TMPL8pRjLGSG"
#define BLYNK_DEVICE_NAME "Week 6 Lab"
#define BLYNK_AUTH_TOKEN "CXGdYkgREo9JvRwFIZ4d8y9WCZ83Zr2b"

#include <blynk.h>
#define BLYNK_IP IPAddress(64, 225, 16, 22)
#define BLYNK_PRINT Serial

unsigned long blynkDelay = 1000;
unsigned long prevMillis = 0;

const int PIN_LED = D7;
const int PIN_RED = D3;
const int PIN_GREEN = D4;
const int PIN_BLUE = D5;
const int PIN_SWITCH = D2;

// FROM APP to ARGON
// BLYNK_WRITE
BLYNK_WRITE(V0)  // red -- THIS IS A FUNCTION
{
    int r = param.asInt();
    analogWrite(PIN_RED, r);
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

// button to choose random color (white yellow magenta red)
BLYNK_WRITE(V4) {
    int buttonVal = param.asInt();  // 0 and 1

    if (buttonVal == 1) {
        int randNum = random(0, 4);  // 0 1 2 3
        if (randNum == 0) {          // white
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 255);
            Blynk.virtualWrite(V7, "white");

        } else if (randNum == 1) {  // yellow
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 0);
            Blynk.virtualWrite(V7, "yellow");
        }
        // repeat for red and magenta
    }
}

void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);

    Blynk.begin(BLYNK_AUTH_TOKEN, BLYNK_IP);
}

void loop() {
    Blynk.run();

    /* if you use latch code, you don't have to use millis here*/
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > blynkDelay) {
        prevMillis = currMillis;
        int switchVal = digitalRead(PIN_SWITCH);
        if (switchVal == HIGH) {
            Blynk.virtualWrite(V3, "open");
        } else {
            Blynk.virtualWrite(V3, "closed");
        }
    }
}