
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

void setup() {
    Serial.begin(9600);
    // Subscribe to the integration response event
    Particle.subscribe("hook-response/sunrise_sunset", myHandler, MY_DEVICES);
}

void myHandler(const char *event, const char *data) {
    // event is a string that stores "nook-response/sunrise_senset"
    //  we dont care about this
    // data is a string that stores the JSON---we do care about this
    Serial.println("We are inside the myhandler function");
    // Serial.println(String(data));

    // declare object to store JSON response
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }
    // now we just PARSE (aka read) the JSON
    String sunrise = doc["sunriseTime"];
    String sunset = doc["sunsetTime"];
    Serial.println("The sun will rise in LA at " + sunrise +
                   " and will set at " + sunset);
}

void loop() {
    // Get some data
    String data = String(10);
    // Trigger the integration
    Serial.println("Inside loop(): about to publish message to API");
    Particle.publish("sunrise_sunset", data, PRIVATE);

    delay(10000);
}