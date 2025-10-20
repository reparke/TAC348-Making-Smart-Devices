
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

// step 3: create the myHandler function
void myHandler(const char *event, const char *data) {
    // two "const char *" params
    // for us, treat these like strings
    // the DATA param includes the entire json response
    // Serial.println(String(data));

    // these 5 lines are from the library and they convert the
    //  JSON string back into an object we manipulate in code
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }
    // json: {"rise":"6:45:03 AM","set":"7:11:35 PM"}
    String sunriseTime = doc["rise"];
    String sunsetTime = doc["set"];
    Serial.println("In LA, the sunset time is " + sunsetTime +
                   " and the sunrise time is " + sunriseTime);
    Serial.println(String(data));
}

void setup() {
    // step 2: "listen" (AKA notify us) for this response
    //          when response comes, call the MYHANDLER function
    Particle.subscribe("hook-response/sunrise_sunset", myHandler, MY_DEVICES);
    Serial.begin(9600);
}

void loop() {
    // step 1: trigger webhook by publishing
    Particle.publish("sunrise_sunset", "");
    delay(5000);
}