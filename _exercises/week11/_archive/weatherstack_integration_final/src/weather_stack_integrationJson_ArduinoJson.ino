/* Connects to WeatherStack to receive current  JSON
This uses Mustache templates

{"city":"{{{location.name}}}","temperature":"{{{current.temperature}}}","description":"{{{current.weather_descriptions.0}}}","precip":"{{{current.precip}}}","humidity":"{{{current.humidity}}}"}

requires ArduinoJson library
requires account at https://weatherstack.com/

*/
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

void setup() {
    // Subscribe to the integration response event
    Particle.subscribe("hook-response/WeatherStackJSON", myHandler);
}

void myHandler(const char *event, const char *data) {
    StaticJsonDocument<2048> doc;
    DeserializationError error = deserializeJson(doc, data);

    if (error == true) {
        Serial.println(" Error: " + String(error.c_str()));
        return;
    }

    String name = doc["name"];
    float temp = doc["temperature"];          // 68
    String description = doc["description"];  // "Sunny"
    int uv_index = doc["uv_index"];           // 0

    Serial.println(name + "\n  " + description +
                   "\n  temperature: " + String(temp, 1) +
                   "%\n  uv_index: " + String(uv_index) + " in");
}

void loop() {
    // Get some data
    String data = "92807";

    // Trigger the integration
    // Particle.publish("WeatherStackJSON", data);

    delay(10000);
}
