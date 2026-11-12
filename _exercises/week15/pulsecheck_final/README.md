# PulseCheck (final)

The completed [PulseCheck](../pulsecheck/) exercise. Setup is the same as the starter's README.

* `src/pulsecheck.cpp`: `onGeminiReply()` sets the LED color, and `safetyRule()` uses the ready-made `defaultSafetyRule()`.
* `src/pulsecheck_setup.h`: unchanged from the starter. Set `PART` to `2` for datasets F-H.
* `pulsecheck_webhook.json`: a complete webhook. Its prompt handles both parts, including `mets` and `sleep`. Replace `PASTE_YOUR_GEMINI_API_KEY_HERE` in the Particle Console only.
