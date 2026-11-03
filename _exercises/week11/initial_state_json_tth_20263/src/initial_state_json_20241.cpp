
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// step 1 for creating json: install and include library
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

/*
Goal: send a random temp and humid to IS in ONE SINGLE JSON msg
    with ONE WEBHOOK

IS expects the following format--string
Syntax:
    [
        {"key":"name1", "value":value1},
        {"key":"name2", "value":value2}
        ...
    ]

we could create this EXACT string manually
    --> however we usually use a library
    less errirs and generally easier


    now lets send MORE data -- GPS Data
    lat long

    IS show gps on a map if we use the following format
    "lat,lng"
*/

float lat = 34.0205;  // usc GPS coord - global var
float lng = -118.2856;

void setup() { Serial.begin(9600); }
void loop() {
    // step 2: create the json container to store what we want to send
    JsonDocument doc;

    // create the string which we will publish (starts as empty)
    String jsonPublishString = "";

    /* what IS wants
    [
        {"key":"Temperature (F)", "value":TEMP_VAR},
        {"key":"Humidity (%)", "value":HUMIDITY_VAR}
    ]

    */
    JsonArray array = doc.to<JsonArray>();  // outer container

    // create the first object
    JsonObject object0 = array.add<JsonObject>();
    object0["key"] = "Temperature (F)";
    object0["value"] = random(70, 90);

    JsonObject object1 = array.add<JsonObject>();
    object1["key"] = "Humidity (%)";    // label which will show up in IS
    object1["value"] = random(20, 60);  // value that will show up in IS

    // how can we simulate the gps position moving?
    // add alittle to the lat lng
    lat = lat + 0.0001;
    lng = lng + 0.0001;
    // format for IS
    String coords = String(lat) + "," + String(lng);

    JsonObject object2 = array.add<JsonObject>();
    object2["key"] = "GPS";
    object2["value"] = coords;

    // convert the json container into a string
    serializeJson(doc, jsonPublishString);

    // publish
    Serial.println(jsonPublishString);
    Particle.publish("initial_state_json", jsonPublishString);

    // we should use millis
    delay(10000);
}