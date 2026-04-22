
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

//include the library
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

/*
green check: full screen side by side workbench + browser
red x:       one screen where I switch back forth
*/

// void myHandler(const char* event, const char* data) {
//     // Handle the integration response
//     //we const char * --> technically this is a C++ character array
//     // however! we can think of it as a string
//     String jsonResponse = String(data);
//     Serial.println("\n ** JSON Response **");
//     Serial.println(jsonResponse);

// }


/*
    why might we want to limit receiving on the photon that we don't care about?
    -
    -harder to parse
    -take of memory of photon (limited memory)
    -slower because more to send / receive
    -BATTERY! one of the heavy battery drains is network activitt
    -cost of bandwidth
*/

void myHandler(const char* event, const char* data) {
    // Part 1 allows for webhook responses to be delivered in multple "chunks";
    // you don't need to change this
    static String jsonBuffer;  // store json response
    int responseIndex = 0;
    const char* slashOffset = strrchr(event, '/');
    if (slashOffset) responseIndex = atoi(slashOffset + 1);
    if (responseIndex == 0) jsonBuffer = "";
    jsonBuffer += data;

    // Part 2 is where you can parse the actual data; you code goes in the IF
    DynamicJsonDocument doc(12288);
    DeserializationError error = deserializeJson(doc, jsonBuffer);

    if (!error) {  // Test to see if was successful

        //we want temp, humidity, wind sepeed
        // wind speed units
        float tempF = doc["current"]["temperature_2m"];
        int windSpeed = doc["current"]["wind_speed_10m"];
        String windSpeedUnits = doc["current_units"]["wind_speed_10m"];


        Serial.println("The temp in LA is " + String(tempF,1) + " and the wind speed is " + String(windSpeed) + " " + windSpeedUnits);

        // add to the print statement the wind speed and units
    }
}

void setup() {
    Serial.begin(9600);
    //this tells cloud that we want to be notifed when a response comes back
    Particle.subscribe("hook-response/open_meteo_json", myHandler, MY_DEVICES);
}
void loop() {
    //trigger the webhook
    Serial.println("\n--Publishing request --");
    Particle.publish("open_meteo_json", "");
    //use millis :)
    delay(5000);

}


/*
EVENT DRIVEN PROGRAMMING!
    -bluetooth -- onDataReceived
    -Blynk    -- BLYNK_WRITE

when the response come back from cloud, because we have SUBSCRIBED to the response
    the photon will be notified
    AND THEN the photon will AUTOMAGICALLY call the event handler
*/















/*
    with APIS, often there a Pub/Sub model (publish and subscribe)
*/





