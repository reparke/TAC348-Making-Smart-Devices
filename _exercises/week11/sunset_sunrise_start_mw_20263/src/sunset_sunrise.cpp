#include "Particle.h"

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

#include "json_webhook_response_helper.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
Photon publishes a request
    Cloud receives and send our requrest to sunrise API because we trigged
        the webhook

    ...time passes... this is ASYNCHRONOUS

    Sunrise API send the RESPONSE to the cloud

    Cloud receives response but in order for us to be sent the resposne
        --> we have to SUBSCRIBE to the response event

    we need to subscribe to the event
    AND
    create an EVENT HANDLER

    THEN
        we will be notified when the response arrives
        AND
        the event handler will be called automatically


    when the respocomes back, our photon will AUTOMATICALLLY call the func
        myHandler
            two param: event which is the name of our event
                       data which is the json
*/

void myHandler(const char* event, const char* data) {
    // Handle the integration response
    // Serial.println(data);
    // Serial.println();
    String fullJson = json_webhook_response_helper(event, data);
    //this is a helper for us that assembles all the parts of a 
    // JSON RESPONSE

    //now we have the full json string
    // Serial.println(fullJson);
    // Serial.println();

    //but we need to "parse" the string into variables
    JsonDocument doc;
    //lets try to "deserialize" the json
    DeserializationError error = deserializeJson(doc, fullJson);
    if (!error) {
        //if this works, now we can parse the parse the json
        String sunrise = doc["sunrise"];

        String sunset = doc["sunset"];

        Serial.println("The sunrise in LA is at " + sunrise + " and the sunset is at " + sunset);

    }
}

void setup() {
    Serial.begin(9600);
    Particle.subscribe("hook-response/sunrise_sunset", myHandler, MY_DEVICES);
}

void loop() {
    //publish the request
    Serial.println("Publishing request to cloud...");
    Particle.publish("sunrise_sunset", "");
    //the second param is empty because we are always requesting the SAME location data


    delay(10000);       //could use millis instead
}
