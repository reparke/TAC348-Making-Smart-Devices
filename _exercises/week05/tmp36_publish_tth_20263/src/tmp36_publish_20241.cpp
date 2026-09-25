
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_TMP = A5;
unsigned long prevMillis = 0;
const unsigned long INTERVAL = 5000;
/*
    print the temperature in F to the serial monitor every 5 sec with millis

what var do we need to create a millis timer
    - unsigned long prevMillis (global)
    - const unsignged long INTERVAL (global CONSTANT)
    - unsigned long currMillis (local)
*/

void setup() {
    pinMode(PIN_TMP, INPUT);
    Serial.begin(9600);
}
void loop() {
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL) {
        prevMillis = currMillis;

        int tmpVal = analogRead(PIN_TMP);
        // what does tmpVal represent?  ADC value of our voltage conv
        // what is its range? [0-4095]

        /*
            tmp36 is designed to convert temp to volt

        ADC --> voltage --> tempC (via datasheet) --> tempF

        how to convert ADC to voltage?
            input: 0-4095
            output: 0-3.3v
        */
        float voltage = float(tmpVal) / 4095 * 3.3; //beware INT div

        float tempC = (voltage - 0.5) / 0.01;

        float tempF = tempC * 9 / 5 + 32;

        Serial.println("Temp in F = " + String(tempF));

        //      .publish(EVENT_NAME, EVENT_VALUE)
        Particle.publish("temperatureF", String(tempF, 1)); // ,1 changes the dec

    }
}
