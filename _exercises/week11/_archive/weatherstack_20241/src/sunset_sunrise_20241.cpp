
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

void myHandler(const char *event, const char *data) {
    // Serial.println(String(data));
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }

    String city = doc["name"];
    int temp = doc["temperature"];
    String weather = doc["description"];

    Serial.println("The weather in " + city  + " is " +String(temp) + " and " + weather);


}

void setup() {
    Particle.subscribe("hook-response/WeatherStackJSON", myHandler, MY_DEVICES);
    Serial.begin(9600);
}

void loop() {
    Particle.publish("WeatherStackJSON", "");
    delay(10000);
}

/*
    temperature, city name, weather description
*/