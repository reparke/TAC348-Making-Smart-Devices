
/*
 to send multiple readings to initial state,
    for ex: temp = 89 and humid = 45
    they want the json to look like
    [ {}, {} ]
    -->
    [ {"key":"temp", "value":"89"},     {"key":"humid", "value":"45"}   ]
*/

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

void setup() { Serial.begin(9600); }

void loop() {
    // create the JSON "document" (1024 bytes is a good maximum)
    StaticJsonDocument<1024> doc;  // this is like the outer [  ]

    // we need to create the nested json object for the temperature
    JsonObject obj1 = doc.createNestedObject();  // this creates the first { }
                                                 // inside the main outer [ ]
    obj1["key"] = "temperature";
    obj1["value"] = random(65, 89);  // random temperature

    // need to create second nested object
    JsonObject obj2 = doc.createNestedObject();
    obj2["key"] = "humidity";
    obj2["value"] = random(45, 75);

    JsonObject obj3 = doc.createNestedObject();
    obj3["key"] = "USC";
    latitudeUSC = String(latitudeUSC.toFloat() + 0.01);
    longitudeUSC = String(longitudeUSC.toFloat() - 0.01);
    obj3["value"] = String(latitudeUSC + "," + longitudeUSC);

    JsonObject obj4 = doc.createNestedObject();
    obj4["key"] = "UCLA";
    obj4["value"] = String(latitudeUCLA + "," + longitudeUCLA);

    // now we just need to convert this json document to a string
    // make new variable
    String jsonString;
    serializeJson(doc, jsonString);

    Serial.println(jsonString);
    Particle.publish("initial_state_json", jsonString);
    delay(10000);
}

/*
    we want to send 3 more readings in our JSON
        -battery level (int 100)
        -GPS coordinates of USC
        -GPS coordinates of UCLA

    for initial state, the format they want for GPS is
        String    "lat,long" --> "45.599,38.9880"


    IF you get that done, they try to move the GPS coords for USC
        slowly

*/