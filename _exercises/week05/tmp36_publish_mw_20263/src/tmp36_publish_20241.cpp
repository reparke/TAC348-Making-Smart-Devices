
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_TMP = A5;

/*
print the temperature to serial monitor every 5 sec with  a millis timer

what var do we need to build a simple millis timer?
    -local: unsigned long currMillis
    -global: unsigned long prevMilllis
    -GLOBAL CONST: const unsigned long INTERVAL...


*/
unsigned long prevMillis = 0;
const unsigned long INTERVAL = 5000;

void setup() {
    pinMode(PIN_TMP, INPUT);
    Serial.begin(9600);
}
void loop() {
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL) {
        prevMillis = currMillis;

        int tmpVal = analogRead(PIN_TMP); //what is this?
        /*
            --> ADC value [0-4095]
            ADC -> Voltage -> temp C -> fahr
        */

        // ADC -> voltage
        // float voltage = tmpVal / 4095 // beware of int div!! gives us 0 always
        float voltage = float(tmpVal) / 4095 * 3.3;

        float tempC = (voltage - 0.5) / 0.01;

        float tempF = tempC * 9 / 5 + 32;

        Serial.println("Temp in Fahr is " + String(tempF,1));

        // Particle.publish (EVENT_NAME, EVENT_VALUE)
        Particle.publish("temperatureF", String(tempF));
    }
}