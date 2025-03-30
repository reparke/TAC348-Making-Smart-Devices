
#include "Particle.h"

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// this function gets triggered when an the webhook sends data
// step 3: take this action when the response comes
void myHandler(const char *event, const char *data) {
    // declare object to store JSON response
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }

    // we will const char * as a String!
    // what is data? It is the entire JSON response from sunrise api
    //  String jsonResposne = String(data);
    //  Serial.println(jsonResposne);

    // {"rise":"{{results.sunrise}}","set":"{{results.sunset}}"}
    String sunsetTime = doc["set"];
    String riseTime = doc["rise"];
    Serial.println("The sunset time is " + sunsetTime +
                   " and the rise time is " + riseTime);
}

void setup() {
    Serial.begin(9600);
    // we need to SUBSCRIBE to our webhook
    // step 2 is listen for response
    Particle.subscribe("hook-response/sunrise_sunset", myHandler, MY_DEVICES);
}

void loop() {
    // step 1 is publish
    Particle.publish("sunrise_sunset", "");
    delay(5000);
}