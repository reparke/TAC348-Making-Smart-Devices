
// Basic Particle + Arduino‑style example for beginners
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// Optional: include ArduinoJson only if/when you want to parse
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

// This handler buffers multipart webhook responses like alt/example.cpp,
// but uses ArduinoJson to detect when the full JSON is ready.
void myHandler(const char* event, const char* data) {
    static String jsonBuffer;     // holds the growing JSON text

    // Get the part index from the event name: .../0, /1, ... or 'last'
    int responseIndex = 0;
    bool isLast = false;
    const char* slash = event ? strrchr(event, '/') : nullptr;
    if (slash) {
        const char* tail = slash + 1;
        if (strcmp(tail, "last") == 0) {
            isLast = true;       // treat 'last' as the end marker
        } else {
            responseIndex = atoi(tail); // 0 for first part, 1 for second, etc.
        }
    }

    // Clear on the first part only (ignore 'last' which would atoi() to 0)
    if (responseIndex == 0 && !isLast) {
        jsonBuffer = "";
    }

    // Append this chunk (guard against null)
    if (data) {
        jsonBuffer += data;
    }

    // Try to parse whenever new data arrives. If the JSON isn't complete yet,
    // ArduinoJson will fail, and we just wait for more chunks.
    DynamicJsonDocument doc(12288);
    DeserializationError err = deserializeJson(doc, jsonBuffer);
    if (!err) {
        // 1) Show students the FULL JSON first
        Serial.println("\n--- Open-Meteo FULL JSON ---");
        Serial.println(jsonBuffer);
        Serial.println("--- end ---\n");

        // 2) Optional: starter parsing example (students can modify)
        // float temp = doc["current_weather"]["temperature"].as<float>();
        // Serial.println(String("Parsed temp: ") + temp + " C");

        // Ready for the next message
        jsonBuffer = "";
    }
}

void setup() {
    // 1) Connect Serial for debugging
    Serial.begin(9600);
    // 2) Listen for webhook responses from the Particle Cloud
    Particle.subscribe("hook-response/OpenMeteoJsonFull", myHandler, MY_DEVICES);
}

void loop() {
    // 3) Request data from your webhook (set up in the Console)
    Particle.publish("OpenMeteoJsonFull", "");
    delay(10000); // wait 10 seconds between requests
}

/*
    temperature, city name, weather description
*/
