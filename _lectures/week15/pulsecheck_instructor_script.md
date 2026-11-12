# PulseCheck: Class Script (90 minutes)

A minute-by-minute script for teaching the [PulseCheck lecture](lecture_pulsecheck.md) with the [student handout](lecture_pulsecheck_handout.md).

Each segment has four kinds of lines:

- **Show**: what to put on the screen or hold up
- **Say**: suggested wording, read it or put it in your own words
- **Ask**: a question for the class, followed by **Expect**, the answer you are looking for
- **Students do**: what they should be working on

Times are a guide. If you run late, the cut list is at the end.

| Time | Segment |
|------|---------|
| 0:00 | 1. Hook and demo |
| 0:07 | 2. How it works, and why a webhook |
| 0:15 | 3. Wiring |
| 0:25 | 4. Starter code |
| 0:32 | 5. Gemini key, prompt, and webhook |
| 0:48 | 6. Part 1: five mystery datasets |
| 0:59 | 7. When Gemini gets it wrong, and the safety rule |
| 1:05 | 8. Check Part 1 |
| 1:08 | 9. Part 2: more signals |
| 1:23 | 10. Check Part 2 |
| 1:26 | 11. Wrap up |

## Before Class

- [ ] Each kit has: common anode RGB LED, three 330 Ohm resistors, one 10k Ohm resistor, a push button, jumper wires
- [ ] Students have a Google account for their own Gemini API key (each key has its own free-tier quota)
- [ ] Check that `gemini-3.5-flash-lite` still works. Google retires models. If it returns 404, use the newest Flash-Lite model and update the lecture
- [ ] Flash `pulsecheck_final` on your own Photon 2. Press through A to E, then set `PART = 2` and press through F to H. Write down what Gemini answered, so you know what students will see
- [ ] Have two windows ready on the projector: the lecture page, and a serial monitor (`particle serial monitor --follow`)
- [ ] Print the handout, one per pair
- [ ] Post the starter zip link: `/resources/pulsecheck/pulsecheck_start.zip`

## 1. Hook and Demo (0:00 to 0:07)

**Show:** your own watch or ring if you have one. Then your wired Photon 2 under the camera.

**Say:** "How many of you wear something that tracks your heart rate? That data goes to the cloud, and more and more often an AI model reads it and tells you what's going on: you slept badly, you had a good workout, something looks wrong. Today the Photon 2 is the watch. You'll send it real Fitbit data from real people. Gemini will decide what each person is doing. Your job is to grade Gemini."

**Show:** press the button on your demo. The LED goes white, then a color about a second later. Show the serial monitor line.

```
Dataset A | Gemini: state=walking alert=0 msg="Steady walk, avg 100 bpm"
```

**Say:** "White means waiting for Gemini. Then the color is the answer: green resting, yellow walking, orange workout, blue sleep. Blinking red is an alert."

**Ask:** "What could go wrong if a watch trusts the AI completely?"
**Expect:** it misses a real emergency, or it raises a false alarm and scares someone. Either answer is good. Tell them they will see both today.

**Say:** "There are two parts and a handout. The answer key is at the bottom of the lecture page. Don't scroll down to it until I say so."

**Students do:** find a partner, take one handout per pair.

## 2. How It Works, and Why a Webhook (0:07 to 0:15)

**Show:** the "How It Works" diagram on the lecture page.

**Say:** "Follow the arrows. You press the button. The Photon publishes an event, just text. A webhook in the Particle Cloud catches it, adds a prompt and an API key, and calls Gemini. Gemini answers with JSON. The webhook sends that back as a hook-response event, and your code sets the LED."

**Ask:** "Where have we seen this publish, webhook, response pattern before?"
**Expect:** the weather or API webhook exercises (week 5 and week 11). It's the same pattern, with Gemini as the API.

**Show:** the example reply.

```json
{"state": "workout", "alert": false, "msg": "Great pace, avg 156 bpm!"}
```

**Ask:** "What are the three keys, and what type is each one?"
**Expect:** `state` is a string, `alert` is a boolean, `msg` is a string.

