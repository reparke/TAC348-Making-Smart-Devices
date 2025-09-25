#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_TMP = A5;

void setup() {
    pinMode(PIN_TMP, INPUT);
    Serial.println(9600);
}

/*
    we never want to publish too often to the cloud because could over quota AND
there is 1 message / sec rule anyways

    --> whenver we use publish, we will always MILLIS!
        we wont use DELAY anymore (kinda)

    to use millis, what variables did we need?
    - GLOBAL prevMillis  
    - GLOBAL interval between events
    - LOCAL for current time
*/
unsigned long prevMillis = 0;
const unsigned long PUBLISH_INTERVAL = 5000;

void loop() {
    // analog input device
    // analogRead: input reading: 0-4095
    // what is it reading? Temperature
    // read the sensor and print out the temp in celsius and fahr
    //

    int tmpVal = analogRead(PIN_TMP);  // 0-4095
    // ADC -> voltage -> tempC -> tempF

    // is voltage int or float?

    /*
        when we use analogread, it uses ADC to get a range of 0-4095
        --> convert the ADC  into a voltage
            --> voltage range is 0-3.3v
    */
    float voltage = float(tmpVal) / 4095 *
                    3.3;  // remember C++ div of INT truncates decimal

    // 0.5 V offset and 10mv for 1 deg C
    float tempC = (voltage - 0.5) / 0.01;

    float tempF = tempC * (9.0 / 5) + 32;

    unsigned long curMillis = millis();     //get current relative time
    if (curMillis - prevMillis > PUBLISH_INTERVAL) {
        //always!
        prevMillis = curMillis;
        Serial.println("Temp C = " + String(tempC) + ", Temp F = " + tempF);

        //how to get data to initial state? we use Particle.publish
        Particle.publish("temperatureC", String(tempC));
        Particle.publish("temperatureF", String(tempF));
    }

    //now publish temperature in Fahr
    // Use the SAME initial state bucket
    //make a new webhook with a new event name
    //publish tempF to trigger the new webhook

}
