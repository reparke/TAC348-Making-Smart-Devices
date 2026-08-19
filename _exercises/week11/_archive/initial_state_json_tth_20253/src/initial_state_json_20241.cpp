
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// creating json
// step 1: include the library and set a value
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

int battery = 100;
float lat = 34.0224;
float lng = -118.2851;
/*
let's send a random temp and humid to IS using JSON and ONE webhook
    IS docs:
    single datapoint: {"key": "temp", "value": 32}

    why not just: {"temp": 32} --> initial state's decision

    multiple datapoints
        [ {}, {}, ... {}]
    ex:    [ {"key":"temp", "value": 32},
             {"key":"humidity", "value": 55}
            ]
    while we could make our json string by hand, no one does!
        --> library instead

*/

/*
    NOW....send battery levl and GPS coordinates
        each datapoint is going to change each time we publish
    
        battery level starts at 100: decrease by 5 each time
        --> int

        GPS: start at USC and move just a little each time
        --> this has a specific format in IS
        GPS : "lat,lng"

        "GPS" : "55.33939,38.99898"


*/

void setup() { Serial.begin(9600); }



void loop() {
    // step 2: create the JSON container which store the data we're building
    StaticJsonDocument<1024> doc;
    String output = "";  // the final string we publish

    int tempF = random(70, 90);
    int humidity = random(20, 60);

    /*
    what exactly are doing? create this string below
    [
        {"key":"Temperature (F)", "value":tempF},
        {"key":"Humidity (%)", "value":humidity}
    ]
    */

    // step 3: build the json data
    JsonObject obj0 = doc.createNestedObject();
    // obj0["key"] = "Temperature (F)";
    // obj0["value"] = tempF;

    // BUT! there is a bug in the arduinojson library
    //  when use string literals, we need to explicity cast it to a string
    obj0[String("key")] = String("Temperature (F)");
    obj0[String("value")] = tempF;

    // humidity
    JsonObject obj1 = doc.createNestedObject();
    obj1[String("key")] = String("Humidity (%)");
    obj1[String("value")] = humidity;

    // battery
    battery = battery - 5;
    if (battery < 0) {
        battery = 100;
    }
    JsonObject obj2 = doc.createNestedObject();
    obj2[String("key")] = String("Battery (%)");
    obj2[String("value")] = battery;

    // gps
    lat = lat + 0.00001;
    lng = lng + 0.00001;
    String coords = String(lat) + "," + String(lng);  // "34.9,55.4"
    JsonObject obj3 = doc.createNestedObject();
    obj3[String("key")] = String("GPS");
    obj3[String("value")] = coords;

    // step 3: turn our json data into a string
    serializeJson(doc, output);

    Serial.println(output);
    Particle.publish("initial_state_json", output);

    delay(5000);
}