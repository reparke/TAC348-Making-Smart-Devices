#include "Particle.h"

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

#include "json_webhook_response_helper.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
photon publishes a request (particle.publish)

cloud receives request and it triggers the webhook
    --> the cloud send our request to the sunset API

    ... ... ... time passes ... ... ...  ASYNCHRONOUS

Sunrise API send a RESPONSE back to the cloud (json format)

cloud receives the response...by default, it does nothing
    --> in order for photon to receive the response, we must SUBSCRIBE to the event

    once we have SUBSCRIBE, we are need to create EVENT HANDLER

THEN
    we will be notified when the response arrives
    AND
    our event handler will be called automatically

    myHandler is our event handler
        const char *  ---> we can treat mostly like a String
        event is the name 
        data is the json message

*/

void myHandler(const char* event, const char* data) {
    // Handle the integration response
    // Serial.println(data);
    // Serial.println();
    
    //this is a helper fn that assembles all the pieces of the full json
    String fullJson = json_webhook_response_helper(event, data);

    // Serial.println(fullJson);

    //we now have all the json string
    //we need to DESERIALIZE
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, fullJson);

    // Part 2 is where you can parse the actual data; you code goes in the IF
    if (!error) {

        String sunrise = doc["sunrise"];
        String sunset = doc["sunset"];

        Serial.println("In LA, the sunset is at " + sunset + " and the sunrise is at " + sunrise);
    }
}
void setup() {
    Serial.begin(9600);
    Particle.subscribe("hook-response/sunrise_sunset", myHandler, MY_DEVICES);
}


void loop() {
    //publish
    Particle.publish("sunrise_sunset", ""); //empty string
    Serial.println("Publishing request to cloud");
    delay(10000);       //we should use millis
}
