#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

void myHandler(const char *event, const char *data) {
    // Handle the integration response
    // Serial.println(String(data) + "\n\n");

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }

    String name = doc["name"];
    int temp = doc["temperature"];
    String description = doc["description"];
    Serial.println("The weather in " + name + " is " + description + " and " + String(temp) + " degrees C");
}

void setup() {
    Serial.begin(9600);
    // Subscribe to the integration response event
    Particle.subscribe("hook-response/WeatherStackJSON", myHandler, MY_DEVICES);
}


void loop() {
    // Get some data
    String data = String(10);
    // Trigger the integration
    Particle.publish("WeatherStackJSON", data, PRIVATE);
    // Wait 60 seconds
    delay(10000);
}

//name, description, temperature

