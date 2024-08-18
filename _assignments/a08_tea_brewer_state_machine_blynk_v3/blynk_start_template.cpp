#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);


#define BLYNK_TEMPLATE_ID "ADD_YOUR_OWN"
#define BLYNK_DEVICE_NAME "ADD_YOUR_OWN"
#define BLYNK_AUTH_TOKEN "ADD_YOUR_OWN"

#include <blynk.h>  //library (need to import it in your own project)



unsigned long blynkDelay = 1000;  // delay between sending PHOTON to APP
unsigned long prevMillis = 0;

/* template for RECEIVING APP to PHOTON */
/*
BLYNK_WRITE(V0) {

}
*/

void setup() {
    // 1. Require initial Blynk delay
    delay(5000);
    // 2. connect to blynk
    Blynk.begin(BLYNK_AUTH_TOKEN);
}

void loop() {
    Blynk.run();  // 3. start Blynk -- do NOT put in millis timer
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > blynkDelay) {
        prevMillis = currMillis;

        /* template for SENDING PHOTON to APP*/
        /*
            Blynk.virtualWrite(V0, 0);
        */
    }
}