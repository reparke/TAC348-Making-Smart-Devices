# PulseCheck

Send 10 minutes of real Fitbit heart rate and step data to Google Gemini through a Particle webhook, and show Gemini's answer on an RGB LED. See the [PulseCheck lecture](https://makingsmartdevices.com/lectures/week15/lecture_pulsecheck.html) for how it works.

## Files

| File | What it is |
|------|------------|
| `src/pulsecheck.cpp` | Your code: TODO 1, and optional TODO 2 |
| `src/pulsecheck_setup.h` | The plumbing: five windows of Fitbit data, the button, publishing, reading Gemini's reply, timeouts. Change only `EVENT_NAME` at the top |
| `pulsecheck_webhook_starter.json` | The webhook template, with blanks W1–W5 |

## 1. Wire the RGB LED and button

| Part | Pin | Resistor |
|------|-----|----------|
| RGB LED red | SCL | 330 Ohm |
| RGB LED green | MISO (MI on the board) | 330 Ohm |
| RGB LED blue | MOSI (MO on the board) | 330 Ohm |
| Button | D5 | 10k Ohm |

Same wiring as the RGB LED and button exercise. The button reads `LOW` when pressed.

## 2. Get a Gemini API key

Follow [Particle + Gemini Integration](https://makingsmartdevices.com/lectures/weekX/lecture_particle_gemini_integration.html) to create a key. Keep it private: never put it in your code, a commit, a screenshot, or a chat. The free tier is enough.

## 3. Pick your event name

Use `pulsecheck_` followed by your USC username, for example `pulsecheck_ttrojan`. Every device in the class product shares one event stream, so if two students use the same name, each press triggers both webhooks and spends both API keys.

Set it as `EVENT_NAME` at the top of `src/pulsecheck_setup.h`.

## 4. Create the webhook

1. Fill in the blanks in `pulsecheck_webhook_starter.json`:
   * **W1** your event name from step 3
   * **W2** `gemini-3.5-flash-lite`
   * **W4** your prompt: what the data is, the four states to choose from, when to set `alert`, and how to write `msg` (40 characters at most)
   * **W5** `"sleep", "resting", "walking", "workout"`
2. In the Particle Console, open the class product, then **Integrations**, **Add integration**, **Webhook**.
3. Click the **Custom template** tab (not Webhook Builder), delete what is there, and paste your file.
4. Replace the W3 text with your API key, here in the Console only, and save.

To change the webhook later, open it, click **Edit**, and use **Custom template**. Change only the lines you mean to change.

## 5. Complete the TODOs

Open this folder in Particle Workbench, configure it for your Photon 2, and flash after each TODO.

| TODO | Goal | How to check it |
|------|------|-----------------|
| 1 | Show Gemini's answer on the RGB LED in `onGeminiReply()` with `changeLedColor(r, g, b)` | Press the button: the LED turns white, then the color for Gemini's answer |
| 2 (optional) | Write your own safety rule in `safetyRule()` | The `anomaly` scenario logs "Safety rule: alert" and blinks red |

`safetyRule()` starts with the ready-made `defaultSafetyRule()`, so the alert works even if you skip TODO 2.

## 6. Run it

* **Press the button** to send the next window of Fitbit data: resting, walking, workout, sleep, anomaly. Wait 10 seconds between presses.
* Watch the serial monitor: `particle serial monitor --follow`. Each press prints the hidden window name next to Gemini's answer:

  ```
  Hidden scenario: walking
  Answer key: walking | Gemini: state=walking alert=0 msg="Steady walk, avg 100 bpm"
  ```

Check Gemini's answers against the answer key:

| # | Window | Correct `state` | Correct `alert` | Safety rule fires? |
|---|--------|-----------------|-----------------|--------------------|
| 1 | resting | `resting` | `false` | no |
| 2 | walking | `walking` | `false` | no |
| 3 | workout | `workout` | `false` | no |
| 4 | sleep | `sleep` | `false` | no |
| 5 | anomaly | `resting` | `true` | **yes** |

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
| Nothing happens when you press the button | Check the button wiring on D5 and its 10k Ohm resistor. |
