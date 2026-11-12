# PulseCheck (final)

The completed [PulseCheck](../pulsecheck/) exercise. Setup is the same as the starter's README.

* `src/pulsecheck.cpp`: `onGeminiReply()` sets the LED color, and `safetyRule()` uses the ready-made `defaultSafetyRule()`.
* `src/pulsecheck_setup.h`: unchanged from the starter. Set `PART` to `2` for datasets F-H.
* `pulsecheck_webhook_body.json`: the complete JSON body for the webhook. Its prompt handles both parts, including `mets` and `sleep`. Paste it under **Extra settings**, **JSON data**, **Custom** in the Webhook Builder. The other settings (URL, `x-goog-api-key` header, response template) are in the starter's README.
