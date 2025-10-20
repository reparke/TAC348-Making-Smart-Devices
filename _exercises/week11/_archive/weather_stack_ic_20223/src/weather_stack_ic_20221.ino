#include "JsonParserGeneratorRK.h"

JsonParser jsonParser;

void myHandler(const char *event, const char *data) {
    // Part 1 allows for webhook responses to be delivered in multple "chunks";
    // you don't need to change this
    int responseIndex = 0;
    const char *slashOffset = strrchr(event, '/');
    if (slashOffset) responseIndex = atoi(slashOffset + 1);
    if (responseIndex == 0) jsonParser.clear();
    jsonParser.addString(data);

    // Part 2 is where you can parse the actual data; you code goes in the IF
    if (jsonParser.parse()) {
        /****** YOUR PARSING CODE GOES HERE ********/
        // print city, temperature, humidity,  description, precipitatio
        String city = jsonParser.getReference().key("location").key("name").valueString();

        double temp = jsonParser.getReference().key("current").key("temperature").valueDouble();

        double humidity = jsonParser.getReference().key("current").key("humidity").valueDouble();

        String description = jsonParser.getReference().key("current").key("weather_description").index(0).valueString();

        int precipation = jsonParser.getReference().key("current").key("precip").valueInt();

        Serial.println(
            city + "\n  " + description +
            "\n  temperature: " + String(temp, 1) +
            " F\n  humidity: " + String(humidity, 1) +
            "%\n  rainfall: " + String(precipation) + " in");
    }
}

void setup() {
    Particle.subscribe("hook-response/weatherstack", myHandler, MY_DEVICES);
}

void loop() {
    Particle.publish("weatherstack", "90089");
    delay(10000);
}