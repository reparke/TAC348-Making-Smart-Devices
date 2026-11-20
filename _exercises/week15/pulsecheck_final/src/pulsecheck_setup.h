#include "Particle.h"
#include "fitbit_data.h"     // the Fitbit datasets: A-E for Part 1, F-H for Part 2
#include "GeminiWebhook.h"   // library: sending, waiting, timeout, errors (reusable in any project)

/* This is the event your webhook listens for.
   It must match the "event" in your webhook exactly.
*/
const char* EVENT_NAME = "pulsecheck";

/*
1) PINS AND SETTINGS ==========================================
  RGB LED: 330 Ohm resistor on each color, long leg to GND
  Button: 10k Ohm resistor (reads LOW when pressed)
  ===============================================================
*/
const int PIN_RED = SCL;
const int PIN_GREEN = MISO;  // on board its MI
const int PIN_BLUE = MOSI;   // on board its MO
const int PIN_BUTTON = D5;

/* Which kind of RGB LED you have:
     false = common cathode: the long leg goes to GND
     true  = common anode:   the long leg goes to 3V3
   If the LED is white when it should be off, change this.
*/
const bool COMMON_ANODE = false;

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

  The numbers are in fitbit_data.h (and data/fitbit_windows.csv).
  Each button press sends the next dataset. Only the numbers are
  sent to Gemini, never the letter. Your job is to record what
  Gemini says for each one, then check the answer key.
  ===============================================================
*/

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
3) EVENT HANDLER FORWARD DECLARATION =========================
  You need to define this function in pulsecheck.cpp.
  However, we need a "forward declaration" (the function header)
  as a C++ requirement because it is used below.
  ===============================================================
*/
// Return true when the data needs an alert, whatever Gemini says.
bool safetyRule();

/*
4) LED AND LOG HELPERS ========================================
  Use these in pulsecheck.cpp
  ===============================================================
*/
bool alertOn = false;
bool ruleFired = false;

// Common cathode (long leg to GND): HIGH = on. Common anode (long leg to 3V3): LOW = on,
// so the values are flipped. Set COMMON_ANODE at the top of this file to match your LED.
void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, COMMON_ANODE ? 255 - r : r);
    analogWrite(PIN_GREEN, COMMON_ANODE ? 255 - g : g);
    analogWrite(PIN_BLUE, COMMON_ANODE ? 255 - b : b);
}

// Blink the LED red until the next button press.
void showAlert() {
    alertOn = true;
    changeLedColor(255, 0, 0);
}

// true when your safetyRule() raised an alert for the dataset that was just sent
bool safetyRuleFired() { return ruleFired; }

// Print Gemini's answer next to the dataset letter in the serial monitor.
void logAnswer(String state, bool alert, String msg) {
    Log.warn("Dataset %s | Gemini: state=%s alert=%d msg=\"%s\"",
             datasetLabel(), state.c_str(), alert, msg.c_str());
    if (ruleFired && !alert) Log.warn("Safety rule overrides Gemini: alert on");
}

/*
5) SEND =======================================================
  One button press sends the next dataset to your webhook.
  Reading the reply is your job, in pulsecheck.cpp.
  ===============================================================
*/
int prevButtonVal = HIGH;

void sendData() {
    if (!geminiReady()) {
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

    alertOn = false;
    changeLedColor(255, 255, 255);               // white = waiting for Gemini
    geminiSend(payload);
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
    geminiSetup(EVENT_NAME);
}

void pulsecheck_loop() {
    // one press = button goes from HIGH (not pressed) to LOW (pressed)
    int currButtonVal = digitalRead(PIN_BUTTON);
    if (prevButtonVal == HIGH && currButtonVal == LOW) {
        sendData();
    }
    prevButtonVal = currButtonVal;

    geminiLoop();                                // reports a timeout if no reply came
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
