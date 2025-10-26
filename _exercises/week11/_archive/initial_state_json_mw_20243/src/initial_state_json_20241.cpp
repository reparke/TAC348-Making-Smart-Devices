
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

/*
    How to send multiple values to initial state - JSON
        one value:  { "key": label1, "value": value1}
        multiple: [ {}, {}, ...]

    send GPS location - make this USC
    send battery level
        battery level should decrease each time you publish
    format for GPS is  
        latitude,longtitude     -->  "32.543345,-10.54334"

*/

int battery = 100;
// float lat = 34.0224;    //34.0224000000001 causes error
String lat = "34.0224";
String lng = "-118.2851";

void setup() { Serial.begin(9600); }

void loop() {

    int temperature = random(68, 95);
    float humidity = random(34, 60);

    battery -= 5;
    if (battery <= 0 ) {
        battery = 100;
    }
    //initial state format
    lat = String(lat.toFloat() - 0.005);
    lng = String(lng.toFloat() + 0.005);

    String gps = lat+","+lng;

    //step 1: create our JSON "document" that will store all our data for initial
    StaticJsonDocument<1024> doc;
    String jsonString;

    //step 2: add the data to our document
    JsonObject obj0 = doc.createNestedObject();
    obj0["key"] = "Temp F";
    obj0["value"] = temperature;

    JsonObject obj1 = doc.createNestedObject();
    obj1["key"] = "Humidity (%)";
    obj1["value"] = humidity;

    JsonObject obj2 = doc.createNestedObject();
    obj2["key"] = "Battery";
    obj2["value"] = battery;

    JsonObject obj3 = doc.createNestedObject();
    obj3["key"] = "GPS";
    obj3["value"] = gps;

    //step 3: "serialize" the JSON doc into astring
    serializeJson(doc, jsonString);
    //now, String jsonString contains what we want send to initial state

    Particle.publish("initial_state_json", jsonString);

    delay(5000);

}