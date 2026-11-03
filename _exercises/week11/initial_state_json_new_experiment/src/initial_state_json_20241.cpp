
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// step 1 to send json
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

/*
Goal: send a random temp and humid to IS in one SINGLE JSON MESSAGE
    JUST ONE WEBHOOK

from the IS docs
    syntax: { "key":"temperature", "value": 76 }

multiple json values uses an array
    [
        { "key": "temperature", "valud": 76},
        { "key": "humidity", "value" : 54}
    ]

we could create this EXACT string manually
    --> most of the time, we would rather use a library
        less errors and generally easier

NOW lets send MORE data!

    send battery level

    lets send GPS
*/

int battery = 100; //fake battery %
float lat = 34.0224;
float lng = -118.2851;      //USC's GPS coord

//goal: adjust battery and gps on every publish


void setup() {
    Serial.begin(9600);
}
void loop() {
    //step 2: create the json document (or container) -- library
    JsonDocument doc;
    JsonArray readings = doc.to<JsonArray>(); //outer container: [ ]
    //create string to hold our final json string for IS
    String finalJsonString = "";

/*
    what are we building? we need the EXACT string below

    [
        { "key" : "Temperature (F)", "value" : temp_var} ,
        { "key" : "Humidity (%)",    "value" : humidity_var}
    ]
*/
    battery = battery - 5;
    //how do simulate GPS coords moving?
    lat = lat + 0.0001;
    lng = lng + 0.0001;

    //IS will map GPS for you automatically
    //format:  "lat,lng"
    String gpsCoords = String(lat) + "," + String(lng);

//step 3: build the json data
    //library code syntax
    JsonObject object0 = readings.add<JsonObject>();
    // object0["key"] = "Temperature (F)";
    object0["key"] = String("Temperature (F)");         //bug here with strings
    object0["value"] = random(70,90);

    JsonObject object1 = readings.add<JsonObject>();
    // object1["key"] = "Humidity (%)";
    object1["key"] = String("Humidity (%)");        //bug
    object1["value"] = random(20, 70);

    JsonObject object2 = readings.add<JsonObject>();
    object2["key"] = String("Battery (%)");
    object2["value"] = battery;

    JsonObject object3 = readings.add<JsonObject>();
    object3["key"] = String("GPS");
    object3["value"] = gpsCoords;

    //add any other json objects you need

    //step 4: convert our json data/container into a string
    serializeJson(doc, finalJsonString);

    //step 5: send data to cloud
    Serial.println(finalJsonString);
    Particle.publish("initial_state_json", finalJsonString);

    //we use millis
    delay(7000);


}
