/* Connects to WeatherStack to receive current focus as JSON

requires JsonParserGeneratorRK library
requires account at https://weatherstack.com/

*/

#include "JsonParserGeneratorRK.h"
JsonParser jsonParser;  // dynamic version: needs to be global if multi-part
                        // responses will be sent

String response;
double temp;
double humidity;  
int precipation;
String description;
String city;

void setup() {
  // Subscribe to the integration response event
  Particle.subscribe("hook-response/WeatherStackJSON", jsonSubscriptionHandler,
                     MY_DEVICES);
}


void jsonSubscriptionHandler(const char *event, const char *data) {
  // Serial.println(String(event) + " " + String(data));
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
    // Looks valid (we received all parts)
    city = jsonParser.getReference().key("location").key("name").valueString();
    temp = jsonParser.getReference()
               .key("current")
               .key("temperature")
               .valueDouble();
    humidity = jsonParser.getReference()
                   .key("current")
                   .key("humidity")
                   .valueDouble();

    description = jsonParser.getReference()
                      .key("current")
                      .key("weather_descriptions")
					  .index(0)
                      .valueString();

    precipation =
        jsonParser.getReference().key("current").key("precip").valueInt();

    Serial.println(city + "\n  " + description + "\n  temperature: " +
                   String(temp, 1) + " F\n  humidity: " + String(humidity, 1) +
                   "%\n  rainfall: " + String(precipation) + " in");
  }
}

void loop() {
  // Get some data
  String data = "92831";

//   String data = "fetch:ip";	//auto detect IP but doesn't get right IP
  // Trigger the integration
  Particle.publish("WeatherStackJSON", data, PRIVATE);
  // Wait 60 seconds
  delay(60000);
}
