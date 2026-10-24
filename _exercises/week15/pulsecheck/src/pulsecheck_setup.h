#include "Particle.h"

/* This is the event your webhook listens for.
   Change it to pulsecheck_ followed by your USC username, for example
   pulsecheck_ttrojan. It must match the "event" in your webhook exactly.
*/
const char* EVENT_NAME = "pulsecheck";

/*
1) SETTINGS ===================================================
  How much data to send and how often
  ===============================================================
*/
const int MINUTES = 60;                          // one heart rate and step reading per minute
const unsigned long AUTO_SEND_MS = 0;            // 0 = send only when you tap MODE; 30000 = every 30 s
const unsigned long MIN_GAP_MS = 10000;          // at most one request every 10 s (free-tier quota)
const unsigned long REPLY_TIMEOUT_MS = 20000;    // no reply after 20 s = error

/*
2) FAKE SMARTWATCH DATA =======================================
  Five scenarios. The scenario name is NOT sent to Gemini, so it
  works as an answer key in the serial monitor.
  Each scenario is the same fixed batch every time.
  ===============================================================
*/
const char* SCENARIOS[] = {"resting", "walking", "workout", "sleep", "anomaly"};
const int NUM_SCENARIOS = 5;

int heartRate[MINUTES];                          // beats per minute
int stepsPerMin[MINUTES];                        // steps per minute
int scenario = 0;                                // index into SCENARIOS

int noise(int range) { return random(-range, range + 1); }

void generateFakeData() {
    randomSeed(348 + scenario);
    for (int i = 0; i < MINUTES; i++) {
        if (scenario == 0) {             // resting
            heartRate[i] = 68 + noise(4);
            stepsPerMin[i] = random(0, 6);
        } else if (scenario == 1) {      // walking
            heartRate[i] = 98 + noise(6);
            stepsPerMin[i] = 100 + noise(10);
        } else if (scenario == 2) {      // workout: heart rate climbs from 110 to 155
            heartRate[i] = 110 + i * 45 / (MINUTES - 1) + noise(4);
            stepsPerMin[i] = 150 + noise(15);
        } else if (scenario == 3) {      // sleep
            heartRate[i] = 54 + noise(3);
            stepsPerMin[i] = 0;
        } else {                         // anomaly: heart rate jumps while sitting still
            heartRate[i] = (i < MINUTES * 6 / 10) ? 70 + noise(3) : 145 + noise(5);
            stepsPerMin[i] = random(0, 4);
        }
    }
}

// The text sent to the webhook. No double quotes, so it fits inside the webhook's JSON.
String buildPayload() {
    String hr = "hr_bpm=[", steps = "steps_per_min=[";
    for (int i = 0; i < MINUTES; i++) {
        hr += String(heartRate[i]) + (i < MINUTES - 1 ? "," : "]");
        steps += String(stepsPerMin[i]) + (i < MINUTES - 1 ? "," : "]");
    }
    return hr + " " + steps + " interval=1min";
}

/*
2b) READY-MADE SAFETY RULE ====================================
  Gemini sometimes calls a heart rate spike at rest a "workout".
  This returns true when the average heart rate of the last 15
  minutes is 30+ bpm above the first 30 minutes while steps stay
  under 10 per minute. Your safetyRule() can just return this.
  ===============================================================
*/
bool defaultSafetyRule() {
    long early = 0, late = 0, steps = 0;
    for (int i = 0; i < MINUTES / 2; i++) early += heartRate[i];         // first half hour
    for (int i = MINUTES * 3 / 4; i < MINUTES; i++) {                     // last 15 minutes
        late += heartRate[i];
        steps += stepsPerMin[i];
    }
    early /= MINUTES / 2;
    late /= MINUTES / 4;
    steps /= MINUTES / 4;
    return late - early >= 30 && steps < 10;     // heart rate up 30+ while sitting still
}

/*
3) EVENT HANDLER FORWARD DECLARATIONS ========================
  You need to define these two functions in pulsecheck.cpp.
  However, we need a "forward declaration" (the function header)
  as a C++ requirement because they are used below.
  ===============================================================
*/
// Called when Gemini answers. Set the LED color here.
void onGeminiReply(String state, bool alert, String msg);

// Return true when the data needs an alert, whatever Gemini says.
bool safetyRule();

/*
4) LED HELPERS ================================================
  ===============================================================
*/
bool waitingForReply = false;
bool alertOn = false;
bool ruleFired = false;

