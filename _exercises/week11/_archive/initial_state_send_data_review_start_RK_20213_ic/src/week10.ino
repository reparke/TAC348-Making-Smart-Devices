#include "JsonParserGeneratorRK.h"
/*
How to send multiple values to Initil format : [ {}, {} ] ex :
[
    {"key" : "temperature" : "value" : TEMP_VAR},
    {"key" : "weather", "value" : "WEATHER_VAR"}
]
*/

// 34.0224° N, 118.2851° W
// GPS format for initial state
// "LAT,LONG"
// "key":"favorite_place", "value":COORD
// add GPS coord that slowly increases so map moves
// add a battery value that slowly decreases to 100 to 0

int batteryLevel = 100;
float latitude = 34.0224;
float longitude = -118.2851;
unsigned long prevMillis = 0;
const unsigned long UPDATE_DELAY = 5000;

int temperature = 0;
String lightValue = "";

void setup() { Serial.begin(9600); }
void publishJson() {
    // create the object (tool) that is going to our json
    JsonWriterStatic<622> jw;
    // initialize this object
    jw.init();

    // create a set of curly braces
    {
        // create the array
        JsonWriterAutoArray jsonArray(&jw);

        jw.startObject();  // crates the first obj
        jw.insertKeyValue("key", "temperature");
        jw.insertKeyValue("value", temperature);
        jw.finishObjectOrArray();

        // now we do lightvalue
        jw.startObject();
        jw.insertKeyValue("key", "light value");
        jw.insertKeyValue("value", lightValue);
        jw.finishObjectOrArray();

        jw.startObject();
        jw.insertKeyValue("key", "battery value");
        jw.insertKeyValue("value", batteryLevel);
        jw.finishObjectOrArray();

        String coordinate = String(latitude) + "," + String(longitude);
        jw.startObject();
        jw.insertKeyValue("key", "my coordinates");
        jw.insertKeyValue("value", coordinate);
        jw.finishObjectOrArray();
    }
    Serial.println(jw.getBuffer());
    Particle.publish("week10_initial_state", jw.getBuffer());
}

void loop() {
    temperature = random(70, 100);  // generate random temperature
    int lightLevel = random(0, 4095);
    if (lightLevel > 3000) {
        lightValue = "dark";
    } else if (lightLevel > 1500) {
        lightValue = "ambient";
    } else {
        lightValue = "bright";
    }

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > UPDATE_DELAY) {
        prevMillis = currMillis;
        batteryLevel = batteryLevel - 10;  // decrease battery level
        if (batteryLevel < 0) {
            batteryLevel = 100;
        }
        latitude = latitude + 0.01;
        longitude = longitude + 0.01;

        publishJson();
    }
}