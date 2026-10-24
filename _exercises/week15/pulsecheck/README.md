# PulseCheck

Send an hour of fake smartwatch data to Google Gemini through a Particle webhook, and show Gemini's answer on the Photon 2's LED. See the [PulseCheck lecture](../../../_lectures/week15/lecture_pulsecheck.md) for how it works.

## Files

| File | What it is |
|------|------------|
| `src/pulsecheck.cpp` | Your code: TODO 1, and optional TODO 2 |
| `src/pulsecheck_setup.h` | The plumbing: fake data, publishing, reading Gemini's reply, timeouts. Change only `EVENT_NAME` at the top |
| `pulsecheck_webhook_starter.json` | The webhook template, with blanks W1–W5 |

## 1. Get a Gemini API key

1. Go to <https://aistudio.google.com/api-keys> and sign in with a Google account. If your USC account is blocked, use a personal Gmail account.
2. Click **Create API key**, name it `PulseCheck`, choose **Default Gemini Project**, and click **Create key**.
3. Copy the key. Keep it private: never put it in your code, a commit, a screenshot, or a chat.

The free tier is enough. Do not set up billing.

## 2. Pick your event name

Use `pulsecheck_` followed by your USC username, for example `pulsecheck_ttrojan`. Every device in the class product shares one event stream, so if two students use the same name, each press triggers both webhooks and spends both API keys.

Set it as `EVENT_NAME` at the top of `src/pulsecheck_setup.h`.

## 3. Create the webhook

1. Fill in the blanks in `pulsecheck_webhook_starter.json`:
   * **W1** your event name from step 2
   * **W2** `gemini-3.5-flash-lite`
   * **W4** your prompt: what the data is, the four states to choose from, when to set `alert`, and how to write `msg` (40 characters at most)
   * **W5** `"sleep", "resting", "walking", "workout"`
2. In the Particle Console, open the class product, then **Integrations**, **Add integration**, **Webhook**.
3. Click the **Custom template** tab (not Webhook Builder), delete what is there, and paste your file.
4. Replace the W3 text with your API key, here in the Console only, and save.

To change the webhook later, open it, click **Edit**, and use **Custom template**. Change only the lines you mean to change.

## 4. Complete the TODOs

Open this folder in Particle Workbench, configure it for your Photon 2, and flash after each TODO.

| TODO | Goal | How to check it |
|------|------|-----------------|
| 1 | Show Gemini's answer on the LED in `onGeminiReply()` | Tap MODE: the LED turns white, then the color for Gemini's answer |
| 2 (optional) | Write your own safety rule in `safetyRule()` | The `anomaly` scenario logs "Safety rule: alert" and blinks red |

`safetyRule()` starts with the ready-made `defaultSafetyRule()`, so the alert works even if you skip TODO 2.

## 5. Run it

* **Tap MODE** (do not hold it) to send the next scenario: walking, workout, sleep, anomaly, resting. Wait 10 seconds between taps.
* Watch the serial monitor: `particle serial monitor --follow`. Each tap prints the hidden scenario next to Gemini's answer:

  ```
  Hidden scenario: walking
  Answer key: walking | Gemini: state=walking alert=0 msg="Steady walk, avg 98 bpm"
  ```

| LED | Meaning |
|-----|---------|
| White | Waiting for Gemini |
| Green | Resting |
| Yellow | Walking |
| Orange | Workout |
| Blue | Sleep |
| Blinking red | Alert |
| Magenta | Error: bad reply, webhook error, or timeout |

## Free-tier limits

`gemini-3.5-flash-lite` allows 15 requests per minute and 500 per day for each Google project, which is plenty for one class. Other models allow only 20 per day. The daily limit resets at midnight Pacific time. If you run out (error 429 `RESOURCE_EXHAUSTED`), wait, or switch W2 to `gemini-3.6-flash` for the rest of the day.

## Troubleshooting

| What you see | Cause and fix |
|--------------|---------------|
| White, then magenta after 20 s | No reply. Check that the webhook exists in the class product and its event name matches `EVENT_NAME` exactly. |
| Magenta right away, "Webhook error" | Gemini rejected the request. Open the webhook in the Console and read the latest error. |
| Error 400 or `API_KEY_INVALID` | The key is wrong or still the W3 placeholder, or the template was pasted into Webhook Builder instead of Custom template. |
| Error 404 "no longer available" | The model in W2 was retired. Use `gemini-3.5-flash-lite`. |
| LED breathing magenta, nothing runs | Safe mode: the firmware needs a newer Device OS. Run `particle update` with USB connected, then flash again. |
| LED blinking dark blue | Wi-Fi setup mode, usually from holding MODE. Press RESET. |
