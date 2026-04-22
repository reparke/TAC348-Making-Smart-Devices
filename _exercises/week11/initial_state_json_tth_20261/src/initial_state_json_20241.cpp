
#include "Particle.h"
//under particle.h

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// step 1 to sending json
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

/*
    send a random temp and humidity to IS in one single JSON message
    from IS docs:
        syntax: { "key": "temperature", "value": 76}

    multiple values
        [
            { "key": "temperature", "value": 76} ,
            { "key": "humidity", "value": 54}
        ]
    we could create this string manually    --> most of time we WONT do that
    -->  instead, we use a library to create and to read JSON

    NOW! let's send more data
        send battery level and GPS coords

        battery level starts at 100 and decrease by 5 loop()    reset when gets to zero

        GPS: send coordinates for USC
            IS format is
            "GPS" : "lat,lng"

            "GPS": "34.22922,88.33333"

            for challenge, try move the gps coord each
*/

int battery = 100;
float lat = 34.0224;
float lng = -118.2851;

void setup() {
    Serial.begin(9600);
}
void loop() {
    //step 2: create json docuemnt (or container)
    StaticJsonDocument<1024> doc;
    String finalJsonString = ""; //this is what we sent to inital state

    //generate our random data
    int tempF = random(70, 90);
    int humidity = random(20,60);

    battery = battery - 5;
    if (battery < 0) {
        battery = 100;
    }

    //how can we simulate GPS changing
    lat = lat + 0.0001;
    lng = lng + 0.0001;
    String coords = String(lat) + "," + String(lng); // IS format for GPS

    /*
    what are we trying to do?  we want to create the following string
    [
        { "key" : "Temperature (F)", "value" : tempF    } ,
        { "key" : "Humidity (%),     "value" : humidity } 
    ]
    */
    //step 3: build the json data
    JsonObject object0 = doc.createNestedObject();
    // object0["key"] = "Temperature (F)";  //but ther is a bug in the library
    object0["key"] = String("Temperature (F)");  //just use this for string literals
    object0["value"] = tempF;

    //add next one
    JsonObject object1 = doc.createNestedObject();
    object1["key"] = String("Humidity (%)");
    object1["value"] = humidity;

    // add battery
    JsonObject object2 = doc.createNestedObject();
    object2["key"] = String("Battery Level");
    object2["value"] = battery;

    // add gps
    JsonObject object3 = doc.createNestedObject();
    object3["key"] = String("GPS");
    object3["value"] = coords;

    // ... add other json data here

    // step 4: convert our json data / container into a string to send to particle
    serializeJson(doc, finalJsonString);

    // step 5: send data to cloud
    Serial.println(finalJsonString);
    Particle.publish("initial_state_json", finalJsonString);

    //we should use millis...
    delay(7000);


}
