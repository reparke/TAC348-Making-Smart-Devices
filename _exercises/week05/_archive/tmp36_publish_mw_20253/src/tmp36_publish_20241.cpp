
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_TMP = A5;

/*
    publish to cloud
        why should we care about how often we publish to cloud?
            1) we have a quota of data per month
            2) 1 message / sec limit

        whenever we publish, ALWAYS use MILLIS from now on
        and in general WE WILL NEVER USE DELAY ANYMORE


    to use millis, what variables do we need to create?
    1) global prevMillis
    2) local currMillis
    3) GLOBAL INTERVAL
*/

unsigned long prevMillis = 0;
const unsigned long INTERVAL_PUBLISH = 5000;

void setup() {
    pinMode(PIN_TMP, INPUT);
    Serial.begin(9600);
}

void loop() {
    /*
        do serial println (not publish just yet)
            inside the millis timer, print out the temp in F and C
    */
    unsigned long currMillis = millis();
    int tmpVal = analogRead(PIN_TMP);
    // ADC --> voltage --> tempC --> tempF

    /*
        step 1: ADC -> voltage
            0-4095 --> 0-3.3V
    */

    // float voltage = float(tmpVal) / 4095 * 3.3;
    float voltage = tmpVal * 3.3 / 4095;

    // convert voltage to temperature
    // datasheet says
    // 0.5 V offset and 10mV per deg C
    float tempC = (voltage - 0.5) / 0.01;

    float tempF = tempC * (9.0 / 5) + 32;

    if (currMillis - prevMillis > INTERVAL_PUBLISH) {
        prevMillis = currMillis;
        // now do stuff...
        Serial.println("Cel = " + String(tempC) + ", Fahr = " + String(tempF));

        Particle.publish("fahr", String(tempF,1));
        Particle.publish("cels", String(tempC,1));
    }

}

/*
for now, when you want to send MULTIPLE pieces of data to initial state 
we will use MULTIPlE webhooks

*/