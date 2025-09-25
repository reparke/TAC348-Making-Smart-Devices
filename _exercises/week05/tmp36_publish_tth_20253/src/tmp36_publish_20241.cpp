
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_TMP = A5;

/*
    print the temperature every 5 seconds--> use millis

    what variables do we need to create a millis timer?
    1) global prev time
    2) global CONST interval
    3) local curr time


    ---

    TMP36 - analog input
    ADC value (0-4095) --> voltage --> cel --> fahr

    let's print the temp in C and F

    NOW publish in Cel
        create a NEW webhook (event name = cel)
        use the same initial state settings
*/
unsigned long prevMillis = 0;
const unsigned long INTERVAL = 5000;

void setup() {
    Serial.begin(9600);
    pinMode(PIN_TMP, INPUT);
}

// millis() returns what?
// current relative time since the device turned on

void loop() {
    unsigned long currMillis = millis();

    int tmpVal = analogRead(PIN_TMP);

    // float voltage = tmpVal * 3.3 / 4095;
    float voltage = float(tmpVal) / 4095 * 3.3;

    float tempC = (voltage - 0.5) / 0.01;

    float tempF = tempC * 9 / 5 + 32;

    if (currMillis - prevMillis > INTERVAL) {
        prevMillis = currMillis;
        //do stuff
        Serial.println("Cel = " + String(tempC) + ", Fahr = " + String(tempF));

        Particle.publish("fahr", String(tempF));
        Particle.publish("cel", String(tempC));
    }
}