void showColor(uint8_t r, uint8_t g, uint8_t b) {
    RGB.control(true);
    RGB.color(r, g, b);
}

// Bad reply, webhook error, or timeout: magenta, or red if the safety rule fired.
void showError(const char* why) {
    Log.error("%s", why);
    waitingForReply = false;
    alertOn = ruleFired;
    showColor(255, 0, ruleFired ? 0 : 255);
}

/*
5) SEND AND RECEIVE ===========================================
  Publish the data, and read Gemini's reply from the webhook:
    {"state":"workout","alert":false,"msg":"Great pace!"}
  ===============================================================
*/
unsigned long lastSendMs = 0;
bool hasSent = false;
volatile bool buttonPressed = false;

void sendData() {
    if (waitingForReply || (hasSent && millis() - lastSendMs < MIN_GAP_MS)) {
        Log.warn("Too soon, request skipped");
        return;
    }
    scenario = (scenario + 1) % NUM_SCENARIOS;   // next scenario
    generateFakeData();
    ruleFired = safetyRule();
    if (ruleFired) Log.warn("Safety rule: alert");
    String payload = buildPayload();
    Log.warn("Hidden scenario: %s", SCENARIOS[scenario]);
    Log.info("Sending: %s", payload.c_str());

    waitingForReply = true;
    alertOn = false;
    hasSent = true;
    lastSendMs = millis();
    showColor(255, 255, 255);                    // white = waiting for Gemini
    if (!Particle.publish(EVENT_NAME, payload)) showError("Could not publish");
}

void onWebhookReply(const char* event, const char* data) {
    if (!waitingForReply) return;                // ignore late replies
    JSONValue obj = JSONValue::parseCopy(data ? data : "");
    String state, msg;
    bool alert = false, hasState = false, hasAlert = false, hasMsg = false;
    if (obj.isObject()) {
        JSONObjectIterator it(obj);
        while (it.next()) {
            String key = it.name().data();
            if (key == "state" && it.value().isString()) {
                state = it.value().toString().data();
                hasState = true;
            } else if (key == "alert" && it.value().isBool()) {
                alert = it.value().toBool();
                hasAlert = true;
            } else if (key == "msg" && it.value().isString()) {
                msg = it.value().toString().data();
                hasMsg = true;
            }
        }
    }
    bool validState = state == "resting" || state == "walking" || state == "workout" || state == "sleep";
    if (!hasState || !hasAlert || !hasMsg || !validState) {
        showError("Reply was not the expected JSON");
        return;
    }

    waitingForReply = false;
    Log.warn("Answer key: %s | Gemini: state=%s alert=%d msg=\"%s\"",
             SCENARIOS[scenario], state.c_str(), alert, msg.c_str());
    if (ruleFired && !alert) Log.warn("Safety rule overrides Gemini: alert on");
    alertOn = alert || ruleFired;
    onGeminiReply(state, alertOn, msg);          // your code in pulsecheck.cpp
}

void onWebhookError(const char* event, const char* data) {
    if (waitingForReply) showError("Webhook error");
}

void onModeButton(system_event_t event, int clicks) { buttonPressed = true; }

/*
6) SETUP AND LOOP =============================================
  Call pulsecheck_setup() in setup() and pulsecheck_loop() in loop()
  ===============================================================
*/
void pulsecheck_setup() {
    Particle.subscribe(String("hook-response/") + EVENT_NAME, onWebhookReply);
    Particle.subscribe(String("hook-error/") + EVENT_NAME, onWebhookError);
    System.on(button_click, onModeButton);
}

void pulsecheck_loop() {
    bool autoDue = AUTO_SEND_MS > 0 && !waitingForReply && Particle.connected() &&
                   millis() - lastSendMs >= AUTO_SEND_MS;
    if (buttonPressed || autoDue) {
        buttonPressed = false;
        sendData();                              // a press that is too soon is skipped, not counted
    }
    if (waitingForReply && millis() - lastSendMs > REPLY_TIMEOUT_MS) {
        showError("No reply from webhook (timeout)");
    }
    if (alertOn) {
        showColor((millis() / 250) % 2 ? 255 : 0, 0, 0);   // blink red
    }
}

/*-------------------- DEBUG FUNCTIONS -----------------------*/
/*
  printData
      prints the current data to the serial monitor ===
*/
void printData() {
    for (int i = 0; i < MINUTES; i++) {
        Serial.printlnf("minute %2d: heart rate %3d, steps %3d", i, heartRate[i], stepsPerMin[i]);
    }
}
