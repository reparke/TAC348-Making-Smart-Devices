#include "JsonParserGeneratorRK.h"

JsonParser jsonParser;
/*
{
   "results":{
      "sunrise":"1:52:35 PM",
      "sunset":"2:07:22 AM",
      "solar_noon":"7:59:59 PM",
      "day_length":"12:14:47",
      "civil_twilight_begin":"1:28:54 PM",
      "civil_twilight_end":"2:31:04 AM",
      "nautical_twilight_begin":"12:59:43 PM",
      "nautical_twilight_end":"3:00:15 AM",
      "astronomical_twilight_begin":"12:30:10 PM",
      "astronomical_twilight_end":"3:29:48 AM"
   },
   "status":"OK"
}
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
        // Serial.println(String(data));
        Serial.println();
        //look for key "results" and then key "sunrise"
        String sunset = jsonParser.getReference().key("results").key("sunset").valueString();
        String sunrise = jsonParser.getReference().key("results").key("sunrise").valueString();

        Serial.println("The sunrise is " + sunrise + " and the sunset is " + sunset);


    }
}

void setup() {
    Serial.begin(9600);

    // to receive the json from sunrise, use subscribe
    Particle.subscribe("hook-response/sunrise_sunset", myHandler);
}

void loop() {
    // send the request for sunrise data, use publish
    Particle.publish("sunrise_sunset", "");
    delay(10000);  // millis is better :)
}
