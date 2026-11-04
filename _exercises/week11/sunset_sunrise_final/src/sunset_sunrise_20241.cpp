
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>
#include "json_webhook_response_helper.h"

/*
Photon publish a request
    Cloud sends request to Sunrise API because publish triggered the webhook
       Sunrise API receives the request
  
  ...time passes... this is ASYNCHRONOUS

       Sunrise API send a response to the Cloud
    Cloud receives response AND see that Photon has SUBSCRIBED to this response
    THEREFORE, Cloud will send Photon the response
Photon receives response and immediately (automatically) calls myHandler

*/

void myHandler(const char* event, const char* data) {
    String fullJson = json_webhook_response_helper(event, data);
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, fullJson);

    if (!error) {  // Test to see if was successful
        String sunrise = doc["results"]["sunrise"];
        String sunset = doc["results"]["sunset"];

        Serial.println("The sunset in LA is " + sunset + " and the sunrise is " + sunrise);
    }
}

void setup() { 
    Serial.begin(9600);
    
    //tells the cloud we want be notified when 
    //we get a reponse to our request
    //ALSO, "myHandler" is going to be the fn we write to 
    //respond as the event handler
    Particle.subscribe("hook-response/sunrise_sunset", myHandler, MY_DEVICES);
}
void loop() {
    // lets publish request
    Particle.publish("sunrise_sunset", "");
    // second parameter is empty because we are always getting the same location

    delay(5000);
}
