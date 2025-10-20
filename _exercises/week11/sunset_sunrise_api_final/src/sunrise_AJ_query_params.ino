#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

String latitude = "48.8566";
String longitude = "2.3522";

void setup() {
    Serial.begin(9600);
    Particle.subscribe("hook-response/sunrise_sunset_params",
                       jsonSubscriptionHandler);
}
void sunriseAPI() {
    /*
        This function uses the particle integration: Sunrise Sunset with
       Mustache
       The lat and lon are hard-coded into the URL
    */

    Particle.publish("sunrise_sunset_params", "", PRIVATE);
    // Wait 60 seconds
    delay(10000);
}

void sunriseAPIQueryParam() {
    /*
    This function uses the particle integration: Sunrise Sunset with
   Mustache and Query Param

   The lat and lon are sent via JSON
*/
    StaticJsonDocument<1024> doc;  // object to store JSON response
    String
        output;  // will store JSON string which is used for Particle.publish()

    /* Here is where JSON creation code goes */

    // for query params, don't created a nested object
    doc["lat"] = latitude;
    doc["lng"] = longitude;

    serializeJson(doc, output);  // create JSON string

    Particle.publish("sunrise_sunset_params", output, PRIVATE);
    // Wait 60 seconds
    delay(10000);
}
void loop() {
    sunriseAPI();
    // sunriseAPIQueryParam();
}

void jsonSubscriptionHandler(const char *event, const char *data) {
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }

    /* Here is where your parsing code goes */

    String sunrise = doc["sunrise"];  // "los angeles"
    String sunset = doc["sunset"];    // 89

    Serial.println("Sunrise: " + sunrise + ", Sunset: " + sunset);
}
