#include <blynk.h>  //library (need to import it in your own project)
#define BLYNK_PRINT Serial 
#define BLYNK_IP IPAddress(64, 225, 16, 22)  // https://ny3.blynk.cloud/ – New York

#define BLYNK_TEMPLATE_ID "ADD_YOUR_OWN"
#define BLYNK_TEMPLATE_NAME "ADD_YOUR_OWN"
#define BLYNK_AUTH_TOKEN "ADD_YOUR_OWN"

unsigned long blynkDelay = 1000;  // delay between sending ARGON to APP
unsigned long prevMillis = 0;

/* template for RECEIVING APP to ARGON */
/*
BLYNK_WRITE(V0) {

}
*/

void setup() {
    // 1. Require initial Blynk delay
    delay(5000);
    // 2. connect to blynk
    Blynk.begin(BLYNK_AUTH_TOKEN, BLYNK_IP);
}

void loop() {
    Blynk.run();  // 3. start Blynk -- do NOT put in millis timer
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > blynkDelay) {
        prevMillis = currMillis;

        /* template for SENDING ARGON to APP*/
        /*
            Blynk.virtualWrite(V0, 0);
        */
    }
}