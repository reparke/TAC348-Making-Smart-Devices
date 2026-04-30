

#include "Particle.h"

SYSTEM_MODE(MANUAL);

SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_PIR = D2;
const int PIN_LED = D7;  // onboard

int counter = 0;

void setup() {
    /*
        some components need a pullup resistor (large resistor >=10K to power)
            ex: button
        when we use the button, we connect one leg of the button to 3.3v with a
       10K resistor

        the PIR ALSO needs a pull up resistor so we have two choices
        1) use 10k resisttor and connect D2 to 3.3v (like button)
        or
        2) we use pinMode    INPUT_PULLUP

        INPUT_PULLUP internally connects the input pin to very large internal
       resistor

        so either 1) or 2) is perfectly fine, but dont use both

        BTW there is also INPUT_PULLDOWN

        General Notes
        - this is a relatively simple digital sensor
        - detects changes in heat/infrared, but not distance, size, location

        - any advanced features you will have to add with code

        ex
        - want a longer alarm time, you could use a millis
        - to adjust sensitivity, you could use a millis for how long "motion is
       detected" before you trigger alarm
    */
    pinMode(PIN_PIR, INPUT_PULLUP);  // we do NOT connect a 10K resistor
    pinMode(PIN_LED, OUTPUT);
    Serial.begin(9600);
    // need a delay to give the sensor time to "read the room" and settle
    delay(5000);
}
void loop() {
    int alarmSignal = digitalRead(PIN_PIR);

    // LOW means movement was detected
    if (alarmSignal == LOW) {
        Serial.println("Motion detected: " + String(counter++));
        digitalWrite(PIN_LED, HIGH);
    } else {  // movement stopped
        digitalWrite(PIN_LED, LOW);
    }
}

// when the photon turns on, try to be still for ~ 10 sec
//