#include "Particle.h"

/* This is the event your webhook listens for.
   It must match the "event" in your webhook exactly.
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

const int MINUTES = 10;                          // one reading per minute
const unsigned long MIN_GAP_MS = 10000;          // at most one request every 10 s (free-tier quota)
const unsigned long REPLY_TIMEOUT_MS = 20000;    // no reply after 20 s = error

/* Which part of the exercise you are on:
     1 = Part 1: datasets A-E, heart rate and steps
     2 = Part 2: datasets F-H, heart rate, steps, calories, intensity, METs, and sleep
*/
const int PART = 1;

/*
2) FITBIT DATA ================================================
  Real Fitbit data from a public dataset:
  Furberg, R., Brinton, J., Keating, M., & Ortiz, A. (2016).
  Crowd-sourced Fitbit datasets 03.12.2016-05.12.2016. Zenodo.
  https://doi.org/10.5281/zenodo.53894 (CC BY 4.0)

  Each button press sends the next dataset. Only the numbers are
  sent to Gemini, never the letter. Your job is to record what
  Gemini says for each one, then check the answer key.
  ===============================================================
*/
// Part 1: heart rate (bpm) and steps per minute
const int NUM_PART1 = 5;
const char* LABELS_PART1[NUM_PART1] = {"A", "B", "C", "D", "E"};
const int HR_PART1[NUM_PART1][MINUTES] = {
    {100, 97, 100, 104, 104, 100, 96, 100, 100, 97},     // A: user 4558609924, 2016-04-30 19:00
    {42, 42, 43, 42, 42, 43, 42, 43, 43, 43},            // B: user 5577150313, 2016-04-17 03:10
    {70, 68, 66, 68, 65, 68, 144, 143, 143, 138},        // C: user 2347167796, 2016-04-12 17:20 (edited)
    {72, 70, 71, 72, 75, 74, 75, 72, 73, 75},            // D: user 2022484408, 2016-04-13 13:00
    {154, 155, 156, 158, 159, 156, 160, 157, 154, 153},  // E: user 2022484408, 2016-04-17 09:30
};
const int STEPS_PART1[NUM_PART1][MINUTES] = {
    {103, 104, 99, 100, 99, 88, 100, 100, 100, 101},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {172, 169, 166, 170, 174, 171, 171, 173, 172, 171},
};

// Part 2: heart rate and steps, plus four more signals from the same Fitbit data
//   calories  = calories burned per minute (stored x10, so 12 means 1.2)
//   intensity = Fitbit's activity level: 0 sedentary, 1 light, 2 moderate, 3 very active
//   METs      = energy use compared to rest: 1.0 = sitting still, 3+ = exercise
//               (stored x10, so 12 means 1.2)
//   sleep     = 0 awake, 1 asleep, 2 restless (from Fitbit's sleep tracking)
const int NUM_PART2 = 3;
const char* LABELS_PART2[NUM_PART2] = {"F", "G", "H"};
const int HR_PART2[NUM_PART2][MINUTES] = {
    {62, 62, 62, 62, 62, 60, 63, 97, 97, 96},            // F: user 6962181067, 2016-04-21 03:45
    {137, 132, 142, 189, 191, 191, 186, 172, 165, 163},  // G: user 4020332650, 2016-04-15 21:55
    {66, 66, 67, 65, 68, 74, 90, 97, 100, 100},          // H: user 6117666160, 2016-04-28 11:10
};
const int STEPS_PART2[NUM_PART2][MINUTES] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
const int KCAL10_PART2[NUM_PART2][MINUTES] = {
    {9, 9, 9, 9, 9, 9, 9, 10, 11, 9},
    {124, 124, 105, 127, 193, 193, 193, 187, 172, 161},
    {10, 11, 10, 10, 10, 10, 10, 13, 13, 13},
};
const int INTENSITY_PART2[NUM_PART2][MINUTES] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
const int METS10_PART2[NUM_PART2][MINUTES] = {
    {10, 10, 10, 10, 10, 10, 10, 11, 12, 10},
    {90, 90, 76, 92, 140, 140, 140, 136, 125, 117},
    {10, 11, 10, 10, 10, 10, 10, 12, 12, 12},
};
const int SLEEP_PART2[NUM_PART2][MINUTES] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
const char* SLEEP_NAMES[] = {"awake", "asleep", "restless"};

