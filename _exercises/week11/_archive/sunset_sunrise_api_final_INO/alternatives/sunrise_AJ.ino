#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

String latitude = "-26.718614";
String longitude = "153.061886";

void setup() {
    Serial.begin(9600);
    Particle.subscribe("hook-response/sunrise_sunset", jsonSubscriptionHandler);
}

void loop() {
    // Get some data
    String data = String(10);
    // Trigger the integration
    Particle.publish("sunrise_sunset", data, PRIVATE);
    // Wait 60 seconds
    delay(10000);
}

void jsonSubscriptionHandler(const char *event, const char *data) {
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }

    /* Here is where your parsing code goes */

    String sunrise = doc["sunrise"];  // "los angeles"
    String sunset = doc["sunset"];    // 89

    Serial.println("Sunrise: " + sunrise + ", Sunset: " + sunset);
}
