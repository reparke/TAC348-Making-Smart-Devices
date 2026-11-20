#include "Particle.h"

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

#include "json_webhook_response_helper.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#include "pulsecheck_setup.h"
/*
  PulseCheck: Fitbit data -> Particle webhook -> Gemini -> RGB LED

  Press the button to send the next 10-minute dataset of real Fitbit data
  (A-E for Part 1, F-H for Part 2; set PART in pulsecheck_setup.h). Gemini
  answers with JSON:
    {"state": "workout", "alert": false, "msg": "Great pace, avg 156 bpm!"}
  onWebhookReply() below unpacks it and shows it on the RGB LED.

  Libraries (already listed in project.properties)
    ArduinoJson     unpacks JSON
    GeminiWebhook   sending, waiting, timeout (reusable in any project)

  Files
    pulsecheck.cpp                   this file
    pulsecheck_setup.h               the button, the LED, and the Fitbit data
    json_webhook_response_helper.h   joins a webhook reply that arrives in pieces
    fitbit_data.h                    the numbers

  Wiring: RGB LED on SCL (red), MISO (green), MOSI (blue), each with a
  330 Ohm resistor, long leg to GND. Button on D5 with a 10k Ohm resistor.

  Open the serial monitor to see Gemini's answer for each dataset:
    particle serial monitor --follow

  LED
    white          waiting for Gemini
    green          resting
    yellow         walking
    orange         workout
    blue           sleep
    blinking red   alert
    magenta        error (webhook error, timeout, or an answer we don't know)
*/

/* onWebhookReply()
    Event handler for the webhook's reply. data holds Gemini's whole reply.
    Inside it, as text, is the answer your prompt asked for, for example
    {"state": "workout", "alert": false, "msg": "Great pace!"}
*/
void onWebhookReply(const char* event, const char* data) {
    // A long reply arrives in pieces. This returns "" until all of it is here.
    String fullJson = json_webhook_response_helper(event, data);
    if (fullJson == "") return;
    if (!geminiGotReply()) return;               // stops the timeout; ignores late replies

    // Step 1: unpack Gemini's reply. The answer is the text deep inside it.
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, fullJson);
    if (error) {
        onGeminiError("Reply was not JSON");
        return;
    }
    String answerText = doc["candidates"][0]["content"]["parts"][0]["text"].as<String>();

    // Step 2: that text is JSON too, so unpack it the same way.
    JsonDocument answer;
    error = deserializeJson(answer, answerText);
    if (error) {
        onGeminiError("Gemini's answer was not JSON");
        return;
    }
    String state = answer["state"].as<String>(); // "resting", "walking", "workout", or "sleep"
    bool alert = answer["alert"];                // true or false
    String msg = answer["msg"].as<String>();     // a short note

    logAnswer(state, alert, msg);                // print it to the serial monitor
    if (safetyRuleFired()) alert = true;         // the safety rule wins, whatever Gemini says

    // show it on the RGB LED
    if (alert)                    showAlert();                   // blinking red
    else if (state == "resting")  changeLedColor(0, 255, 0);     // green
    else if (state == "walking")  changeLedColor(255, 200, 0);   // yellow
    else if (state == "workout")  changeLedColor(255, 80, 0);    // orange
    else if (state == "sleep")    changeLedColor(0, 0, 255);     // blue
    else                          changeLedColor(255, 0, 255);   // magenta: a state we don't know
}

/* onGeminiError()
    Called by the GeminiWebhook library when a request fails: the webhook reported an
    error, no reply came in time, or the publish did not go out.
*/
void onGeminiError(String why) {
    if (safetyRuleFired()) showAlert();          // still raise the alert without Gemini
    else changeLedColor(255, 0, 255);            // magenta
}

/* safetyRule()
    Gemini sometimes calls a heart rate spike at rest a "workout".
    Return true to raise the alert yourself, whatever Gemini says.
    heartRate[i] and stepsPerMin[i] hold the data for minute i.
    In Part 2, kcal10[i], intensity[i], mets10[i], and sleepStage[i] are filled in too.
    defaultSafetyRule() in pulsecheck_setup.h is a ready-made rule.
*/
bool safetyRule() {
    return defaultSafetyRule();                  // ready-made rule in pulsecheck_setup.h
}

void setup() {
    pulsecheck_setup();

    Serial.begin(9600);  // begin serial communication

    // listen for the webhook's reply
    // The reply is named "hook-response/pulsecheck". Some webhooks put the device ID
    // in front of that name, so listen for both.
    Particle.subscribe("hook-response/pulsecheck", onWebhookReply, MY_DEVICES);
    Particle.subscribe(System.deviceID() + "/hook-response/pulsecheck", onWebhookReply, MY_DEVICES);
}

void loop() {
    pulsecheck_loop();
}
