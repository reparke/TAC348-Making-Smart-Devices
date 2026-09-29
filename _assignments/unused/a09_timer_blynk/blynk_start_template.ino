// Includes
#include <blynk.h>

// Blynk configuration
#define BLYNK_TEMPLATE_ID "ADD_YOUR_OWN"
#define BLYNK_TEMPLATE_NAME "ADD_YOUR_OWN"
#define BLYNK_AUTH_TOKEN "ADD_YOUR_OWN"
#define BLYNK_IP IPAddress(64, 225, 16, 22)  // https://ny3.blynk.cloud

/*
    BLYNK_WRITE OPERATIONS (app --> argon)
    =======================================
*/
/* Example
BLYNK_WRITE(V0) {

}
*/

/*  Blynk Delay Updates
    -------------------
    To send data from ARGON to APP,  MUST use millis()
    limit is 10 values per sec
*/
unsigned long prevMillisBlynkUpdate = 0;
unsigned long blynkUpdateInterval = 1000;

/*
    SETUP
    ========================
*/
void setup() {
    // 1. have delay
    delay(5000);  // needs to be delay, not millis

    // 2. connect to blynk
    Blynk.begin(BLYNK_AUTH_TOKEN, BLYNK_IP);
}

/*
    LOOP
    ========================
*/
void loop() {
    Blynk.run();  // 3. start Blynk -- do NOT put in millis timer
    unsigned long currMillis = millis();
    if (currMillis - prevMillisBlynkUpdate > blynkUpdateInterval) {
        prevMillisBlynkUpdate = currMillis;

        /* SENDING from ARGON to APP */
        /* Example
            Blynk.virtualWrite(V0, 0);
        */
    }
}
