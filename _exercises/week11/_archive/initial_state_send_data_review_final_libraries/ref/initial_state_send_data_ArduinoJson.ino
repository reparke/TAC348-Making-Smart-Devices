#include <Arduino.h>
#define ARDUINOJSON_ENABLE_PROGMEM 0
#include <ArduinoJson.h>
/*
How to send single values to Initial state in JSON format
  format: {}
  ex:
    {"key":"temperature", "value":79}

How to send multiple values to Initil
  format: [ {}, {} ]
  ex:
    [
      {"key":"temperature":"value":TEMP_VAR},
      {"key":"weather", "value":"WEATHER_VAR"}
    ]
    */

// format for GPS
// lat,long       --> "23.4993,343.3999"

/*
  send data to initial state
  - Create a "bucket" at IS which has our ACCESS KEY and BUNDLE KEY
  - Create a Webhook in Particle console (with ACCESS KEY and BUNDLE KEY) so our
  data gets relay to IS
  - Create string value that has JSON data we want to send to IS
  - Publish the string to via Particle.cloud
*/

String latitudeUSC = "34.02051";
String longitudeUSC = "-118.28563";
String latitudeUCLA = "34.0689";
String longitudeUCLA = "-118.4452";
int battery = 100;

unsigned long batteryDecreaseTime = 3000;
unsigned long prevMillis = 0;

void setup() { Serial.begin(9600); }

void loop() {
    unsigned long curMillis = millis();
    if (curMillis - prevMillis >
        batteryDecreaseTime) {  // decrease battery level by 10% ever 3 sec
        battery = battery - 10;
        if (battery == 0) {  // reset battery to 100% when it gets to 0%
            battery = 100;
        }
        latitudeUSC = String(latitudeUSC.toFloat() + 0.01);
        longitudeUSC = String(longitudeUSC.toFloat() - 0.01);
        prevMillis = curMillis;
    }

    /*
        [
          {"key" : "location" : "value" : "34.33,-193.00"},
         {"key" : "battery", "value" : battery}
         ]
    */

    //  publishJSONManually();
    publishJSONArduinoJSON();

    delay(10000);
}
// DynamicJsonDocument doc(200);
void publishJSONArduinoJSON() {
    String coordsUSC = latitudeUSC + "," + longitudeUSC;
    String coordsUCLA = latitudeUCLA + "," + longitudeUCLA;

    // Allocate the JSON document
    //
    // Inside the brackets, 200 is the RAM allocated to this document.
    // Don't forget to change this value to match your requirement.
    // Use arduinojson.org/v6/assistant to compute the capacity.
    StaticJsonDocument<192> doc;

    
    JsonObject doc_0 = doc.createNestedObject();
    doc_0["key"] = "locationUSC";
    doc_0["value"] = coordsUSC;

    JsonObject doc_1 = doc.createNestedObject();
    doc_1["key"] = "locationUCLA";
    doc_1["value"] = coordsUCLA;

    JsonObject doc_2 = doc.createNestedObject();
    doc_2["key"] = "battery";
    doc_2["value"] = battery;

    String msg;
    serializeJson(doc, msg);

    // // Generate the minified JSON and send it to the Serial port.

    // // Start a new line
    Serial.println(msg);

    // Generate the prettified JSON and send it to the Serial port.
    //
    // serializeJsonPretty(doc, Serial);
    // The above line prints:
    // {
    //   "sensor": "gps",
    //   "time": 1351824120,
    //   "data": [
    //     48.756080,
    //     2.302038
    //   ]
    // }
    Particle.publish("week10_20203", msg);
}