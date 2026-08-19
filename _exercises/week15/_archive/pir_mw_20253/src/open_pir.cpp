#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUTTON = D10;
const int PIN_PIR = D2;
const int PIN_LED = D7;

int count = 0;

void setup() {
    // some of components require a PULL-UP RESISTOR
    //   ex: button, PIR
    //   so when we use the button, we connect one leg of button to 3.3v with a
    //   10k R the PIR also needs a pull-up
    //   --> we two choices:
    //       1) use a 10k resistor and connect D2 to 3.3V (like button)
    //       2) we use pinMode with INPUT_PULLUP
    //       --> don't use both 1 and 2
    pinMode(PIN_BUTTON, INPUT);
    // pinMode(PIN_PIR, INPUT);    //use this with a physical 10k resistor
    pinMode(PIN_PIR,
            INPUT_PULLUP);  // here photon includes resistance internally
    pinMode(PIN_LED, OUTPUT);

    Serial.begin(9600);
    // need to give the PIR sensor time to "read the room" and settle
    delay(5000);
}

void loop() {
    int alarm = digitalRead(PIN_PIR);
    if (alarm == LOW) {
        // LOW means motion detected
        Serial.println(String(count++) + " Motion detected");
        digitalWrite(PIN_LED, HIGH);
    } else {  // motion stopped
        digitalWrite(PIN_LED, LOW);
    }
}
