#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_PIR = D2;
const int PIN_BUTTON = D10;
const int PIN_ONBOARD_LED = D7;

int count = 0;

void setup()
{
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_ONBOARD_LED, OUTPUT);

    //PIR alarm pin NEEDS a pull-up resistor
    //option1: connect 10K R from D2 to 3.3V (like button)
    //OR
    //option 2: make pinMode be INPUT_PULLUP --> photon includes an internal pull up
    // pinMode(PIN_PIR, INPUT); //but need to include actual 10K R on board

    pinMode(PIN_PIR, INPUT_PULLUP); // DONT CONNECT ACTUAL R

    Serial.begin(9600);
    
    //the PIR needs a few seconds to "read" the room
    delay(5000);
}

/*
- use a millis timer control how long the "alarm" is active

- the PIR triggers a buzzer than can only be reset with button press

    pinMode
        OUTPUT
        INPUT  -- no internal R
        INPUT_PULLUP -- connect internally a large R to 3.3v
        INPUT_PULLDOWN -- connect a large R to GND

    for the PIR, the alarm pin will be floating (neither H nor L)
    --> "pullup" the "non-alarm" signal to 3.3v 
      then when motion is detected, the signal drops to GND
*/

void loop()
{
    //PIR is a simple digital input
    int alarm = digitalRead(PIN_PIR);
    if (alarm == LOW) { // movement sensed
        Serial.println(String(count++) + " Movement detected");
        digitalWrite(PIN_ONBOARD_LED, HIGH);
    }
    else {
        //movement stopped 5-10 seconds ago (PIR has a hold time before re-arming)
        digitalWrite(PIN_ONBOARD_LED, LOW);
    }

    // delay(200); // without this, loop floods serial with thousands of messages per trigger
}