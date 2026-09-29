#define BLYNK_TEMPLATE_ID "TMPL8pRjLGSG"
#define BLYNK_TEMPLATE_NAME "Week 6 Lab"
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
BLYNK_WRITE(V0)  // red
{
    int redVal = param.asInt();  // the rgb value sent from the app
    analogWrite(PIN_RED, redVal);
}
BLYNK_WRITE(V1)  // green
{
    int greenVal = param.asInt();  // the rgb value sent from the app
    analogWrite(PIN_GREEN, greenVal);
}
BLYNK_WRITE(V2)  // blue
{
    int blueVal = param.asInt();  // the rgb value sent from the app
    analogWrite(PIN_BLUE, blueVal);
}

// button to choose random color (white yellow magenta red)
BLYNK_WRITE(V4) {
    int buttonVal = param.asInt();

    // this function gets called when button is PRESSED and RELEASED
    if (buttonVal == 1) {  // prevent from being called twice
        int randNum = random(0, 4);
        if (randNum == 0) {  // white---change LED, and we send string to app
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 255);
            Blynk.virtualWrite(V7, "white");
        } else if (randNum ==
                   1) {  // yellow---change LED, and we send string to app
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 0);
            Blynk.virtualWrite(V7, "yellow");
        } else if (randNum ==
                   2) {  // yellow---change LED, and we send string to app
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 0);
            analogWrite(PIN_BLUE, 255);
            Blynk.virtualWrite(V7, "magenta");
        } else if (randNum ==
                   3) {  // yellow---change LED, and we send string to app
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 165);
            analogWrite(PIN_BLUE, 0);
            Blynk.virtualWrite(V7, "orange");
        }
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

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > blynkDelay) {
        prevMillis = currMillis;

        // any code that is going FROM ARGON to APP usually needs to bein a
        // millis block
        int switchVal = digitalRead(PIN_SWITCH);
        if (switchVal == HIGH) {
            Blynk.virtualWrite(V3, "open");  // from ARgon to App
        } else {
            Blynk.virtualWrite(V3, "closed");
        }
    }
}