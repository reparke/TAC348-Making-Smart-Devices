#include "Particle.h"
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

String latitudeUSC = "34.02051";
String longitudeUSC = "-118.28563";
String latitudeUCLA = "34.0689";
String longitudeUCLA = "-118.4452";
int battery = 100;

/*
 test out json -> generate a random temperature and random humidity

 How to send multiple values: from the IS documentation
    they want the following
    [ {}, {}, {}, ...]
    inside each json object, they want
    { "key":key1, "value":value1} --> ex: { "key":"temp", "value":"89.9"}
*/
void setup() { Serial.begin(9600); }

void loop() {
    // step 1: create the container that will store all the json
    StaticJsonDocument<380> document;

    // step 2: we store our data in the json document using the format
    //       initial state gave us

    // create obj
    JsonObject obj1 = document.createNestedObject();  // this create the {...}
    int temp = random(65, 88);
    obj1["key"] = "temperature";
    obj1["value"] = temp;

    JsonObject obj2 = document.createNestedObject();
    float humidity = random(40, 60);
    obj2["key"] = "humidity";
    obj2["value"] = humidity;

    JsonObject obj3 = document.createNestedObject();
    obj3["key"] = "battery";
    obj3["value"] = battery;

    // format for gps: "lat,long"
    String coordUSC = latitudeUSC + "," + longitudeUSC;
    String coordUCLA = latitudeUCLA + "," + longitudeUCLA;
    JsonObject obj4 = document.createNestedObject();
    obj4["key"] = "USC";
    obj4["value"] = coordUSC;
    JsonObject obj5 = document.createNestedObject();
    obj5["key"] = "UCLA";
    obj5["value"] = coordUCLA;

    // test out json document by printing out the json
    String output;                    // new variable
    serializeJson(document, output);  // convert our document into a string

    Serial.println(output);
    // publish to initial state
    Particle.publish("initial_state_json", output);
    delay(10000);
}

/*

    show gps and battery level
        --pretend (in code) you are starting with a 100% battery
            and you are starting at USC
        - use millis timer, every 5 seconds
            --decrease the battery timing
            --update your GPS coord

    For initial state, the GPS format is str: "latitude,longtitude"
                                ex: "45.38829,38.4855"
    step1: show static gps and battery

    step2: adjust battery level and gps
*/