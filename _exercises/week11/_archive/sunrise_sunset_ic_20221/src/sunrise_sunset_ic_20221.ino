#include "JsonParserGeneratorRK.h"
JsonParser jsonParser; 

void setup() {
    // Subscribe to the integration response event
    Particle.subscribe("hook-response/sunrise_sunset", myHandler, MY_DEVICES);
    Serial.begin(9600);
}

/*
{

   "results":{
      "sunrise":"6:03:34 AM",
      "sunset":"6:40:06 PM",
*/
void myHandler(const char *event, const char *data) {
    // Handle the integration response
    // Serial.println(data);
    int responseIndex = 0;
    const char *slashOffset = strrchr(event, '/');
    if (slashOffset) responseIndex = atoi(slashOffset + 1);
    if (responseIndex == 0) jsonParser.clear();
    jsonParser.addString(data);

    // Part 2 is where you can parse the actual data; you code goes in the IF
    if (jsonParser.parse()) {
        String sunrise = jsonParser.getReference().key("results").key("sunrise").valueString();
        String sunset = jsonParser.getReference().key("results").key("sunset").valueString();
        Serial.println("The sunrise time at your location is " + sunrise + " and the sunset time is" + sunset);
    }
}


void loop() {
  Particle.publish("sunrise_sunset","");

  delay(10000);
  
}