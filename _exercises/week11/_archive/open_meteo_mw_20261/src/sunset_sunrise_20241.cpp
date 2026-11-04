
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

void myHandler(const char* event, const char* data) {
    // Part 1 allows for webhook responses to be delivered in multple "chunks";
    // you don't need to change this
    static String jsonBuffer;  // store json response
    int responseIndex = 0;
    const char* slashOffset = strrchr(event, '/');
    if (slashOffset) responseIndex = atoi(slashOffset + 1);
    if (responseIndex == 0) jsonBuffer = "";
    jsonBuffer += data;

    // Part 2 is where you can parse the actual data; you code goes in the IF
    DynamicJsonDocument doc(12288);
    DeserializationError error = deserializeJson(doc, jsonBuffer);

    if (!error) {  // Test to see if was successful
        // first this is lets see what we get as response
        //  Serial.println();
        //  Serial.println(String(jsonBuffer));
        //  Serial.println();
        float tempF = doc["current"]["temperature_2m"];
        int humidity = doc["current"]["relative_humidity_2m"];
        Serial.println("The temp in LA is " + String(tempF, 2) +
                       " and the humidity is " + String(humidity));
    }
}

void setup() {
    Particle.subscribe("hook-response/open_meteo_json", myHandler, MY_DEVICES);
    Serial.begin(9600);
}
void loop() {
    Particle.publish("open_meteo_json", "");
    delay(5000);
}
