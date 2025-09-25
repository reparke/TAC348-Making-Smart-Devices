#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_TMP = A5;

//millis timer
unsigned long prevMillis = 0;
const unsigned long INTERVAL_TEMP = 2000;

void setup() {
    pinMode(PIN_TMP, INPUT);
    Serial.begin(9600);
}
void loop() {
    int tmpVal = analogRead(PIN_TMP);

    /*
        what is tmpVal?
         - voltage? No
         - temperature? No
         - ADC value 0-4095 Yes

         The TMP36 is an analog sensor that we read with ANALOGREAD
                --> the value we read will ALWAYS be an ADC 0-4095

        ADC value but how do we get Temp in Fahr?
        ADC value --> voltage --> temp Cel --> temp Fahr

        Goal is to print the temperature in Fahr


    */
    // ADC -> Voltage
  
    
    // float voltage = tmpVal / 4095 * 3.3; // bad math in C++
    // float voltage = tmpVal / 4095.0 * 3.3; // fixed the problem
    // float voltage = float(tmpVal) / 4095 * 3.3; // fixed the problem
    float voltage = tmpVal * 3.3 / 4095; // fixed the problem

    // voltage - > temp C
    float tempC = (voltage - 0.5) / 0.01;
    // tempC to tempF
    float tempF = tempC * (9.0 / 5) + 32;

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL_TEMP) {
        prevMillis = currMillis;
        Serial.println("Temp in F = " + String(tempF, 1));

        //      .publish(EVENT_NAME, EVENT_VALUE)
        Particle.publish("temperature", String(tempF,1));
    }

}

// change this so we use a millis timer to print the temp every 2 sec
