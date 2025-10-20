#include "JsonParserGeneratorRK.h"
JsonParser jsonParser;  // dynamic version: needs to be global if multi-part

void setup() {
    Particle.subscribe("hook-response/JSONWeatherStack",
                       jsonSubscriptionHandler, MY_DEVICES);
}

void loop() {
    // Trigger the integration
    Particle.publish("sunrise_sunset", "", PRIVATE);
    // Wait 60 seconds
    delay(60000);
}
void jsonSubscriptionHandler(const char *event, const char *data) {
    // Part 1 allows for webhook responses to be delivered in multple "chunks";
    // you don't need to change this
    int responseIndex = 0;
    const char *slashOffset = strrchr(event, '/');
    if (slashOffset) responseIndex = atoi(slashOffset + 1);
    if (responseIndex == 0) jsonParser.clear();
    jsonParser.addString(data);

    // Part 2 is where you can parse the actual data; you code goes in the IF
    if (jsonParser.parse()) {
        String sunset = jsonParser.getReference().key("results").key("sunset").valueString();
        String sunrise = jsonParser.getReference()
                            .key("results")
                            .key("sunrise")
                            .valueString();

        Serial.println("Sunset: " + sunset);
        Serial.println("Sunrise: " + sunrise);
    }
}