**Ask:** "Why don't we put the Gemini API key in the firmware and call Gemini straight from the Photon?"
**Expect:** anyone with the code or the device could read the key and use up the quota. The webhook keeps the key in the cloud.

**Say:** "Important: your API key never goes in your code, a commit, a screenshot, or a chat. If it leaks, delete it and make a new one."

## 3. Wiring (0:15 to 0:25)

**Show:** the wiring table on the lecture page.

| Part | Pin | Resistor |
|------|-----|----------|
| RGB LED red | SCL | 330 Ohm |
| RGB LED green | MISO (MI on the board) | 330 Ohm |
| RGB LED blue | MOSI (MO on the board) | 330 Ohm |
| RGB LED common (long leg) | 3V3 | none |
| Button | D5 | 10k Ohm |

**Say:** "This is the same RGB LED and button wiring you've done before. Two things to watch. First, this LED is common anode, so the long leg goes to 3V3, not ground. Second, the button: the 10k resistor goes from D5 to 3V3, and the button connects D5 to ground. Use two legs that are diagonal from each other."

**Ask:** "How do you tell a 330 Ohm resistor from a 10k?"
**Expect:** the color bands. 330 is orange, orange, brown. 10k is brown, black, orange. (Or measure with a multimeter.)

**Ask:** "With this button wiring, what does D5 read when the button is not pressed?"
**Expect:** `HIGH`. The resistor pulls it up to 3.3 V. Pressing connects it to ground, so it reads `LOW`.

**Students do:** wire the LED and the button. Walk around.

| If you see | It means |
|------------|----------|
| Colors inverted after flashing (white when it should be off) | The LED is common cathode, or the long leg is on ground |
| One color never lights | That leg's resistor or wire is in the wrong row |

## 4. Starter Code (0:25 to 0:32)

**Show:** the starter zip link, then the `pulsecheck_start` folder open in Workbench.

**Say:** "There are two files in `src`. `pulsecheck.cpp` is yours. `pulsecheck_setup.h` is the plumbing, the same idea as the setup headers we've used before: the data, the button, publishing, reading the reply, timeouts. You don't change anything in it for Part 1."

**Show:** the top of `pulsecheck_setup.h`.

```cpp
const char* EVENT_NAME = "pulsecheck";
```

**Say:** "This is the event the Photon publishes. Your webhook listens for the same name. It's already set in both places, so leave it."

**Ask:** "What happens if the event name in the code and the one in the webhook don't match?"
**Expect:** the webhook never fires, so no reply comes back. The LED stays white and then turns magenta after 20 seconds.

**Students do:** download, unzip, open the folder, and read through `pulsecheck.cpp`.

## 5. Gemini Key, Prompt, and Webhook (0:32 to 0:48)

**Show:** Google AI Studio's API key page, then `pulsecheck_webhook_body_starter.json`.

**Say:** "Make a Gemini API key with your own Google account. Then open the webhook body file. It's the JSON we send to Gemini, and it has two blanks: `TODO PROMPT` and `TODO STATES`."

**Say:** "The prompt is the interesting one. It's the instructions Gemini reads before it sees the data. Gemini only knows what you tell it."

**Show:** the "Writing Your Prompt" table on the lecture page, then the one-line prompt: *Tell me what this person is doing.*

**Ask:** "If this were the whole prompt, what would Gemini have to guess?"
**Expect:** what the numbers are and their units, which words it's allowed to answer with, what counts as an alert, and how long the message can be.

**Say:** "A good prompt answers five questions. Role: who is Gemini here? Input: what is the data and what units? Choices: what answers are allowed? Rules: how does it decide, and when is it an alert? Output: what should the reply look like? Plan one sentence for each on the handout, then type them into `TODO PROMPT`."

**Ask:** "Your code checks for the word `resting`. What happens if your prompt tells Gemini to answer `at rest`?"
**Expect:** the words wouldn't match. Use the same words in the prompt as in the code. (The `TODO STATES` list also forces the four exact values.)

**Say:** "Two more tips. Don't use double quotes inside the prompt, because it sits inside JSON. And keep your first version simple. We write prompts like code: test, find the mistake, change one sentence, test again."

