
#include "Particle.h"


// these two lines MUST BE BELOW #include "Particle.h"
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

float lat = 34.0224;
float lng = -118.2851;

/*
Let's  send a random temp and humid using JSON to initial state with ONE webhook
    IS docs:
    single entity / data point
    ex: { "key" : "humidity", "value" : 87}

        could IS have been designed to accept instead {"humidity":87}? YES

    ex: multiple datapoints
    [ {}, {} , ... {}]
    [
        { "key" : "humidity", "value" : 87}],
        { "key" : "temperature", "value" : 75.6}
    ]
    
    we COULD do create this JSON string by hand / code manually
            --> NO ONE DOES THIS!
        instead, use a library

How to send JSON to initial state
-----
step 1) set up intial state
step 2) create webhook
step 3) workbench code
    A) install library ArduinoJson
    B) include library AND add enable string
    C) create the json and send to cloud


    Challenge: show gps on map in initial state
        format
        "GPS": "44.440,54.333"  <--- try to modify what we have to so far so USC coord
        bonus: try to get the coord to move
*/
void setup() {
    Serial.begin(9600);
}
void loop() {
    //create the JSON container which will store our data
    StaticJsonDocument<1024> doc;  // this is C++....don't worry about it
    String finalMessage = "";       // data string we send to initial state

    //create random values
    int tempF = random(65,100);
    int humidity = random(20,60);

    /*
        what are we ACTUALLY trying to do? create the following string for IS
        [
            { "key" : "Temperature (F)", "value" : tempF   } ,
            { "key" : "Humidity (%)",    "value" : humidty }
        ]

    */

    //create the json data
    JsonObject object0 = doc.createNestedObject();
    // object0["key"] = "Temperature (F)";   //<----- there is bug!
    object0["key"] = String("Temperature (F)");     //add String() around strings
    object0["value"] = tempF;

    //make NEXT json object
    JsonObject object1 = doc.createNestedObject();
    object1["key"] = String("Humidity (%)");
    object1["value"] = humidity;

    lat = lat + 0.00001;
    lng = lng + 0.00002;
    String coords = String(lat) + "," + String(lng);
    JsonObject object2 = doc.createNestedObject();
    object2["key"] = String("GPS");
    object2["value"] = coords;

    //we are done creating json data...
    //      --> now let's make it a string and publish

    //to turn json container into json string
    serializeJson(doc, finalMessage);
    Serial.println(finalMessage);
    Particle.publish("initial_state_json", finalMessage);

    //should use millis
    delay(5000);
}


