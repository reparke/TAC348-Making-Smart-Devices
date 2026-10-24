#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#include "pulsecheck_setup.h"
/*
  PulseCheck: fake smartwatch data -> Particle webhook -> Gemini -> LED

  Tap MODE to send the next scenario (resting, walking, workout, sleep,
  anomaly). Gemini answers with the activity, an alert, and a short message,
  and onGeminiReply() below shows it on the LED.

  Open the serial monitor to see the answer key next to Gemini's answer:
    particle serial monitor --follow

  LED
    white          waiting for Gemini
    green          resting
    yellow         walking
    orange         workout
    blue           sleep
    blinking red   alert
    magenta        error (bad reply, webhook error, or timeout)
*/

/* onGeminiReply()
    Event handler for Gemini's answer
    state is "resting", "walking", "workout", or "sleep"
    alert is true when Gemini or your safety rule raised an alert
    msg   is a short note from Gemini
*/
void onGeminiReply(String state, bool alert, String msg) {
    if (alert)                    showColor(255, 0, 0);    // red (blinks)
    else if (state == "resting")  showColor(0, 255, 0);    // green
    else if (state == "walking")  showColor(255, 200, 0);  // yellow
    else if (state == "workout")  showColor(255, 80, 0);   // orange
    else if (state == "sleep")    showColor(0, 0, 255);    // blue
}

/* safetyRule()
    Gemini sometimes calls a heart rate spike at rest a "workout".
    Return true to raise the alert yourself, whatever Gemini says.
    heartRate[i] and stepsPerMin[i] hold the data for minute i.
    defaultSafetyRule() in pulsecheck_setup.h is a ready-made rule.
*/
bool safetyRule() {
    return defaultSafetyRule();                  // ready-made rule in pulsecheck_setup.h
}

void setup() {
    pulsecheck_setup();

    Serial.begin(9600);  // begin serial communication
}

void loop() {
    pulsecheck_loop();
}
