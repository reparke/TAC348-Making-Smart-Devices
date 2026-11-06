#include "Particle.h"

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

#include "json_webhook_response_helper.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
Goal: display the current temperature, humidity, and weather code for USC 

Steps:

1) created webhook
2) Subscribe
3) Build event handler
4) In event handler, we get the data we need from json (parse)
5) Publish the original request

*/

void myHandler(const char* event, const char* data) {
    // Part 1: helper function allows for webhook responses to be delivered in
    // multple "chunks"; you don't need to change these lines
    String fullJson = json_webhook_response_helper(event, data);
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, fullJson);

    // Part 2 is where you can parse the actual data; you code goes in the IF
    if (!error) {
        float temperature = doc["current"]["temperature_2m"];
        int humidity = doc["current"]["relative_humidity_2m"];
        int weatherCode = doc["current"]["weather_code"];

        int elevation = doc["elevation"];

        Serial.println("At USC, the temperature is " + String(temperature,0) + "F and the humidity is " +  String(humidity));
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
