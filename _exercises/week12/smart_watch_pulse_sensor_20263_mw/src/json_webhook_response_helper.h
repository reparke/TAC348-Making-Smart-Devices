#pragma once

#include "Particle.h"
#include <ArduinoJson.h>

// Collect each webhook's numbered pieces separately.
// Return "" until a complete JSON response is ready.
// Supports four active webhook names, with up to ten pieces per response.
// Finish one request to a webhook before starting another request to that same webhook.
inline String json_webhook_response_helper(const char* event, const char* data) {
    const int MAX_WEBHOOKS = 4;
    const int MAX_PARTS = 10;
    const unsigned long RESPONSE_TIMEOUT = 20000;

    struct ResponseBuffer {
        String eventName;
        String parts[MAX_PARTS];
        bool havePart[MAX_PARTS] = {false};
        unsigned long lastPartTime = 0;
    };
    static ResponseBuffer responses[MAX_WEBHOOKS];

    if (event == nullptr || data == nullptr || event[0] == '\0') return "";

    // Numbered events end in /0, /1, etc. Unnumbered events are a single piece.
    String eventName = event;
    int partNumber = 0;
    int slash = eventName.lastIndexOf('/');
    if (slash >= 0 && slash + 1 < (int)eventName.length()) {
        const char* suffix = event + slash + 1;
        if (suffix[0] >= '0' && suffix[0] <= '9') {
            for (unsigned int i = 0; suffix[i] != '\0'; i++) {
                if (suffix[i] < '0' || suffix[i] > '9') return "";
                partNumber = partNumber * 10 + (suffix[i] - '0');
                if (partNumber >= MAX_PARTS) return "";
            }
            eventName = eventName.substring(0, slash);
        }
    }
    if (eventName.length() == 0) return "";

    unsigned long now = millis();
    int responseIndex = -1;
    int freeIndex = -1;
    for (int i = 0; i < MAX_WEBHOOKS; i++) {
        // Each webhook has its own timeout; another webhook cannot keep it alive.
        if (responses[i].eventName.length() > 0 &&
            now - responses[i].lastPartTime > RESPONSE_TIMEOUT) {
            responses[i] = ResponseBuffer();
        }
        if (responses[i].eventName == eventName) responseIndex = i;
        if (responses[i].eventName.length() == 0 && freeIndex < 0) freeIndex = i;
    }

    if (responseIndex < 0) {
        if (freeIndex < 0) return "";  // Keep the responses already in progress
        responseIndex = freeIndex;
        responses[responseIndex].eventName = eventName;
    }
    ResponseBuffer& response = responses[responseIndex];
    response.lastPartTime = now;
    response.parts[partNumber] = data;
    response.havePart[partNumber] = true;

    String jsonBuffer;
    for (int i = 0; i < MAX_PARTS; i++) {
        if (!response.havePart[i]) break;
        jsonBuffer += response.parts[i];
    }

    JsonDocument checkDoc;
    if (deserializeJson(checkDoc, jsonBuffer)) return "";

    response = ResponseBuffer();
    return jsonBuffer;
}
