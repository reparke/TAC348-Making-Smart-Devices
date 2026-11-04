#include "Particle.h"

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

#include "json_webhook_response_helper.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

void myHandler(const char* event, const char* data) {
    // Handle the integration response
    // assemble/parse
    // Part 1: helper function allows for webhook responses to be delivered in
    // multple "chunks"; you don't need to change these lines
    String fullJson = json_webhook_response_helper(event, data);
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, fullJson);

    // Part 2 is where you can parse the actual data; you code goes in the IF
    if (!error) {
        /*          ============
        Here is where your parsing code goes
                    ============
        */
       float temperature = doc["current"]["temperature_2m"];
        int humidty = doc["current"]["relative_humidity_2m"];
        int weatherCode = doc["current"]["weather_code"];
        int elevation = doc["elevation"];

        Serial.println("In LA, the temperature now is " + String(temperature,0) + " and the humidity is " + String(humidty) + "%");
    }
}

void setup() {
    Serial.begin(9600);

    // Subscribe to the integration response event
    Particle.subscribe("hook-response/open_meteo", myHandler, MY_DEVICES);
}

void loop() {
    Particle.publish("open_meteo", "");

    delay(10000);
}

/*

- Created webhook by looking at API
- Publish the request
- Subscribed to the response
- Create the event handler (myHandler)
- Assemble/deserialize/parse JSON

*/