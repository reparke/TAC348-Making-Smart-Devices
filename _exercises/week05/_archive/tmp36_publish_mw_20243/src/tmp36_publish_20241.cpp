#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_TMP = A5;  // A4 is also S4

// build a publish timer
unsigned long prevMillis = 0;
const unsigned long INTERVAL_PUBLISH = 2000;

void setup() {
    pinMode(PIN_TMP, INPUT);
    Serial.begin(9600);
}
void loop() {
    int tmp36Val = analogRead(PIN_TMP);

    /*
      what is this reading?
        ideally we want the voltage
        BUT analogread always gives an ADC value 0-4095

        convert this ADC reading to a temperature

        we have ADC value AND we have a conversion fn from Volts -> temp

        ADC -> volts -> tempC -> tempF
    */

    // is voltage in INT or FLOAT?
    float voltage = tmp36Val * 3.3 / 4095;  // we have volts

    // 0.5 v offset, and 10mv for 1 deg C
    float tempC = (voltage - 0.5) / 0.01;
    float tempF = tempC * (9.0 / 5) + 32;

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL_PUBLISH) {
        prevMillis = currMillis;
        Serial.println("Temp in F = " +
                       String(tempF, 1));  // use String to limit decimal places
        // event name needs to match our webhook/integration "event name"
        Particle.publish("temperature", String(tempF, 1));
        //      .publish(EVENT_NAME,    EVENT_VALUE     )
    }
}
