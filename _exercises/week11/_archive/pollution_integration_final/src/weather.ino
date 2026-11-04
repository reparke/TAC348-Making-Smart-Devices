#include "JsonParserGeneratorRK.h"
JsonParser jsonParser;

/*
  1) publish an event to "Open_Weather"
  2) Subscribe to the RESPONSE to "Open_Weather" and ask that func "MYHANDLER" get called
  3) write MYHANDLER--what do you want to happen when a message comes back
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
      // String test = jsonParser.getReference().key("main").valueString();
      // double temp = jsonParser.getReference().key("main").key("temp").valueDouble();
      // String city = jsonParser.getReference().key("name").valueString();

      // double windSpeed = jsonParser.getReference().key("wind").key("speed").valueDouble();
      // String weather = jsonParser.getReference().key("weather").index(0).key("main").valueString();
      int aqi = jsonParser.getReference().key("list").index(0).key("main").key("aqi").valueInt();
    

      Serial.println("AQI: "+ String(aqi) + " of 5");
      Particle.publish("AQI: " + String(aqi) + " of 5");

      //get the wind speed
      //get weather - main (fn .index())
      // Serial.println("The temperature in " + city + " is " + String (temp));
      // Serial.println("The weather is " + weather + " and the wind speed is " + String(windSpeed));
    }
}

void setup() {
    Particle.subscribe("hook-response/pollution", myHandler, MY_DEVICES);
    Serial.begin(9600);
}

void loop() {

  Particle.publish("pollution", "");   //trigger our webhook to get data from openweather
  delay(10000);

}