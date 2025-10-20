#include "JsonParserGeneratorRK.h"

/*
{
  "results": {
    "sunrise": "6:34:07 AM",
    "sunset": "5:29:09 PM",
    "solar_noon": "12:01:38 PM",
    "day_length": "10:55:02",
    "civil_twilight_begin": "6:09:02 AM",
    "civil_twilight_end": "5:54:15 PM",
    "nautical_twilight_begin": "5:38:43 AM",
    "nautical_twilight_end": "6:24:34 PM",
    "astronomical_twilight_begin": "5:08:40 AM",
    "astronomical_twilight_end": "6:54:37 PM"
  },
  "status": "OK"
}
*/
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
        Serial.println(jsonParser.getBuffer());
        String sunset = jsonParser.getReference().key("results").key("sunset").valueString();
        String sunrise = jsonParser.getReference().key("results").key("sunrise").valueString();
        Serial.println("The sunrise is at " + sunrise);
        Serial.println("The sunset is at "+ sunset);
    }
}

void setup()
{
    Serial.begin(9600);
    Particle.subscribe("hook-response/sunrise_sunset", myHandler, MY_DEVICES);
}

void loop() {
    Particle.publish("sunrise_sunset", ""); // this will trigger the webhook to request data from the API
    delay(10000);
}

