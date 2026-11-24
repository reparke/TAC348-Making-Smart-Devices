# PulseCheck (final)

The completed [PulseCheck](../pulsecheck/) exercise. Setup is the same as the starter's README.

* `src/pulsecheck.cpp`: `setup()` subscribes to the webhook's reply, `onWebhookReply()` unpacks Gemini's reply with `ArduinoJson` in two steps (the reply, then the answer text inside it) and sets the LED color, and `safetyRule()` uses the ready-made `defaultSafetyRule()`.
* `src/pulsecheck_setup.h`, `src/json_webhook_response_helper.h`: unchanged from the starter. `project.properties` already lists the `ArduinoJson` and `GeminiWebhook` libraries. Set `PART` to `2` in `pulsecheck_setup.h` for datasets F-H.
* `pulsecheck_webhook_body.json`: the complete JSON body for the webhook. Its prompt handles both parts, including the four extra Part 2 signals. Paste it under **Extra settings**, **JSON data**, **Custom** in the Webhook Builder. The other settings (URL, `x-goog-api-key` header) are in the starter's README.
