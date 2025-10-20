#include "JsonParserGeneratorRK.h"

JsonParser jsonParser;

void loop() {
    // Get some data
    Serial.begin(9600);
    String data = "90089";
    // Trigger the integration
    Particle.publish("WeatherStackJSON", data, PRIVATE);
    // Wait 60 seconds
    delay(20000);
}

void setup() {
    // Subscribe to the integration response event
    Particle.subscribe("hook-response/WeatherStackJSON", myHandler, MY_DEVICES);
}

void myHandler(const char *event, const char *data) {

    int responseIndex = 0;

    const char *slashOffset = strrchr(event, '/');
    if (slashOffset) {
        responseIndex = atoi(slashOffset + 1);
    }

    if (responseIndex == 0) {
        jsonParser.clear();
    }
    jsonParser.addString(data);

    /*
  "location": {
    "name": "Los Angeles",
    "country": "USA",
    "region": "California",
    "lat": "34.018",
    "lon": "-118.284",
    "timezone_id": "America/Los_Angeles",
    "localtime": "2020-10-22 16:47",
    "localtime_epoch": 1603385220,
    "utc_offset": "-7.0"
  },
   "current": {
    "observation_time": "11:47 PM",
    "temperature": 22,
    "weather_code": 116,
    "weather_icons": [
      "https://assets.weatherstack.com/images/wsymbols01_png_64/wsymbol_0002_sunny_intervals.png"
    ],
    "weather_descriptions": [
      "Partly cloudy"
    ],
    "wind_speed": 7,
    "wind_degree": 270,
    "wind_dir": "W",
    "pressure": 1011,
    "precip": 0,
    "humidity": 59,
    "cloudcover": 50,
    "feelslike": 22,
    "uv_index": 5,
    "visibility": 14,
    "is_day": "yes"
  }
*/

    //this is where we start coding
    if (jsonParser.parse()) {
      String city = jsonParser.getReference().key("location").key("name").valueString();
      int temp = jsonParser.getReference().key("current").key("temperature").valueInt();
      int humidity = jsonParser.getReference().key("current").key("humidity").valueInt();
      int precipitation = jsonParser.getReference().key("current").key("precip").valueInt();

      String desc = jsonParser.getReference().key("current").key("weather_description").index(0).valueString();


      Serial.println("Weather for " + city);

      //temperarture, humidity, precipitation, descritpion
    }
}