**Students do:** fill in "Plan Your Prompt" on the handout, then type it into `TODO PROMPT`.

**Ask:** "`TODO STATES` is a list of the only four values `state` is allowed to be. Why limit Gemini like that?"
**Expect:** so the firmware always gets a value it knows. Otherwise Gemini might answer "jogging" or "Resting." and the `if` statements wouldn't match.

**Show:** the "Creating the Webhook" section, then do it live in the Particle Console: Cloud services, Integrations, Add new integration, Custom Webhook.

| Field | Value |
|-------|-------|
| Name | `PulseCheck` |
| Event name | `pulsecheck` |
| URL | `https://generativelanguage.googleapis.com/v1beta/models/gemini-3.5-flash-lite:generateContent` |
| Request type | `POST` |
| Request format | `JSON` |
| Extra settings: JSON data | **Custom**, then paste the whole body file |
| Extra settings: HTTP headers | key `x-goog-api-key`, value your API key |
| Extra settings: Response template | `{{#candidates}}{{#content}}{{#parts}}{{{text}}}{{/parts}}{{/content}}{{/candidates}}` |

**Say:** "This is the same Webhook Builder you used in the Gemini lecture. Three things go under Extra settings: the body, the key as a header, and the response template. Then do TODO 1 in `pulsecheck.cpp`: set the LED color for each state with `changeLedColor`. Flash it."

**Ask:** "The body has `{{{PARTICLE_EVENT_VALUE}}}` in it. What does Particle put there?"
**Expect:** the data string the Photon published: the heart rate and steps lists.

**Students do:** key, webhook, TODO 1, flash, first button press.

| If you see | Fix |
|------------|-----|
| White, then magenta after 20 seconds | No webhook, or its event isn't `pulsecheck` |
| Error 400 or `API_KEY_INVALID` | The `x-goog-api-key` header is missing or wrong, or something other than the body file is in JSON data |
| Error 404 | The model was retired. Use the current Flash-Lite model in the URL |
| Error 429 | Quota used up. Wait a minute, or switch the URL to another model for today |
| LED breathing magenta, nothing runs | Safe mode. Run `particle update` over USB, then flash again |
| Nothing happens on a press | Button wiring. Check D5, the 10k resistor, and the diagonal legs |

**Checkpoint at 0:48:** every pair's LED should turn white and then a color. Pairs that are stuck can watch a neighbor for Part 1 and catch up after.

## 6. Part 1: Five Mystery Datasets (0:48 to 0:59)

**Show:** the Part 1 arrays in `pulsecheck_setup.h` (`HR_PART1` and `STEPS_PART1`).

**Say:** "There are five datasets, A to E. Each one is ten minutes of a real person's heart rate and steps, one reading per minute. One is resting, one is walking, one is a workout, one is sleep, and one is something a watch should worry about. I'm not telling you which is which. Before you press anything, look at the numbers and write your own guess on the handout, question 1."

**Students do (3 minutes):** guess A to E on the handout.

**Say:** "Now press the button once per dataset. Wait ten seconds between presses. Copy Gemini's state, alert, and msg from the serial monitor into the table."

**Students do (5 minutes):** run A to E, fill in handout questions 2 to 5.

**Ask** (when most pairs are done): "Which dataset was the easiest to guess, and why?"
**Expect:** E. Heart rate in the 150s and about 170 steps a minute is clearly running. A is also easy: about 100 steps a minute is a walk.

**Ask:** "B and D both have zero steps. How did you tell them apart?"
**Expect:** the heart rate. B is 42 to 43, which is very low, so sleep. D is in the 70s, so awake and resting.

**Ask:** "What did Gemini say for C? Did anyone get something different from their neighbor?"
**Expect:** mixed answers. That's the point. Many will have `workout` with no alert. Some will have `resting` with an alert. Write both on the board.

## 7. When Gemini Gets It Wrong, and the Safety Rule (0:59 to 1:05)

**Show:** dataset C's numbers.

```
hr_bpm=[70,68,66,68,65,68,144,143,143,138] steps_per_min=[0,0,0,0,0,0,0,0,0,0]
```

