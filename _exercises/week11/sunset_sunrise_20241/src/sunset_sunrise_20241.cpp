
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

// myHandler is EVENT DRIVEN PROGRAMMING
// this function is CALLED FOR US when the sunset api sends data back to us
// WE DONT CALL THIS FUNCTION (just like Blynk_write)
void myHandler(const char *event, const char *data) {
    // const char * can be treated like a String
    // Serial.println("Here is the entire sunrise sunset JSON response");
    // Serial.println(String(data) + "\n\n");

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }

    String sunriseTime = doc["rise"];
    String sunsetTime = doc["set"];
    Serial.println("The rise time is " + sunriseTime + " and the set time is " + sunsetTime);

}
void setup() {
    Particle.subscribe("hook-response/sunrise_sunset", myHandler, MY_DEVICES);
    Serial.begin(9600);
}

void loop() {
    Particle.publish("sunrise_sunset", "");
    // so don't go over quota, add a millis timer or delay
    delay(10000);
}