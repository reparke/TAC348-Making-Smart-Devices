#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);
const int PIN_TMP = A5;

void setup() {
    pinMode(PIN_TMP, INPUT);
    Serial.begin(9600);
}

// read the tmp36, do some conversions, then print temp in fahr and temp in cel
/*
      ACD -> volts --> cel --> fahr
*/

// now, let's publish celsius data to initial state
//  let's use a millis timer to publish only every 5 seconds
/*
    millis timer
    - GLOBAL prevmillis
    - GLOBAL CONST interval
    - LOCAL curMillis
*/
unsigned long prevMillis = 0;
const unsigned long INTERVAL_PUBLISH = 5000;

void loop() {
    // what is the range of this val? ADC val from 0 - 4095
    int tmpVal = analogRead(PIN_TMP);

    // float voltage = tmpVal * 3.3 / 4095;

    // what's wrong with this?
    float voltage = float(tmpVal) / 4095 * 3.3;

    // 0.5 V offset and 10 mV / deg C --> 10 mV = 0.01 v
    float tempC = (voltage - 0.5) / 0.01;
    float tempF = tempC * 9 / 5 + 32;

    Serial.println("Temp C = " + String(tempC) + ", Temp F = " + String(tempF));

    // millis publish timer
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > INTERVAL_PUBLISH) {
        prevMillis = curMillis;  // update

        Particle.publish(
            "temperatureC",
            String(tempC, 1));  // temperatureC is the webhook we just built

        // Particle.publish("temperatureF", String(tempF, 1));
    }
}

// REMEMBER! we have a limited quota for Particle Cloud
// so don't leave device publishing for days