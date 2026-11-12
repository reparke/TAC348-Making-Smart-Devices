# PulseCheck

Send 10 minutes of real Fitbit data to Google Gemini through a Particle webhook, and show Gemini's answer on an RGB LED. See the [PulseCheck lecture](https://makingsmartdevices.com/lectures/week15/lecture_pulsecheck.html) for how it works.

## Files

| File | What it is |
|------|------------|
| `src/pulsecheck.cpp` | Your code: TODO 1, and optional TODO 2 |
| `src/pulsecheck_setup.h` | The plumbing: the Fitbit datasets (A-E for Part 1, F-H for Part 2), the button, publishing, reading Gemini's reply, timeouts. Change only `PART` at the top, for Part 2 |
| `pulsecheck_webhook_body_starter.json` | The JSON body for your webhook, with two blanks: `TODO PROMPT` and `TODO STATES` |

## 1. Wire the RGB LED and button

| Part | Pin | Resistor |
|------|-----|----------|
| RGB LED red | SCL | 330 Ohm |
| RGB LED green | MISO (MI on the board) | 330 Ohm |
| RGB LED blue | MOSI (MO on the board) | 330 Ohm |
| RGB LED common (long leg) | 3V3 | none |
| Button | D5 | 10k Ohm |

Same wiring as the RGB LED and button exercise. The button reads `LOW` when pressed.

## 2. Get a Gemini API key

Follow [Particle + Gemini Integration](https://makingsmartdevices.com/lectures/weekX/lecture_particle_gemini_integration.html) to create a key. Keep it private: never put it in your code, a commit, a screenshot, or a chat. The free tier is enough.

## 3. Create the webhook

1. Open `pulsecheck_webhook_body_starter.json` and fill in the two blanks:
   * **TODO PROMPT** your prompt. Cover five parts: Gemini's role, what the data is and its units, the four states to choose from, when to set `alert`, and how to write `msg` (40 characters at most). Don't use double quotes inside it. See [Writing Your Prompt](https://makingsmartdevices.com/lectures/week15/lecture_pulsecheck.html#writing-your-prompt)
   * **TODO STATES** `"sleep", "resting", "walking", "workout"`
2. In the Particle Console, go to **Cloud services**, **Integrations**, **Add new integration**, and choose **Custom Webhook**.
3. Stay on the **Webhook Builder** tab and fill in:

   | Field | Value |
   |-------|-------|
   | Name | `PulseCheck` |
   | Event name | `pulsecheck` |
   | URL | `https://generativelanguage.googleapis.com/v1beta/models/gemini-3.5-flash-lite:generateContent` |
   | Request type | `POST` |
   | Request format | `JSON` |

4. Open **Extra settings**:
   * **JSON data**: choose **Custom**, delete what is there, and paste your whole body file.
   * **HTTP headers**: add the key `x-goog-api-key` with your Gemini API key as the value. The key goes here in the Console only.
   * **Response template**: `{{#candidates}}{{#content}}{{#parts}}{{{text}}}{{/parts}}{{/content}}{{/candidates}}`
5. Click **Enable integration**.

To change your prompt later, open the webhook, click **Edit**, and change it under **Extra settings**, **JSON data**.

## 4. Complete the TODOs

Open this folder in Particle Workbench, configure it for your Photon 2, and flash after each TODO.

| TODO | Goal | How to check it |
|------|------|-----------------|
| 1 | Show Gemini's answer on the RGB LED in `onGeminiReply()` with `changeLedColor(r, g, b)` | Press the button: the LED turns white, then the color for Gemini's answer |
| 2 (optional) | Write your own safety rule in `safetyRule()` | When it fires, the serial monitor shows "Safety rule: alert" and the LED blinks red |

`safetyRule()` starts with the ready-made `defaultSafetyRule()`, so the alert works even if you skip TODO 2.

## 5. Run Part 1

* **Press the button** to send the next dataset: A, B, C, D, E, then back to A. Wait 10 seconds between presses.
* Each dataset is 10 minutes of a real person: resting, walking, a workout, sleep, or something concerning. The letter is not sent to Gemini.
* Watch the serial monitor: `particle serial monitor --follow`. Each press prints the letter next to Gemini's answer:

  ```
  Sending dataset A
  Dataset A | Gemini: state=walking alert=0 msg="Steady walk, avg 100 bpm"
  ```

* Write Gemini's answer for each dataset on the handout, then check it against the answer key at the end of the [PulseCheck lecture](https://makingsmartdevices.com/lectures/week15/lecture_pulsecheck.html#check-your-answers).

## 6. Run Part 2

1. Set `PART` to `2` at the top of `src/pulsecheck_setup.h` and flash. The button now sends datasets F, G, H.
2. Each Part 2 dataset adds two signals:
   * `mets`: energy use from the motion sensor. 1.0 = sitting still, 3 or more = exercise, even with no steps
   * `sleep`: `awake`, `asleep`, or `restless` for each minute
3. Update your prompt in the Console (**Edit**, then **Extra settings > JSON data**) so Gemini knows what `mets` and `sleep` mean.
4. The safety rule is ready-made: in Part 2, `defaultSafetyRule()` checks METs instead of steps.
5. Write Gemini's answers on the handout and check them against the answer key.

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

`gemini-3.5-flash-lite` allows 15 requests per minute and 500 per day for each Google project, which is plenty for one class. Other models allow only 20 per day. The daily limit resets at midnight Pacific time. If you run out (error 429 `RESOURCE_EXHAUSTED`), wait, or switch the model in the webhook URL to `gemini-3.6-flash` for the rest of the day.

## Troubleshooting

| What you see | Cause and fix |
|--------------|---------------|
| White, then magenta after 20 s | No reply. Check that the webhook exists in your product and its event is `pulsecheck`. |
| Magenta right away, "Webhook error" | Gemini rejected the request. Open the webhook in the Console and read the latest error. |
| Error 400 or `API_KEY_INVALID` | The `x-goog-api-key` header is missing or the key is wrong. A 400 "Unknown name" means something other than the body file was pasted into JSON data. |
| Error 404 "no longer available" | The model in the URL was retired. Use `gemini-3.5-flash-lite`. |
| LED breathing magenta, nothing runs | Safe mode: the firmware needs a newer Device OS. Run `particle update` with USB connected, then flash again. |
| Nothing happens when you press the button | Check the button wiring on D5 and its 10k Ohm resistor. |
