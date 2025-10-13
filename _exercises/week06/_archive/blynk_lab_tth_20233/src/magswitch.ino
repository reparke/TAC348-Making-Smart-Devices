/*
    1) Use ZeRGBa to control RGB LED on pins V0 V1 V2 (app –> argon)
    2) Use a display to show if magnetic switch is open or closed on pin V3
   (argon –> app)

   3) Use a button on V4 to trigger the RGB LED to display a color randomly
   chosen from white, yellow, magenta, red (app –> argon)
   4 When one of the four
   random colors is displayed on the RGB LED, send a string representing that
   color to the app on pin V7 (argon –> app)


*/

/*Note: This corresponds to locally installed project "Week 6", tab "Demo"
  Features
    - Button to control onboard LED on V5 (app --> argon)
    - display for random number on V6 (argon --> app)
    - virtual LED represents random value on V6 (argon --> app)
*/

/*
    the process to code data FROM APP TO ARGON and FROM ARGON TO APP are
   different!

   The process for data FROM APP TO ARGON is a little different

   EVENT DRIVEN PROGRAMMING
        we write a function that we DONT CALL
        the argon will call the function FOR US when then event happens (for
   example a button is pressed)

*/

#define BLYNK_TEMPLATE_ID "TMPL8pRjLGSG"
#define BLYNK_TEMPLATE_NAME "Week 6 Lab"
#define BLYNK_AUTH_TOKEN "CXGdYkgREo9JvRwFIZ4d8y9WCZ83Zr2b"

#define BLYNK_PRINT Serial
#define BLYNK_IP IPAddress(64, 225, 16, 22)
#include <blynk.h>

const int PIN_LED = D7;
const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15; // aka MOSI pin
const int PIN_SWITCH = D2;

int prevDoorState = HIGH;
int currDoorState = HIGH;

unsigned long prevMillis = 0;
unsigned long currMillis = 0;
const unsigned long INTERVAL_BLYNK = 1000;

void changeLedColor(int r, int g, int b) {
    // theoretical "recipe" or algorithm using these input
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

// "event handler" for virtual button presses on V5
BLYNK_WRITE(V5) {
    // param is a special variable from Blynk which contains the data being from
    // Blynk
    int virtualButtonValue =
        param.asInt();  // convert the value sent from Blynk to be a int

    digitalWrite(PIN_LED, virtualButtonValue);
    Serial.println("Virtual button press: " + String(virtualButtonValue));
}

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
void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);

    delay(5000);
    Blynk.begin(BLYNK_AUTH_TOKEN, BLYNK_IP);
}

/*
    data FROM ARGON TO APP
        - it is important that we don't slow down Blynk.run()
        - we don't want to send too many messages to Blynk too fast
        ---> when sending messages in loop() to Blynk, we should use a millis
   timer
*/

void loop() {
    Blynk.run();  // this SHOULD NOT be in the millis timer

    currMillis = millis();
    if (currMillis - prevMillis > INTERVAL_BLYNK) {
        prevMillis = currMillis;

        // to send data from argon to app, we use Blynk.virtualWrite
        int randNum = random(0, 256);
        Blynk.virtualWrite(V6, randNum);  // send randNum on virtual pin v6
        Serial.println("Random num: " + String(randNum));

        int switchVal = digitalRead(PIN_SWITCH);
        if (switchVal == HIGH) {
            Blynk.virtualWrite(V3, "open");
        } else {
            Blynk.virtualWrite(V3, "closed");
        }
    }

    // currDoorState = digitalRead(PIN_SWITCH);
    // // Serial.println(currDoorState);
    // if (currDoorState == LOW && prevDoorState == HIGH) {
    //     Serial.println("Door was closed");
    //     Blynk.virtualWrite(V3, "closed");  // send randNum on virtual pin v6
    // } else if (currDoorState == HIGH && prevDoorState == LOW) {
    //     Serial.println("Door was opened");
    //     Blynk.virtualWrite(V3, "open");  // send randNum on virtual pin v6

    // }
    // prevDoorState = currDoorState;
}
