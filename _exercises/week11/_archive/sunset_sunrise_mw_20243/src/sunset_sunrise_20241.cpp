
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>
/*
    Goal:
    We are receiving the following JSON
        {"rise":"6:14:53 AM","set":"4:58:33 PM"}
    We want to extract the sunrise and sunset time
    
*/

void myHandler(const char *event, const char *data) {
    // we DONT CALL THIS FUNCTION!
    // const char * is basically a string
    // to const char * data, just say "String(data)"
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }

    // Serial.println(data);
    // NOW the json DOC is basically a dictionary that we can read
    String riseString = doc["rise"];
    String setString = doc["set"];
    Serial.println("The sunset time at USC is " + setString + " and the sunrise time is "+ riseString);

}

void setup() {
    Serial.begin(9600);
    //we are now SUBSCRIBED to this event
    //when the event happens (AKA we get a response), the OS will automatically
    //call this function MYHANDLER
    Particle.subscribe("hook-response/sunrise_sunset", myHandler, MY_DEVICES);
}


void loop() {
    Particle.publish("sunrise_sunset", "");  // not sending any specific data

    delay(10000);  // millis is better!
}