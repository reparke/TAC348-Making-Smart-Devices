
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

int battery = 100;
String lat = "34.0224";
String lng = "-118.2851";

float f = 4.0003;   // 4.00030000001

void setup() { Serial.begin(9600); }

/*
    want to send multiple values to IS at the same time
        format: [ {}, {}, {}, ....]
        object: {"key": IS_LABEL, "value":IS_VALUE}
        ex:     {"key":"Humidity (%)", "value":34.3}


    Now!
        add two more data items to IS
        battery level: start at 100, and decrease by 5 every time
                            (reset to 100 when it gets to zero)

        GPS data
            format: "lat,lng"       -> "53.2922,-105.4334"
            send the GPS coords for USC
            for challenge: try to get the GPS plot to move
*/

void loop() {
    int temp = random(60,90);
    float humidity = random(0,100);

    battery -= 5;
    if (battery <= 0) {
        battery = 100;
    }

    //IS gps format is "lat,lng"
    lat = String(lat.toFloat() + 0.001);
    lng = String(lng.toFloat() - 0.003);
    String gps = lat + "," + lng;


    //step 1: create the blank json document which store all our data
    StaticJsonDocument<1024> doc;
    String finalJsonString;             //store the string we send to IS

    //step 2: build out the json documen
    //create 1st json object
    JsonObject obj0 = doc.createNestedObject();
    //now add the data
    obj0["key"] = "Temperature (F)";
    obj0["value"] = temp;

    //now create NEXT json obj
    JsonObject obj1 = doc.createNestedObject();
    obj1["key"] = "Humidity (%)";
    obj1["value"] = humidity;

    JsonObject obj2 = doc.createNestedObject();
    obj2["key"] = "GPS Coordinates";
    obj2["value"] = gps;

    JsonObject obj3 = doc.createNestedObject();
    obj3["key"] = "Battery Level (%)";
    obj3["value"] = battery;

    //step 3: convert this json document into a simple string (aka "serializing")
    serializeJson(doc, finalJsonString);    
    // takes doc --> stores into finalJsonString

    //step 4: send serialize string to IS
    Particle.publish("initial_state_json", finalJsonString);

    delay(5000);


}