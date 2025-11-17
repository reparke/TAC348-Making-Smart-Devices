
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

// step 3: create the myHandler function
void myHandler(const char* event, const char* data) {
    static String jsonBuffer;

    // two "const char *" params
    // for us, treat these like strings
    // the DATA param includes the entire json response
    // Serial.println(String(data));

    // these 5 lines are from the library and they convert the
    //  JSON string back into an object we manipulate in code

    int responseIndex = 0;
    const char* slashOffset = strrchr(event, '/');
    if (slashOffset) responseIndex = atoi(slashOffset + 1);
    if (responseIndex == 0) jsonBuffer = "";
    jsonBuffer += data;

    // Part 2 is where you can parse the actual data; you code goes in the IF

    // Test to see if was successful
    // StaticJsonDocument<2048> doc;
    DynamicJsonDocument doc(12288);
    DeserializationError error = deserializeJson(doc, jsonBuffer);
    if (!error) {
        // json: {"rise":"6:45:03 AM","set":"7:11:35 PM"}
        // String sunriseTime = doc["rise"];
        // String sunsetTime = doc["set"];
        // Serial.println("In LA, the sunset time is " + sunsetTime +
        //                " and the sunrise time is " + sunriseTime);
        Serial.println(String(jsonBuffer));
        Serial.println();
        float tempF = doc["current"]["temperature_2m"];
        int code = doc["current"]["weather_code"];
        int humidity = doc["current"]["relative_humidity_2m"];
        // Serial.println(String(data));
        Serial.println("The weather is " + String(tempF, 1) + " F and " +
                       String(humidity) + "% humidity with weather code " + (code));
        Serial.println();
    }
}

void setup() {
    // step 2: "listen" (AKA notify us) for this response
    //          when response comes, call the MYHANDLER function
    Particle.subscribe("hook-response/OpenMeteoJsonFull", myHandler,
                       MY_DEVICES);
    Serial.begin(9600);
}

void loop() {
    // step 1: trigger webhook by publishing
    Particle.publish("OpenMeteoJsonFull", "");
    delay(10000);
}