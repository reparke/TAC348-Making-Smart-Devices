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

  Press the button to send the next 10-minute dataset of real Fitbit data to
  your webhook. Gemini answers with JSON:
    {"state": "workout", "alert": false, "msg": "Great pace, avg 156 bpm!"}
  Your job is to receive that reply, unpack the JSON, and show it on the
  RGB LED.

  Files
    pulsecheck.cpp                   this file: your code
    pulsecheck_setup.h               the button, the LED, and the Fitbit data
    json_webhook_response_helper.h   joins a webhook reply that arrives in pieces
    fitbit_data.h                    the numbers

  Wiring: RGB LED on SCL (red), MISO (green), MOSI (blue), each with a
  330 Ohm resistor, long leg to GND. Button on D5 with a 10k Ohm resistor.

  Before you start: install two libraries, the same way as the weather
  exercises. In Workbench: Ctrl/Cmd + Shift + P, "Particle: Install Library".
  Do it once for ArduinoJson and once for GeminiWebhook. The project does
  not compile without them.
    ArduinoJson     unpacks JSON
    GeminiWebhook   sending, waiting, timeout (reusable in any project)

  Your job: complete TODO 1, 2, and 3 below. TODO 4 is optional.

  Open the serial monitor to see Gemini's answer for each dataset:
    particle serial monitor --follow
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

    String state = "";                           // "resting", "walking", "workout", or "sleep"
    bool alert = false;                          // true or false
    String msg = "";                             // a short note

    /* TODO 2: unpack fullJson into state, alert, and msg
        fullJson is Gemini's whole reply. The answer is a piece of text deep
        inside it, and that text is JSON too, so you unpack twice:

          {
            "candidates": [
              { "content": { "parts": [ { "text": "{\"state\": \"workout\", ...}" } ] } }
            ],
            "usageMetadata": { ... }
          }

        Step 1, the same way as the weather exercises:
          - create a JsonDocument
          - deserializeJson() fullJson into it and keep the DeserializationError
          - if there was an error, call onGeminiError("Reply was not JSON") and return
          - read the text into a String:
              doc["candidates"][0]["content"]["parts"][0]["text"].as<String>()

        Step 2:
          - create a second JsonDocument
          - deserializeJson() that String into it, and check the error again
          - read the three values from the second document, for example
              state = answer["state"].as<String>();
    */


    logAnswer(state, alert, msg);                // print it to the serial monitor
    if (safetyRuleFired()) alert = true;         // the safety rule wins, whatever Gemini says

    /* TODO 3: show the answer on the RGB LED
        alert          blinking red   showAlert();
        "resting"      green          changeLedColor(0, 255, 0);
        "walking"      yellow         changeLedColor(255, 200, 0);
        "workout"      orange         changeLedColor(255, 80, 0);
        "sleep"        blue           changeLedColor(0, 0, 255);
        anything else  magenta        changeLedColor(255, 0, 255);
    */

}

/* onGeminiError()
    Called by the GeminiWebhook library when a request fails: the webhook reported an
    error, no reply came in time, or the publish did not go out.
    You don't need to change this.
*/
void onGeminiError(String why) {
    if (safetyRuleFired()) showAlert();          // still raise the alert without Gemini
    else changeLedColor(255, 0, 255);            // magenta
}

/* safetyRule()
    Gemini sometimes calls a heart rate spike at rest a "workout" and gives
    no alert. Return true to raise the alert yourself, whatever Gemini says.
    heartRate[i] and stepsPerMin[i] hold the data for minute i (0 to MINUTES - 1).
    In Part 2, kcal10[i], intensity[i], mets10[i], and sleepStage[i] are filled in too.

    It already uses the ready-made rule, defaultSafetyRule() in
    pulsecheck_setup.h: the heart rate of the last quarter of the window is
    30+ bpm above the first half while the body stays still (Part 1: steps
    under 10 per minute, Part 2: METs at 1.5 or below).

    TODO 4 (optional): replace it with your own rule, for example a different
    threshold or a check for a heart rate that is too low. When it fires, the
    serial monitor shows "Safety rule: alert" and the LED blinks red.
*/
bool safetyRule() {
    return defaultSafetyRule();
}

void setup() {
    pulsecheck_setup();

    Serial.begin(9600);  // begin serial communication

    /* TODO 1: listen for your webhook's reply
        Subscribe to the event "hook-response/pulsecheck" with onWebhookReply
        as the handler, the same way as the weather exercises.

        Some webhooks put the device ID in front of the reply's name. To cover
        that case, subscribe a second time, to
          System.deviceID() + "/hook-response/pulsecheck"
    */

}

void loop() {
    pulsecheck_loop();
}
