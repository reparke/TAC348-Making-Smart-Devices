
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

String latUSC = "34.02051";
String longUSC = "-118.28563";
int batteryLevel = 100;

/*
    generate random temp and humidity
        --> send those to initial state with a SINGLE webhook
    format is [{"key": "temp", "value": 32}]
        -->  [ {}, {}, {} ... {}]
        [ {"key":"firstKey", "value":"firstValue"}, {"key":"secondKey",
   "value":"secondValue"}, ...]

    [{"key": "temp", "value": 70}, {"key":"humidity", "value":45}]

    GPS format for initial state
    String
    latitude,longitude --> "34.48839,-118.38883"
*/

void setup() { Serial.begin(9600); }

void loop() {
    // step1: create the container that will store all the json as build it
    StaticJsonDocument<1024> doc;
    String jsonString;

    // step 2: we will add all the json values to the document
    //      in the format that Initial State gave us

    // generate random temperature and humidity
    int temp = random(70, 100);
    int humidity = random(0, 100);

    // try sending GPS location and a battery value
    // make the battery value decrease

    // create first "nested object"
    JsonObject obj0 = doc.createNestedObject();
    obj0["key"] = "temp";
    obj0["value"] = temp;

    // create second nested object
    JsonObject obj1 = doc.createNestedObject();
    obj1["key"] = "humidity";
    obj1["value"] = humidity;

    JsonObject obj2 = doc.createNestedObject();
    obj2["key"] = "gps_usc";
    obj2["value"] = latUSC + "," + longUSC;

    JsonObject obj3 = doc.createNestedObject();
    obj3["key"] = "battery_level";
    obj3["value"] = batteryLevel;

    batteryLevel = batteryLevel - 2;
    if (batteryLevel < 0) {
        batteryLevel = 100;
    }

    // turn the json document into a string
    serializeJson(doc, jsonString);  // puts the DOC into the a string
                                     // JSONSTRING

    Serial.println(jsonString);

    // we would use millis timer or delay
    Particle.publish("initial_state_json", jsonString);
    delay(10000);
}