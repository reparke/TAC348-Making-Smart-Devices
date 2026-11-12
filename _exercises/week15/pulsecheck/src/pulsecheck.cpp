#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#include "pulsecheck_setup.h"
/*
  PulseCheck: Fitbit data -> Particle webhook -> Gemini -> RGB LED

  pulsecheck_setup.h does the plumbing: it holds 10-minute datasets of real
  Fitbit data (A-E for Part 1, F-H for Part 2), publishes the next one to
  your webhook when you press the button, reads Gemini's JSON reply, and
  handles timeouts. You only change PART at the top, for Part 2.

  Wiring: RGB LED on SCL (red), MISO (green), MOSI (blue), each with a
  330 Ohm resistor. Button on D5 with a 10k Ohm resistor.

  Your job: complete TODO 1 below. TODO 2 is optional.

  Open the serial monitor to see Gemini's answer for each dataset:
    particle serial monitor --follow
*/

/* onGeminiReply()
    Event handler for Gemini's answer
    state is "resting", "walking", "workout", or "sleep"
    alert is true when Gemini or your safety rule raised an alert
    msg   is a short note from Gemini

    TODO 1: show the answer on the RGB LED with changeLedColor(r, g, b)
      alert          red      (255, 0, 0)    it blinks automatically
      "resting"      green    (0, 255, 0)
      "walking"      yellow   (255, 200, 0)
      "workout"      orange   (255, 80, 0)
      "sleep"        blue     (0, 0, 255)
*/
void onGeminiReply(String state, bool alert, String msg) {
    // TODO 1
}

/* safetyRule()
    Gemini sometimes calls a heart rate spike at rest a "workout" and gives
    no alert. Return true to raise the alert yourself, whatever Gemini says.
    heartRate[i] and stepsPerMin[i] hold the data for minute i (0 to MINUTES - 1).
    In Part 2, mets10[i] (METs x10) and sleepStage[i] are filled in too.

    It already uses the ready-made rule, defaultSafetyRule() in
    pulsecheck_setup.h: the heart rate of the last quarter of the window is
    30+ bpm above the first half while the body stays still (Part 1: steps
    under 10 per minute, Part 2: METs at 1.5 or below).

    TODO 2 (optional): replace it with your own rule, for example a different
    threshold or a check for a heart rate that is too low. When it fires, the
    serial monitor shows "Safety rule: alert" and the LED blinks red.
*/
bool safetyRule() {
    return defaultSafetyRule();
}

void setup() {
    pulsecheck_setup();

    Serial.begin(9600);  // begin serial communication
}

void loop() {
    pulsecheck_loop();
}
