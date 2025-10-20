#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

void setup() {
    Serial.begin(9600);
    // Subscribe to the integration response event
    Particle.subscribe("hook-response/WeatherStackJSON", myHandler, MY_DEVICES);
}

void myHandler(const char *event, const char *data) {
    // Handle the integration response
    // Serial.println(String(data)+"\n\n");

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }
    /*
    step 1: create mustache in the webhook response template
    step 2: write json parsing code here in workbench
    extract the following: 
        name
        temperature
        humidity
        weather description
        precipitation
    */
   String city = doc["city"];
   float temp = doc["temperature"];
   float humidity = doc["humidty"];
   String description = doc["description"];
//    int precipitation = doc["precipitation"];
   Serial.println(city);
   Serial.println("\tTemp C: " + String(temp));
   Serial.println("\tHumidity: " + String(humidity));
   Serial.println("\tDescription: " + description);

}

void loop() {
    // Get some data
    String data = String(10);
    // Trigger the integration
    Particle.publish("WeatherStackJSON", data, PRIVATE);
    // Wait 60 seconds
    delay(10000);

}

// http://api.weatherstack.com/current?access_key=6da8a595973d261cc8108ee3d98ac252&uery=90089