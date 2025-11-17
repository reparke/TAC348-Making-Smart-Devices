
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

/*
{
   "results":{
      "sunrise":"6:15:34 AM",
      "sunset":"4:57:54 PM",
      "solar_noon":"11:36:44 AM",
      "day_length":"10:42:20",
      "civil_twilight_begin":"5:50:52 AM",
      "civil_twilight_end":"5:22:37 PM",
      "nautical_twilight_begin":"5:21:07 AM",
      "nautical_twilight_end":"5:52:22 PM",
      "astronomical_twilight_begin":"4:51:46 AM",
      "astronomical_twilight_end":"6:21:43 PM"
      
      */
void myHandler(const char* event, const char* data) {
    // Part 1 allows for webhook responses to be delivered in multple "chunks";
    // you don't need to change this
    static String jsonBuffer;  // store json response
    int responseIndex = 0;
    const char* slashOffset = strrchr(event, '/');
    if (slashOffset) responseIndex = atoi(slashOffset + 1);
    if (responseIndex == 0) jsonBuffer = "";
    jsonBuffer += data;

    // Part 2 is where you can parse the actual data; you code goes in the IF
    DynamicJsonDocument doc(12288);
    DeserializationError error = deserializeJson(doc, jsonBuffer);

    if (!error) {  // Test to see if was successful

        /* Here is where your parsing code goes */
        String sunriseTime = doc["results"]["sunrise"];
        String sunsetTime = doc["results"]["sunset"];
        Serial.println("In LA sunset is " + sunsetTime + " and sunrise is " + sunriseTime);

    }
}
    void setup() {
        Serial.begin(9600);
        // in order to be notified when we receive an API response, we have to
        // SUBSCRIBE
        Particle.subscribe("hook-response/sunrise_sunset", myHandler,
                           MY_DEVICES);
    }

    void loop() {
        // publish so that the API knows we want a response back
        Particle.publish("sunrise_sunset", "");
        delay(5000);
    }