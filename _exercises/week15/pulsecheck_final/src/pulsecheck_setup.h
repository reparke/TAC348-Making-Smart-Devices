#include "Particle.h"

/* This is the event your webhook listens for.
   Change it to pulsecheck_ followed by your USC username, for example
   pulsecheck_ttrojan. It must match the "event" in your webhook exactly.
*/
const char* EVENT_NAME = "pulsecheck";

/*
1) PINS AND SETTINGS ==========================================
  RGB LED: 330 Ohm resistor on each color
  Button: 10k Ohm resistor (reads LOW when pressed)
  ===============================================================
*/
const int PIN_RED = SCL;
const int PIN_GREEN = MISO;  // on board its MI
const int PIN_BLUE = MOSI;   // on board its MO
const int PIN_BUTTON = D5;

const int MINUTES = 10;                          // one heart rate and step reading per minute
const unsigned long MIN_GAP_MS = 10000;          // at most one request every 10 s (free-tier quota)
const unsigned long REPLY_TIMEOUT_MS = 20000;    // no reply after 20 s = error

/*
2) FITBIT DATA ================================================
  Five 10-minute windows of real Fitbit data from a public dataset:
  Furberg, R., Brinton, J., Keating, M., & Ortiz, A. (2016).
  Crowd-sourced Fitbit datasets 03.12.2016-05.12.2016. Zenodo.
  https://doi.org/10.5281/zenodo.53894 (CC BY 4.0)

  Each button press sends the next window. The scenario name is NOT
  sent to Gemini, so it works as an answer key in the serial monitor.
  ===============================================================
*/
const int NUM_SCENARIOS = 5;
const char* SCENARIOS[NUM_SCENARIOS] = {"resting", "walking", "workout", "sleep", "anomaly"};

const int FITBIT_HR[NUM_SCENARIOS][MINUTES] = {
    {72, 70, 71, 72, 75, 74, 75, 72, 73, 75},            // resting: user 2022484408, 2016-04-13 13:00
    {100, 97, 100, 104, 104, 100, 96, 100, 100, 97},     // walking: user 4558609924, 2016-04-30 19:00
    {154, 155, 156, 158, 159, 156, 160, 157, 154, 153},  // workout: user 2022484408, 2016-04-17 09:30
    {42, 42, 43, 42, 42, 43, 42, 43, 43, 43},            // sleep:   user 5577150313, 2016-04-17 03:10
    {70, 68, 66, 68, 65, 68, 144, 143, 143, 138},        // anomaly: user 2347167796, 2016-04-12 17:20,
};                                                       //          +75 bpm added to the last 4 minutes
const int FITBIT_STEPS[NUM_SCENARIOS][MINUTES] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {103, 104, 99, 100, 99, 88, 100, 100, 100, 101},
    {172, 169, 166, 170, 174, 171, 171, 173, 172, 171},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int heartRate[MINUTES];                          // the window being sent, beats per minute
int stepsPerMin[MINUTES];                        // the window being sent, steps per minute
int scenario = -1;                               // index into SCENARIOS; the first press sends 0

void loadData() {
    for (int i = 0; i < MINUTES; i++) {
        heartRate[i] = FITBIT_HR[scenario][i];
        stepsPerMin[i] = FITBIT_STEPS[scenario][i];
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
  This returns true when the average heart rate of the last quarter
  of the window is 30+ bpm above the first half while steps stay
  under 10 per minute. Your safetyRule() can just return this.
  ===============================================================
*/
bool defaultSafetyRule() {
    const int half = MINUTES / 2, tail = MINUTES / 4;
    long early = 0, late = 0, steps = 0;
    for (int i = 0; i < half; i++) early += heartRate[i];               // first half
    for (int i = MINUTES - tail; i < MINUTES; i++) {                      // last quarter
        late += heartRate[i];
        steps += stepsPerMin[i];
    }
    return late / tail - early / half >= 30 && steps / tail < 10;        // heart rate up 30+ while sitting still
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

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

// Bad reply, webhook error, or timeout: magenta, or red if the safety rule fired.
void showError(const char* why) {
    Log.error("%s", why);
    waitingForReply = false;
    alertOn = ruleFired;
    changeLedColor(255, 0, ruleFired ? 0 : 255);
}

/*
5) SEND AND RECEIVE ===========================================
  Publish the data, and read Gemini's reply from the webhook:
    {"state":"workout","alert":false,"msg":"Great pace!"}
  ===============================================================
*/
unsigned long lastSendMs = 0;
bool hasSent = false;
int prevButtonVal = HIGH;

void sendData() {
    if (waitingForReply || (hasSent && millis() - lastSendMs < MIN_GAP_MS)) {
        Log.warn("Too soon, request skipped");
        return;
    }
    scenario = (scenario + 1) % NUM_SCENARIOS;   // next window
    loadData();
    ruleFired = safetyRule();
    if (ruleFired) Log.warn("Safety rule: alert");
    String payload = buildPayload();
    Log.warn("Hidden scenario: %s", SCENARIOS[scenario]);
    Log.info("Sending: %s", payload.c_str());

    waitingForReply = true;
    alertOn = false;
    hasSent = true;
    lastSendMs = millis();
    changeLedColor(255, 255, 255);               // white = waiting for Gemini
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

/*
6) SETUP AND LOOP =============================================
  Call pulsecheck_setup() in setup() and pulsecheck_loop() in loop()
  ===============================================================
*/
void pulsecheck_setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
    Particle.subscribe(String("hook-response/") + EVENT_NAME, onWebhookReply);
    Particle.subscribe(String("hook-error/") + EVENT_NAME, onWebhookError);
}

void pulsecheck_loop() {
    // one press = button goes from HIGH (not pressed) to LOW (pressed)
    int currButtonVal = digitalRead(PIN_BUTTON);
    if (prevButtonVal == HIGH && currButtonVal == LOW) {
        sendData();
    }
    prevButtonVal = currButtonVal;

    if (waitingForReply && millis() - lastSendMs > REPLY_TIMEOUT_MS) {
        showError("No reply from webhook (timeout)");
    }
    if (alertOn) {
        changeLedColor((millis() / 250) % 2 ? 255 : 0, 0, 0);   // blink red
    }
}

/*-------------------- DEBUG FUNCTIONS -----------------------*/
/*
  printData
      prints the current window to the serial monitor ===
*/
void printData() {
    for (int i = 0; i < MINUTES; i++) {
        Serial.printlnf("minute %d: heart rate %3d, steps %3d", i, heartRate[i], stepsPerMin[i]);
    }
}
