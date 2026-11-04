#pragma once

#include "Particle.h"

// Collect the numbered pieces. Return "" until the JSON is complete
inline String json_webhook_response_helper(const char* event, const char* data) {
    const int MAX_PARTS = 10;
    static String parts[MAX_PARTS];
    static bool havePart[MAX_PARTS] = {false};
    static unsigned long lastPartTime = 0;

    if (event == nullptr || data == nullptr) return "";

    // Forget an unfinished response if its next piece never arrived
    if (millis() - lastPartTime > 20000) {
        for (int i = 0; i < MAX_PARTS; i++) {
            parts[i] = "";
            havePart[i] = false;
        }
    }
    lastPartTime = millis();

    String eventName = event;
    int slash = eventName.lastIndexOf('/');
    if (slash < 0) return "";
    int partNumber = eventName.substring(slash + 1).toInt();
    if (partNumber < 0 || partNumber >= MAX_PARTS) return "";

    parts[partNumber] = data;
    havePart[partNumber] = true;

    // Put together the pieces we have, starting with piece 0
    String jsonBuffer;
    for (int i = 0; i < MAX_PARTS; i++) {
        if (!havePart[i]) break;
        jsonBuffer += parts[i];
    }

    // Try parsing to see if all the pieces have arrived
    JsonDocument checkDoc;
    if (deserializeJson(checkDoc, jsonBuffer)) return "";

    for (int i = 0; i < MAX_PARTS; i++) {
        parts[i] = "";
        havePart[i] = false;
    }
    return jsonBuffer;
}
