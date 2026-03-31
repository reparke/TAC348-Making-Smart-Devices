
#include "Particle.h"

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

void myHandler(const char *event, const char *data) {
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }
    // Handle the integration response
    // Serial.println("We just received a response to our publish");

    // const char * is basically A STRING
    // Serial.println(data);
    // printout "The sunrise time is X and the sunset time is Y"
    String sunsetTime = doc["set"];
    String sunriseTime = doc["rise"];
    Serial.println("The sunset time in LA is " + sunsetTime +
                   " and the sunrise time is " + sunriseTime);
}

void setup() {
    Serial.begin(9600);
    // this tells the cloud to listen for this response
    // and then call the function MYHANDLER when we get a response
    // EVENT DRIVEN PROGRAMMING
    Particle.subscribe("hook-response/sunrise_sunset", myHandler, MY_DEVICES);
}

void loop() {
    Particle.publish("sunrise_sunset", "");
    delay(10000);  // millis is better!
}