/* Connects to WeatherStack to receive current  JSON
This uses Mustache templates

{"city":"{{{location.name}}}","temperature":"{{{current.temperature}}}","description":"{{{current.weather_descriptions.0}}}","precip":"{{{current.precip}}}","humidity":"{{{current.humidity}}}"}

requires ArduinoJson library
requires account at https://weatherstack.com/

*/
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

// responses will be sent
String response;

void setup() {
    // Subscribe to the integration response event
    Particle.subscribe("hook-response/WeatherStackMustache", myHandler);
}

void myHandler(const char *event, const char *data) {
    StaticJsonDocument<2048> doc;
    DeserializationError error = deserializeJson(doc, data);

    if (error == false) {
        String city = doc["city"];
        float temp = doc["temperature"];          // 68
        String description = doc["description"];  // "Sunny"
        float precipation = doc["precip"];        // 0
        float humidity = doc["humidity"];         // 40

        Serial.println(city + "\n  " + description +
                       "\n  temperature: " + String(temp, 1) +
                       " F\n  humidity: " + String(humidity, 1) +
                       "%\n  rainfall: " + String(precipation, 1) + " in");
    } else {
        Serial.println(" Error: " + String(error.c_str()));
        Serial.println("\t" + response);
    }
}

void loop() {
    // Get some data
    String data = "92807";

    // Trigger the integration
    Particle.publish("WeatherStackMustache", data);

    delay(10000);
}
