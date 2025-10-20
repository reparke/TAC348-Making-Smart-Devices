
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// add these lines to make library compatible with photon
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

// store initial GPS coordinates
//  34.0224 N, 118.2851 W
// what kind of var should we use for GPS?
// float latitude = 34.0224; // introduces error
// 34.02240000000001
String latitude = "34.0224";
String longitude = "-118.2851";

/*
    lets send a random temperature and humidity to IS using JSON

    Initial State JSON Format
    format:   [ {}, {}, ... {} ]
    JSON object: { "key": LABEL, "value": VALUE }
    ex:          { "key":"Humidity", "value":55.4 }


    We COULD just create this JSON string by hand
    BUT
    often people use libraries

    GPS
    format: "lat,lng"   ---> "53.34,48.33"





*/

void setup() { Serial.begin(9600); }

void loop() {
    // step 1: create the blank JSON document which will store our data to send
    // to IS
    JsonDocument doc;
    // create the final string we will to IS
    String jsonString;

    String strKey = "key";
    String strValue = "value";

    // remember: [ {}, {}, ... {} ]

    // create the first json object with temp data
    JsonObject obj0 = doc.createNestedObject();

    // obj0["key"] = "Temperature (F)";
    // obj0["value"] = random(60, 100);

    // obj0[strKey] = "Temperature (F)";
    // obj0[strValue] = random(60, 100);
    obj0[String("key")] = String("Temperature (F)");
    obj0[String("value")] = random(60, 100);

    // create a 2nd json object with humidity data
    JsonObject obj1 = doc.createNestedObject();
    obj1[strKey] = "Humidity (%)";
    obj1[strValue] = random(55, 80);

    // keep adding other json object to send
    //...
    latitude = String(latitude.toFloat() + 0.0001);
    longitude = String(longitude.toFloat() + 0.0001);

    String gps = latitude + "," + longitude;
    JsonObject obj2 = doc.createNestedObject();
    obj2[strKey] = "GPS";
    obj2[strValue] = gps;

    // step 3: convert the json document into a simple string (aka
    // "serializing")
    serializeJson(doc, jsonString);
    // takes json doc --> stores it as text in final string

    Serial.println(jsonString);

    Particle.publish("initial_state_json", jsonString);

    // String k = String(obj0["key"]);
    // Serial.println();

    delay(5000);
}