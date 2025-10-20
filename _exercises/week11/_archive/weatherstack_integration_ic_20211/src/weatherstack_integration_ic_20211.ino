#include "JsonParserGeneratorRK.h"

JsonParser jsonParser;

/*
{
  "request": {
    "type": "Zipcode",
    "query": "90089",
    "language": "en",
    "unit": "f"
  },
  "location": {
    "name": "Los Angeles",
    "country": "USA",
    "region": "California",
    "lat": "34.018",
    "lon": "-118.284",
    "timezone_id": "America/Los_Angeles",
    "localtime": "2021-03-30 16:31",
    "localtime_epoch": 1617121860,
    "utc_offset": "-7.0"
  },
  */

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
        // Serial.println(jsonParser.getBuffer());
        String city = jsonParser.getReference().key("location").key("name").valueString();
        Serial.println("City: " + city);
        //city: temperature, humidity %, precipitation, description
    }
}

// setup() runs once, when the device is first turned on.
void setup() {
    Serial.begin(9600);
    Particle.subscribe("hook-response/WeatherStackJSON", myHandler, MY_DEVICES);
}

void loop() {
    // Get some data
    String data = "90089";
    // Trigger the integration
    Particle.publish("WeatherStackJSON", data, PRIVATE);
    delay(60000);
}