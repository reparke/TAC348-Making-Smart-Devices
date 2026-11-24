# PulseCheck

Send 10 minutes of real Fitbit data to Google Gemini through a Particle webhook, and show Gemini's answer on an RGB LED. See the [PulseCheck lecture](https://makingsmartdevices.com/lectures/week15/lecture_pulsecheck.html) for how it works.

## Files

| File | What it is |
|------|------------|
| `src/pulsecheck.cpp` | Your code: TODO 1, 2, and 3, and optional TODO 4 |
| `src/fitbit_data.h` | The Fitbit datasets (A-E for Part 1, F-H for Part 2), compiled into the firmware |
| `data/fitbit_windows.csv` | The same numbers as a spreadsheet, for you to look at. The Photon 2 does not read this file |
| `src/pulsecheck_setup.h` | The button, the LED, and loading the Fitbit data. Change only `PART` at the top, for Part 2 |
| `src/json_webhook_response_helper.h` | Joins a webhook reply that arrives in pieces. The same file as the weather exercises |
| `pulsecheck_webhook_body_starter.json` | The JSON body for your webhook, with two blanks: `TODO PROMPT` and `TODO STATES` |

## 1. Wire the RGB LED and button

| Part | Pin | Resistor |
|------|-----|----------|
| RGB LED red | SCL | 330 Ohm |
| RGB LED green | MISO (MI on the board) | 330 Ohm |
| RGB LED blue | MOSI (MO on the board) | 330 Ohm |
| RGB LED common (long leg) | GND | none |
| Button | D5 | 10k Ohm |

Same wiring as the RGB LED and button exercise. The button reads `LOW` when pressed. This is for a common cathode RGB LED. If yours is common anode, the long leg goes to 3V3 instead, and you set `COMMON_ANODE` to `true` at the top of `src/pulsecheck_setup.h`.

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
   * **Response template**: leave it empty. Your code unpacks Gemini's whole reply.
5. Click **Enable integration**.

To change your prompt later, open the webhook, click **Edit**, and change it under **Extra settings**, **JSON data**.

## 4. Complete the TODOs

Open this folder in Particle Workbench and configure it for your Photon 2. Install two libraries first, the same way as the weather exercises: run **Particle: Install Library** once for `ArduinoJson` and once for `GeminiWebhook`. The starter does not include them, so the compile fails with `ArduinoJson.h: No such file or directory` or `GeminiWebhook.h: No such file or directory` until you do.

`GeminiWebhook` handles sending, waiting, and timeouts. It is not tied to PulseCheck: you can install it in any project (see the end of this file). Flash after each TODO.

| TODO | Goal | How to check it |
|------|------|-----------------|
| 1 | In `setup()`, subscribe to `hook-response/pulsecheck` with `onWebhookReply` as the handler. Then subscribe a second time, to `System.deviceID() + "/hook-response/pulsecheck"`, for webhooks that put the device ID in front of the reply's name | Press the button: the LED turns white. In the serial monitor you see `Dataset A \| Gemini: state= alert=0 msg=""` instead of a timeout |
| 2 | In `onWebhookReply()`, unpack Gemini's reply with `ArduinoJson`, in two steps: take the answer text out of the reply, then unpack that text into `state`, `alert`, and `msg` | The serial monitor line now has real values, for example `state=walking alert=0 msg="Steady walk"` |
| 3 | Show the answer on the RGB LED with `changeLedColor(r, g, b)` and `showAlert()` | The LED turns white, then the color for Gemini's answer |
| 4 (optional) | Write your own safety rule in `safetyRule()` | When it fires, the serial monitor shows "Safety rule: alert" and the LED blinks red |

`safetyRule()` starts with the ready-made `defaultSafetyRule()`, so the alert works even if you skip TODO 4.

## 5. Run Part 1

* **Press the button** to send the next dataset: A, B, C, D, E, then back to A. Wait 10 seconds between presses.
* Each dataset is 10 minutes of a real person: resting, walking, a workout, sleep, or something concerning. The letter is not sent to Gemini.
* Watch the serial monitor: `particle serial monitor --follow`. Each press prints the letter next to Gemini's answer:

  ```
  Sending dataset A
  Dataset A | Gemini: state=walking alert=0 msg="Steady walk, avg 100 bpm"
  ```

* Write down Gemini's `state` and `alert` for each dataset. Your instructor goes over the answers at the end of each part.

## 6. Run Part 2

