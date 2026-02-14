

#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
    serial print the temperature in Fahr every 5 sec
    - from now on, we will NOT use delay

    what variables do we need to build a millis timer?
    1 global var for prevMillis
    2 local var for currMillis
    3 GLOBAL CONSTANT for the interval

    TMP 36 - analog input

    ADC 0-4095 --> Voltage  --> Celsius  --> Fahr
*/
const int PIN_TMP = A5;

// millis timer
unsigned long prevMillis = 0;
const unsigned long INTERVAL = 5000;

void setup() {
    Serial.begin(9600);
    pinMode(PIN_TMP, INPUT);
}
void loop() {
    // current time
    unsigned long currMillis = millis();

    if (currMillis - prevMillis >= INTERVAL) {
        prevMillis = currMillis;  // first thing: update prevMillis

        int tmpVal = analogRead(PIN_TMP);  // ADC 4095

        // convert to voltage
        //  in range: 0-4095
        //  out range: 0-3.3
        //  float voltage = tmpVal / 4095.0 * 3.3;
        float voltage = float(tmpVal) / 4095 * 3.3;

        // convert to Cel
        float celsius = (voltage - 0.5) / 0.01;

        float fahr = celsius * 9 / 5 + 32;

        Serial.println("Temp F = " + String(fahr));
        //Particle.publish(EVENT_NAME, EVENT_VALUE)
        //we choose the EVENT_NAME

        // this is STEP 1 of sending to initial state
        Particle.publish("initial_state_single", String(fahr));

        //step 2: creating webhook

        //step 3: setting up dashboard with initial state
    }
}

/*
       tmpVal / 4095.0 * 3.3;
float(tmpVal) / 4095 * 3.3;


in C++, 
    int  /   int   ===> int

    99 / 100        ===> 0


    float / int ==> float
    99.0 / 100      -> 0.99
    float(99) / 100 -> 0.99


*/