**Ask:** "Describe in plain words what happened to this person."
**Expect:** they were sitting still at about 68 bpm, and then their heart rate doubled to about 144 without them moving at all.

**Say:** "With a simple prompt, Gemini often says: great workout, no alert. It looked at the heart rate and ignored the steps. This is the most important dataset, and it's the one the model misses."

**Show:** the "Fixing the Prompt" sentence on the lecture page.

> Decide the state from the steps first: if steps stay near zero, the state is resting or sleep, never walking or workout, even when heart rate is high.

**Students do (2 minutes):** add that sentence to the prompt in the Console (Edit, Extra settings, JSON data), save, press through to C again.

**Ask:** "Did C change?"
**Expect:** yes for most pairs: now `resting` with `alert` true.

**Ask:** "Is the problem solved now? Can we promise it will always say alert?"
**Expect:** no. A better prompt makes the right answer more likely, but the model can still be wrong, or the webhook can fail, or the quota can run out.

**Show:** the Safety Rule section, and the serial monitor line `Safety rule: alert`.

**Say:** "So the guarantee doesn't come from the model. It comes from a few lines of plain code on the Photon. If the average heart rate of the last quarter of the window is 30 or more above the first half, and the person is still, raise the alert. It doesn't matter what Gemini says. Did you notice the LED blinked red on C even when Gemini said workout? That was this rule."

**Ask:** "Handout question 6. What's the real average heart rate of E, and did Gemini's msg match?"
**Expect:** 156.2 bpm. Gemini's number is often close but not exact. Language models are not calculators.

## 8. Check Part 1 (1:05 to 1:08)

**Show:** scroll to **Check Your Answers**, rows A to E only.

| Dataset | What it is | `state` | `alert` | Safety rule fires? |
|---------|------------|---------|---------|--------------------|
| A | walking | walking | false | no |
| B | sleep | sleep | false | no |
| C | heart rate spike at rest | resting | true | **yes** |
| D | resting | resting | false | no |
| E | workout (running) | workout | false | no |

**Say:** "Mark your guesses and Gemini's answers. One honest note: the Fitbit data had no clear emergency in these people, so C is a real resting window with 75 bpm added to the last four minutes. The other four are untouched."

**Ask:** "Who beat Gemini? Who did Gemini beat?"
**Expect:** a show of hands. Most students get all five. Gemini usually gets four or five, depending on the prompt.

## 9. Part 2: More Signals (1:08 to 1:23)

**Say:** "Heart rate and steps can't tell everything apart. Lying awake in bed looks the same as sleeping. And what about someone on a bike? High heart rate, zero steps. What would our steps-first prompt say about them?"

**Ask:** "What would it say?"
**Expect:** resting with an alert. A false alarm.

**Show:** the "Part 2: More Signals" table.

**Say:** "Real watches send more than two signals. Part 2 adds four from the same Fitbit dataset, so six in total. Calories per minute: about 1 at rest, 10 or more in hard exercise. Intensity: Fitbit's own activity level from 0, sedentary, to 3, very active. METs: how hard the body is working compared to rest, where 1.0 is sitting still and 3 or more is exercise, even with no steps. And sleep: Fitbit's sleep tracking for each minute, awake, asleep, or restless."

**Ask:** "Calories, intensity, and METs all come from the motion sensor. Why send three signals that mostly agree?"
**Expect:** they back each other up. If one is noisy or missing, the others still show whether the body is working. But it also means more for the prompt to explain.

**Show:** the top of `pulsecheck_setup.h`.

```cpp
const int PART = 1;
```

**Say:** "Change `PART` to 2 and flash. The button now sends three new datasets, F, G, and H. All three have zero steps the whole time. Do handout question 8 first: guess G from heart rate and steps only, then look at its METs."

**Students do (3 minutes):** set `PART = 2`, flash, handout questions 7 and 8.

**Say:** "Now run F, G, H, but don't change your prompt yet. Write down what Gemini says. Then update your prompt so Gemini knows what the four new signals mean, and run all three again."

