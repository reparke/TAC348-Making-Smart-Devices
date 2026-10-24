# PulseCheck (final)

The completed [PulseCheck](../pulsecheck/) exercise. Setup is the same as the starter's README.

* `src/pulsecheck.cpp`: `onGeminiReply()` sets the LED color, and `safetyRule()` uses the ready-made `defaultSafetyRule()`.
* `src/pulsecheck_setup.h`: unchanged from the starter. To send automatically instead of on MODE, set `AUTO_SEND_MS` to `30000`.
* `pulsecheck_webhook.json`: a complete webhook. Replace `PASTE_YOUR_GEMINI_API_KEY_HERE` in the Particle Console only, and change `"event"` to your own event name.
