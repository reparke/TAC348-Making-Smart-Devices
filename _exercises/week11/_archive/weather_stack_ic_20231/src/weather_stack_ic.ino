#include "JsonParserGeneratorRK.h"

/*
{
   "request":{
      "type":"Zipcode",
      "query":"90089",
      "language":"en",
      "unit":"f"
      },
   "location":{
      "name":"Los Angeles",
      "country":"USA",
      "region":"California",
      "lat":"34.018",
      "lon":"-118.284",
      "timezone_id":"America\/Los_Angeles",
      "localtime":"2023-03-22 13:27",
      "localtime_epoch":1679491620,
      "utc_offset":"-7.0"
   },
   "current":{
      "observation_time":"08:27 PM",
      "temperature":54,
      "weather_code":296,
      "weather_icons":[
         "https:\/\/cdn.worldweatheronline.com\/images\/wsymbols01_png_64\/wsymbol_0017_cloudy_with_light_rain.png"
      ],
      "weather_descriptions":[
         "Light Rain"
      ],
      "wind_speed":4,
      "wind_degree":80,
      "wind_dir":"E",
      "pressure":1018,
      "precip":0,
      "humidity":80,
      "cloudcover":100,
      "feelslike":52,
      "uv_index":3,
      "visibility":6,
      "is_day":"yes"
   }
}
*/
// sample code
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
        //    Serial.println(jsonParser.getBuffer());
        Serial.println();
        Serial.println("Full JSON\n" + String(jsonParser.getBuffer()));

        // city, weather descript, temperature, humidity
        String city =
            jsonParser.getReference().key("location").key("name").valueString();
        int temperature = jsonParser.getReference()
                              .key("current")
                              .key("temperature")
                              .valueInt();
        String description = jsonParser.getReference()
                                 .key("current")
                                 .key("weather_descriptions")
                                 .index(0)
                                 .valueString();
        Serial.println(city + ": The temperature is " + String(temperature) +
                       " F and the weather is " + description);
    }
}

void setup() {
    Serial.begin(9600);
    Particle.subscribe("hook-response/weatherstack", myHandler);
}

void loop() {
    Particle.publish("weatherstack", "");
    delay(10000);  // millis is better
}