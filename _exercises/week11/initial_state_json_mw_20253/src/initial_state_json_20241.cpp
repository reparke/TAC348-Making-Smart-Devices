
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

void setup() { Serial.begin(9600); }

/*
 let's send a random temperature and humidity to IS with JSON

 IS docs - format for SINGLE data point
    { "key": LABEL, "value": VALUE } --> { "key": "Humidity", "value": 45 }

format for multiple values
    [ {}, {}, ... {} ]
     ex:    [ { "key": "Humidity", "value": 45 },
              { "key": "Te  mperature (F)", "value": 78 },
              { "key": "Light Level", "value": "ambient" }
             ]

we could create these strings by hand, but that's awful!
    --> instead! we use libraries


*/
// String latitude = "34.0224";
// String longitude = "-118.2851";
float latitudeF = 34.0224;
float longitudeF = -118.2851;
int battery = 100;

void loop() {
    int tempF = random(70, 90);
    int humidity = random(20, 70);

    StaticJsonDocument<1024> doc;  // json object we are creating
    String output = "";            // text version of our json we send to IS

    /*
        [
            {"key":"Temperature F", "value":tempF},
            {"key:"Humidity", "value":humidity}
        ]

        BUT! there is a bug in ArduinoJson library with strings
        --> when we use string literals, we have to cast it to a string

        instead of this
                obj0["key"] = "Temperature (F)";
        we have to type
                obj0[String("key")] = String("Temperature (F)");


        NOW
        send battery level and GPS coordinates 
            battery level: start a int at 100, and decrease by 5 each time
            GPS will move: 
                format of IS GPS  "lat,lng" --> "53.35, 48.33"
                start at USC, and move each time you publish

    */
    // tempF json object
    JsonObject obj0 = doc.createNestedObject();
    obj0[String("key")] = String("Temperature (F)");
    obj0[String("value")] = tempF;

    //humidity object
    JsonObject obj1 = doc.createNestedObject();   
    obj1[String("key")] = String("Humidity (%)");
    obj1[String("value")] = humidity;

    // //gps
    // latitude = String(latitude.toFloat() + 0.0001);
    // longitude = String(longitude.toFloat() + 0.0001);

    // String gps = latitude + "," + longitude;
    // JsonObject obj2 = doc.createNestedObject();
    // obj2[String("key")] = String("GPS");
    // obj2[String("value")] = gps;

    //battery
    battery = battery - 5;
    if (battery < 0) {
        battery = 100;
    }
    JsonObject obj3 = doc.createNestedObject();
    obj3[String("key")] = String("battery");
    obj3[String("value")] = battery;

    // gps
    latitudeF = latitudeF + 0.0001;
    longitudeF = longitudeF + 0.0001;

    String gpsF = String(latitudeF) + "," + String(longitudeF);
    JsonObject obj4 = doc.createNestedObject();
    obj4[String("key")] = String("GPS Float");
    obj4[String("value")] = gpsF;

    //keep adding objects...

    //converts the variable in memory to a string can send.
    serializeJson(doc, output);

    Serial.println(output);
    Particle.publish("initial_state_json", output);

    delay(5000);


}