1. Set `PART` to `2` at the top of `src/pulsecheck_setup.h` and flash. The button now sends datasets F, G, H.
2. Each Part 2 dataset adds four signals:
   * `calories_per_min`: calories burned each minute. About 1 at rest, 10 or more in hard exercise
   * `intensity`: Fitbit's activity level. 0 sedentary, 1 light, 2 moderate, 3 very active
   * `mets`: energy use compared to rest. 1.0 = sitting still, 3 or more = exercise, even with no steps
   * `sleep`: `awake`, `asleep`, or `restless` for each minute
3. Update your prompt in the Console (**Edit**, then **Extra settings > JSON data**) so Gemini knows what the four new signals mean.
4. The safety rule is ready-made: in Part 2, `defaultSafetyRule()` checks METs instead of steps.
5. Write down Gemini's answer for each dataset. Your instructor goes over the answers.

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
| White, then magenta after 20 s | No reply reached your code. Check that the webhook exists in your product, its event is `pulsecheck`, TODO 1 is done with both subscribe lines, and the name in them matches the event name. |
| `state=` is empty in the serial monitor | The reply arrived but TODO 2 is not finished, or the path to the text has a typo. It also happens if the webhook has a response template: clear that field. |
| Magenta right away, "Webhook error" | Gemini rejected the request. Open the webhook in the Console and read the latest error. |
| Error 400 or `API_KEY_INVALID` | The `x-goog-api-key` header is missing or the key is wrong. A 400 "Unknown name" means something other than the body file was pasted into JSON data. |
| Error 404 "no longer available" | The model in the URL was retired. Use `gemini-3.5-flash-lite`. |
| LED is white when it should be off, or colors look wrong | Your RGB LED is the other kind. Change `COMMON_ANODE` at the top of `src/pulsecheck_setup.h` and move the long leg (GND for common cathode, 3V3 for common anode). |
| LED breathing magenta, nothing runs | Safe mode: the firmware needs a newer Device OS. Run `particle update` with USB connected, then flash again. |
| Nothing happens when you press the button | Check the button wiring on D5 and its 10k Ohm resistor. |

## Using the `GeminiWebhook` library in your own project

The `GeminiWebhook` library is not tied to PulseCheck. In any project, install `GeminiWebhook` and `ArduinoJson` with **Particle: Install Library**, copy `json_webhook_response_helper.h` into the `src` folder, and create a webhook with your own event name and prompt.

| Function | What it does |
|----------|--------------|
| `geminiSetup("my_event")` | Call once in `setup()`. The name must match your webhook's event name |
| `geminiSend(text)` | Sends the text to your webhook. Returns `false` if it is too soon or a reply is pending |
| `geminiReady()` | `true` when `geminiSend()` would send |
| `geminiWaiting()` | `true` while a request is out and no reply has arrived |
| `geminiGotReply()` | Call at the start of your reply handler. Stops the timeout. Returns `false` for a late reply |
| `geminiLoop()` | Call every time through `loop()`. Reports a timeout |
| `onGeminiError(String why)` | You define this. It is called when a request fails |

```cpp
#include "Particle.h"

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

#include "json_webhook_response_helper.h"
#include "GeminiWebhook.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

// The webhook's reply, for example {"answer": "Open a window"}
void myHandler(const char* event, const char* data) {
    String fullJson = json_webhook_response_helper(event, data);
    if (fullJson == "") return;
    if (!geminiGotReply()) return;

    // Gemini's whole reply; the answer is the text deep inside it
    JsonDocument doc;
    if (deserializeJson(doc, fullJson)) return;
    String answerText = doc["candidates"][0]["content"]["parts"][0]["text"].as<String>();

    // that text is JSON too
    JsonDocument answer;
    if (deserializeJson(answer, answerText)) return;
    Serial.println(answer["answer"].as<String>());
}

// Called when a request fails
void onGeminiError(String why) {
    Serial.println("No answer: " + why);
}

void setup() {
    Serial.begin(9600);
    geminiSetup("my_event");
    Particle.subscribe("hook-response/my_event", myHandler, MY_DEVICES);
    Particle.subscribe(System.deviceID() + "/hook-response/my_event", myHandler, MY_DEVICES);
}

void loop() {
    geminiLoop();
    if (geminiReady()) {
        geminiSend("temperature=72F humidity=40%");   // sends again every 10 s
    }
}
```

To change the limits, pass them to `geminiSetup()` in milliseconds, for example `geminiSetup("my_event", 5000, 30000)` for one request every 5 seconds and a 30 second timeout. The defaults are one request every 10 seconds and a 20 second timeout.