**Students do (9 minutes):** handout questions 9 and 10.

What to expect (confirm against your own run before class):

| Dataset | With the Part 1 prompt | After the prompt explains the new signals |
|---------|------------------------|-----------------------------------------------|
| F | often `resting` with an alert, sometimes `sleep` | `sleep`, alert true |
| G | `resting` with an alert: a false alarm | `workout`, alert false |
| H | `resting`, alert true | `resting`, alert true |

**Ask:** "The steps-first sentence fixed C. What did it do to G?"
**Expect:** it broke G. Steps are zero, so the prompt says never workout, but the person is exercising hard. A rule that was right for one dataset was wrong for another.

**Ask:** "What did you add to your prompt?" (have one or two pairs read theirs)
**Expect:** something like: calories is about 1 at rest; intensity goes from 0 sedentary to 3 very active; mets is energy use, 1.0 is still and 3 or more is exercise even with no steps; sleep is asleep, restless, or awake each minute, and if it's mostly asleep the state is sleep.

**Ask:** "The safety rule in Part 2 checks METs instead of steps. Why?"
**Expect:** steps miss exercise like cycling or rowing. A rule that only looks at steps could raise a false alarm in the middle of a bike ride.

## 10. Check Part 2 (1:23 to 1:26)

**Show:** **Check Your Answers**, rows F to H.

| Dataset | What it is | `state` | `alert` | Safety rule fires? |
|---------|------------|---------|---------|--------------------|
| F | heart rate spike while asleep | sleep | true | **yes** |
| G | workout with no steps (like cycling) | workout | false | no |
| H | heart rate spike while sitting awake | resting | true | **yes** |

**Say:** "These three are real and unedited. F is someone asleep whose heart rate jumps from 62 to 97. H is someone sitting at 11 in the morning whose heart rate climbs from 66 to 100. Spikes like these can have a harmless cause, a bad dream or a stressful email. But a watch should still flag them and let the person decide."

## 11. Wrap Up (1:26 to 1:30)

**Ask:** "On which datasets did the safety rule fire?"
**Expect:** C, F, and H. The three where heart rate jumped while the body was still.

**Ask:** "Should a smart watch let Gemini alone decide when to raise a health alert?"
**Expect:** no. The model is good at interpreting, and its answers got better with a better prompt and more signals. But it can still be wrong, so safety checks belong in code you can test.

**Say:** "That's the idea to take with you for any project that uses AI. Let the model interpret the data. Keep the safety checks in plain code. And one more thing: PulseCheck is not a medical device. Don't send your real health data to a free-tier AI service."

**Ask:** "Handout question 14. What other signal would help, and with which dataset?"
**Expect:** heart rate variability, skin temperature, blood oxygen, breathing rate, or time of day (which would help tell B from D).

**Students do:** finish the handout and turn it in. Leave the circuit built if you plan to use it again.

## If You Run Short on Time

- **Cut first:** handout question 6 (the average heart rate). Mention it in one sentence instead
- **Cut next:** the "before" run in segment 9. Have students update the prompt right away and run F to H once
- **If setup runs long:** do Part 2 as a demo on your own Photon and have students fill in the handout from your serial monitor
- **Do not cut:** segment 7. Dataset C and the safety rule are the point of the lesson

## Full Answer Key

| Dataset | What it is | `state` | `alert` | Safety rule |
|---------|------------|---------|---------|-------------|
| A | walking | walking | false | no |
| B | sleep | sleep | false | no |
| C | heart rate spike at rest (edited) | resting | true | yes |
| D | resting | resting | false | no |
| E | workout (running) | workout | false | no |
| F | heart rate spike while asleep | sleep | true | yes |
| G | workout with no steps (like cycling) | workout | false | no |
| H | heart rate spike while sitting awake | resting | true | yes |

Data: Furberg, R., Brinton, J., Keating, M., & Ortiz, A. (2016). *Crowd-sourced Fitbit datasets 03.12.2016-05.12.2016*. Zenodo. [doi.org/10.5281/zenodo.53894](https://doi.org/10.5281/zenodo.53894) (CC BY 4.0)
