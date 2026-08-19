
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);
/*
    now: we are publishing to our webhook
        -Particle cloud is sending our message to the API
        -the API will send a response
        -BUT how will we know the response has arrived?

    parsing JSON
        we could do this manually by hand -- AWFUL
        --> use ArduinoJson library
*/
//step 1: install library

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

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
        String sunrise = doc["results"]["sunrise"];
        String sunset = doc["results"]["sunset"];

        Serial.println("The sunrise in LA is at " + sunrise + " and the sunset is at " + sunset);

    }
}

    void setup() {
        Serial.begin(9600);
        Particle.subscribe("hook-response/sunrise_sunset", myHandler,
                           MY_DEVICES);
        /* this tell particle that we want to NOTIFIED when RESPONSE to our
           webHOOK called SUNRISE_SUNSET is received

            we need a function that is called when the response is received

            --> EVENT HANDLER
        */
    }

    void loop() {
        // publish the message to sunrise api, which the api
        // to send us back a json response
        Particle.publish("sunrise_sunset", "");
        delay(5000);
    }