#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

// event driven programming just link BLYNK_WRITE
void myHandler(const char *event, const char *data) {
    // Handle the integration response
    // const char * is a c++ variable type
    // think of event as a string, it is "sunrise_sunset"
    // think of data as a string, it is the entire JSON response
    // Serial.println("In myhandler: received json response");
    // Serial.println(String(data));

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }

    // here is where actually PARSE or read out specific values from the data
    String sunriseTime = doc["sunrise"];
    String sunsetTime = doc["sunset"];
    Serial.println("The sunrise in LA is at " + sunriseTime + " and the sunset is at " + sunsetTime);
    

}

void setup() {
    Serial.begin(9600);
    // Subscribe to the integration response event
    Particle.subscribe("hook-response/sunrise_sunset", myHandler, MY_DEVICES);
}



void loop() {
    // Get some data
    String data = String(10);
    // Trigger the integration
    Serial.println("In loop: about to publish to API");
    Particle.publish("sunrise_sunset", data, PRIVATE);
    // Wait 60 seconds
    delay(10000);
}
