
#include "JsonParserGeneratorRK.h"
JsonParser jsonParser;  // dynamic version: needs to be global if multi-part


String sunrise;
String sunset;

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
    int responseIndex = 0;

    const char *slashOffset = strrchr(event, '/');
    if (slashOffset) {
        responseIndex = atoi(slashOffset + 1);
    }

    if (responseIndex == 0) {
        jsonParser.clear();
    }
    jsonParser.addString(data);

    if (jsonParser.parse()) {
        sunrise = jsonParser.getReference().key("results").key("sunrise").valueString();
        sunset = jsonParser.getReference().key("results").key("sunset").valueString();

        Serial.println("Sunrise: " + sunrise + ", Sunset: " + sunset);
    }
}