int heartRate[MINUTES];                          // the dataset being sent, beats per minute
int stepsPerMin[MINUTES];                        // steps per minute
int kcal10[MINUTES];                             // calories per minute x10 (Part 2 only)
int intensity[MINUTES];                          // 0 sedentary to 3 very active (Part 2 only)
int mets10[MINUTES];                             // METs x10 (Part 2 only)
int sleepStage[MINUTES];                         // 0 awake, 1 asleep, 2 restless (Part 2 only)
int dataset = -1;                                // which dataset; the first press sends 0

int numDatasets() { return PART == 1 ? NUM_PART1 : NUM_PART2; }
const char* datasetLabel() { return PART == 1 ? LABELS_PART1[dataset] : LABELS_PART2[dataset]; }

void loadData() {
    for (int i = 0; i < MINUTES; i++) {
        if (PART == 1) {
            heartRate[i] = HR_PART1[dataset][i];
            stepsPerMin[i] = STEPS_PART1[dataset][i];
            kcal10[i] = 0;
            intensity[i] = 0;
            mets10[i] = 0;
            sleepStage[i] = 0;
        } else {
            heartRate[i] = HR_PART2[dataset][i];
            stepsPerMin[i] = STEPS_PART2[dataset][i];
            kcal10[i] = KCAL10_PART2[dataset][i];
            intensity[i] = INTENSITY_PART2[dataset][i];
            mets10[i] = METS10_PART2[dataset][i];
            sleepStage[i] = SLEEP_PART2[dataset][i];
        }
    }
}

// The text sent to the webhook. No double quotes, so it fits inside the webhook's JSON.
String buildPayload() {
    String hr = "hr_bpm=[", steps = "steps_per_min=[", kcal = "calories_per_min=[";
    String level = "intensity=[", mets = "mets=[", sleep = "sleep=[";
    for (int i = 0; i < MINUTES; i++) {
        String sep = i < MINUTES - 1 ? "," : "]";
        hr += String(heartRate[i]) + sep;
        steps += String(stepsPerMin[i]) + sep;
        kcal += String(kcal10[i] / 10) + "." + String(kcal10[i] % 10) + sep;
        level += String(intensity[i]) + sep;
        mets += String(mets10[i] / 10) + "." + String(mets10[i] % 10) + sep;
        sleep += String(SLEEP_NAMES[sleepStage[i]]) + sep;
    }
    if (PART == 1) return hr + " " + steps + " interval=1min";
    return hr + " " + steps + " " + kcal + " " + level + " " + mets + " " + sleep + " interval=1min";
}

/*
2b) READY-MADE SAFETY RULE ====================================
  Gemini sometimes calls a heart rate spike at rest a "workout".
  This returns true when the average heart rate of the last quarter
  of the window is 30+ bpm above the first half while the body
  stays still. Your safetyRule() can just return this.
    Part 1: still = steps under 10 per minute
    Part 2: still = METs at 1.5 or below. Steps miss exercise like
            cycling, but METs do not
  ===============================================================
*/
bool defaultSafetyRule() {
    const int half = MINUTES / 2, tail = MINUTES / 4;
    long early = 0, late = 0, steps = 0, mets = 0;
    for (int i = 0; i < half; i++) early += heartRate[i];               // first half
    for (int i = MINUTES - tail; i < MINUTES; i++) {                      // last quarter
        late += heartRate[i];
        steps += stepsPerMin[i];
        mets += mets10[i];
    }
    bool still = PART == 1 ? steps / tail < 10 : mets / tail <= 15;
    return late / tail - early / half >= 30 && still;                    // heart rate up 30+ while still
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

// Common anode RGB LED: the long leg goes to 3V3, so LOW = on. Flip the values.
void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, 255 - r);
    analogWrite(PIN_GREEN, 255 - g);
    analogWrite(PIN_BLUE, 255 - b);
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
    dataset = (dataset + 1) % numDatasets();     // next dataset
    loadData();
    ruleFired = safetyRule();
    if (ruleFired) Log.warn("Safety rule: alert");
    String payload = buildPayload();
    Log.warn("Sending dataset %s", datasetLabel());
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
    Log.warn("Dataset %s | Gemini: state=%s alert=%d msg=\"%s\"",
             datasetLabel(), state.c_str(), alert, msg.c_str());
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
    changeLedColor(0, 0, 0);  // off at boot
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
        Serial.printlnf("minute %d: heart rate %3d, steps %3d, calories %d.%d, intensity %d, METs %d.%d, %s",
                        i, heartRate[i], stepsPerMin[i], kcal10[i] / 10, kcal10[i] % 10, intensity[i],
                        mets10[i] / 10, mets10[i] % 10, SLEEP_NAMES[sleepStage[i]]);
    }
}
