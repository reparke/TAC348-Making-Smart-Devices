#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#include "pulsecheck_setup.h"
/*
  PulseCheck: Fitbit data -> Particle webhook -> Gemini -> RGB LED

  Press the button to send the next 10-minute dataset of real Fitbit data
  (A-E for Part 1, F-H for Part 2; set PART in pulsecheck_setup.h). Gemini
  answers with the activity, an alert, and a short message, and
  onGeminiReply() below shows it on the RGB LED.

  Wiring: RGB LED on SCL (red), MISO (green), MOSI (blue), each with a
  330 Ohm resistor. Button on D5 with a 10k Ohm resistor.

  Open the serial monitor to see Gemini's answer for each dataset:
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
    if (alert)                    changeLedColor(255, 0, 0);    // red (blinks)
    else if (state == "resting")  changeLedColor(0, 255, 0);    // green
    else if (state == "walking")  changeLedColor(255, 200, 0);  // yellow
    else if (state == "workout")  changeLedColor(255, 80, 0);   // orange
    else if (state == "sleep")    changeLedColor(0, 0, 255);    // blue
}

/* safetyRule()
    Gemini sometimes calls a heart rate spike at rest a "workout".
    Return true to raise the alert yourself, whatever Gemini says.
    heartRate[i] and stepsPerMin[i] hold the data for minute i.
    In Part 2, mets10[i] (METs x10) and sleepStage[i] are filled in too.
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
