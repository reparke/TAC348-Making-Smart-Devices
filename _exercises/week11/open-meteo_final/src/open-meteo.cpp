#include "Particle.h"

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

#include "json_webhook_response_helper.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

void myHandler(const char* event, const char* data) {
    JsonDocument doc;

    String fullJson = json_webhook_response_helper(event, data);

    DeserializationError error = deserializeJson(doc, fullJson);
    if (!error) {
        Serial.println(fullJson);
        Serial.println();

        float tempF = doc["current"]["temperature_2m"];
        int code = doc["current"]["weather_code"];
        int humidity = doc["current"]["relative_humidity_2m"];

        Serial.println("The weather is " + String(tempF, 1) + " F and " +
                       String(humidity) + "% humidity with weather code " +
                       String(code));
        Serial.println();

        // just for remote debugging
        String output = "The weather is " + String(tempF, 1) + " F and " +
                        String(humidity) + "% humidity with weather code " +
                        String(code);
        Particle.publish("Output", output);
    }
}

void setup() {
    Serial.begin(9600);
    Particle.subscribe("hook-response/open_meteo", myHandler, MY_DEVICES);
}

void loop() {
    Particle.publish("open_meteo", "");
    delay(10000);
}
