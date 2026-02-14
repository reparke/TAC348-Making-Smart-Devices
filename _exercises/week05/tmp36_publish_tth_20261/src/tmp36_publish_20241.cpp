#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
    print the temp to the serial monitor every 5 seconds with millis timer

    what var do we need to create a millis timer?
    1 unsigned long prevMillis (global)
    2 unsigned long currMillis (local)
    3 const unsigned long INTERVAL (global)

    ---

TMP 36 - analog input
    ADC 0-4095 --> voltage  -->  temp Cel --> temp Fahr
*/

const int PIN_TMP = A5;

// millis
unsigned long prevMillis = 0;
const unsigned long INTERVAL = 5000;
void setup() {
    Serial.begin(9600);
    pinMode(PIN_TMP, INPUT);
}
void loop() {
    unsigned long currMillis = millis();  // current RELATIVE time

    if (currMillis - prevMillis >= INTERVAL) {
        // IMPORTANT! update timer right away
        prevMillis = currMillis;

        // int tmpVal = analogRead(PIN_TMP);  // ADC

        // // convert ADC to voltage
        // // input: 0-4095
        // // output: 0-3.3
        // //  float voltage = tmpVal / 4095 * 3.3;        //problem...? INT
        // //  dividsion float voltage = tmpVal * 3.3 / 4095;
        // float voltage = float(tmpVal) / 4095 * 3.3;

        // // conv volt to C
        // float tempC = (voltage - 0.5) / 0.01;

        // // conv C to F
        // float tempF = tempC * 9 / 5 + 32;
        int tmpVal = analogRead(PIN_TMP);

        // float voltage = tmpVal * 3.3 / 4095;
        float voltage = float(tmpVal) / 4095 * 3.3;

        float tempC = (voltage - 0.5) / 0.01;

        float tempF = tempC * 9 / 5 + 32;

        Serial.println("Temp F = " + String(tempF));
        //       .publish(EVENT_NAME, EVENT_VALUE)
        Particle.publish("temperatureF", String(tempF));
    }
}