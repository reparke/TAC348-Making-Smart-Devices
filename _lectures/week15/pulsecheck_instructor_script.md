# PulseCheck: Instructor Script

Talk track for running the [PulseCheck lecture](lecture_pulsecheck.md) with the [student handout](lecture_pulsecheck_handout.md) in one 100-minute class. Times are a guide. Lines marked **Say** are suggested wording. **Ask** lines have the expected answer after them.

## Before Class

- [ ] Each student kit has: common anode RGB LED, three 330 Ohm resistors, one 10k Ohm resistor, a push button, jumper wires
- [ ] Students have a Google account for their own Gemini API key (each key has its own free-tier quota)
- [ ] Check that `gemini-3.5-flash-lite` still works: Google retires models. If it returns 404, use the newest Flash-Lite model and update the lecture
- [ ] Build and run `pulsecheck_final` on your own Photon 2 once. Press through A to E, then set `PART = 2` and press through F to H, so you have a working demo
- [ ] Print the handout, one per pair
- [ ] Post the starter zip link: `/resources/pulsecheck/pulsecheck_start.zip`

## 0:00 to 0:10 What Is PulseCheck?

**Say:** "Your watch or ring sends your heart rate to the cloud, and more and more often an AI model reads it and tells you what's going on. Today the Photon 2 is the watch. You'll send it real Fitbit data, Gemini will decide what the person is doing, and you'll grade Gemini."

- Show the demo: press the button, LED goes white, then a color in about a second
- **Ask:** "What could go wrong if a watch trusts the AI completely?" Expected: it misses an emergency, or raises a false alarm
- Tell them there are two parts and a handout, and that the answer key is at the bottom of the lecture. They shouldn't look until they finish each part

## 0:10 to 0:20 How It Works and Why a Webhook

- Walk through the pipeline diagram: publish, webhook, Gemini, `hook-response`
- **Say:** "The Photon never talks to Gemini. It publishes an event, the same way as the webhook lecture in week 5. The webhook adds the prompt and the API key."
- Stress API key safety: never in code, a commit, a screenshot, or a chat
- **Ask:** "Why not put the key in the firmware?" Expected: anyone with the device or the code could read it and use up the quota

## 0:20 to 0:35 Wiring and Starter Code

- Wiring table on the lecture page. Common mistakes:
  - The RGB LED is **common anode**: the long leg goes to **3V3**, not GND. If colors look inverted (white when it should be off), the LED is in backwards or it's a common cathode LED
  - Button: 10k from D5 to 3V3, button from D5 to GND. Use diagonal legs on the button
- Download and unzip the starter, open `pulsecheck_start` in Workbench
- Point out the two files: `pulsecheck.cpp` (theirs) and `pulsecheck_setup.h` (the plumbing, same style as earlier setup headers)
- They change `EVENT_NAME` to `pulsecheck_` plus their USC username

**Say:** "Every device in the class product shares one event stream. If two of you use the same event name, every press triggers both webhooks."

## 0:35 to 0:50 Webhook and Gemini Key

- Students create a Gemini key ([Particle + Gemini Integration](/lectures/weekX/lecture_particle_gemini_integration.html))
- Fill in W1 to W5 in `pulsecheck_webhook_starter.json`, paste into **Custom template** (not Webhook Builder), add the key in the Console only
- W4 is their own prompt. Don't give them the final prompt yet. Let the first version be simple
- Then TODO 1 (LED colors) and flash

Common problems:

| Symptom | Fix |
|---------|-----|
| White, then magenta after 20 s | Event name in the webhook doesn't match `EVENT_NAME` |
| Error 400 / `API_KEY_INVALID` | Key missing, or the template was pasted into Webhook Builder |
| Error 404 | Model retired. Switch W2 to the current Flash-Lite model |
| Error 429 | Quota used up. Wait, or switch to another model for the day |
| Breathing magenta, nothing runs | Safe mode. `particle update` over USB, then flash again |

## 0:50 to 1:05 Part 1: Five Mystery Datasets

- Handout questions 1 and 2: guess first from the numbers, then press through A to E
- Walk around. Look at their serial monitors

**Ask** (after most pairs finish): "Who got all five right?" Then "Who got C wrong? What did Gemini say?"

- With a simple prompt, Gemini usually calls C a workout: the heart rate jumps to 144, but there are zero steps
- This is the "When Gemini Gets It Wrong" slide. Show the one-sentence fix: decide the state from the steps first
- Have them add that sentence to their prompt and re-run C

**Say:** "A better prompt makes the right answer more likely. It doesn't make it certain. That's why we also have the safety rule."

- Safety rule slide: plain code on the Photon, alert if the last quarter's heart rate is 30+ above the first half while still. It fired on C no matter what Gemini said
- Handout question 6: the real average for E is 156.2. Gemini's number is often a little off. Language models are not calculators

## 1:05 to 1:10 Check Part 1

- Reveal **Check Your Answers** for A to E
- Point out C was edited (75 bpm added) to make a clear spike. The other four are real, unedited

## 1:10 to 1:30 Part 2: More Signals

**Say:** "Heart rate and steps can't tell everything apart. Lying awake looks like sleeping. Cycling has a high heart rate and no steps. Real watches send more."

- Introduce `mets` (1.0 = still, 3+ = exercise even without steps) and `sleep` (awake, asleep, restless)
- Students set `PART = 2` and flash
- Handout question 9: run F, G, H with the **Part 1 prompt** first, then update the prompt and run again

What to expect (confirm this in your own demo run before class):

- With the Part 1 prompt, G (heart rate near 190, zero steps) is usually called resting with an alert. The steps-first sentence now causes a mistake
- After the prompt explains METs, G becomes workout with no alert
- F (spike while asleep) and H (spike while sitting awake) should alert either way. The safety rule fires on both

**Ask:** "The steps-first sentence fixed C. Why did it break G?" Expected: steps are zero in G, but the person is exercising. A rule that was right for one dataset was wrong for another

**Ask:** "Why does the Part 2 safety rule check METs instead of steps?" Expected: steps miss cycling and rowing, so a steps-based rule could raise a false alarm on a bike ride

## 1:30 to 1:35 Check Part 2

- Reveal F to H in **Check Your Answers**
- F and H are real heart rate jumps with no movement. A spike like that can have a harmless cause, but a watch should still flag it

## 1:35 to 1:40 Wrap Up

- Handout questions 12 to 14
- Key message: **let the model interpret the data, and keep safety checks in code you can test**
- Free tier: one press a minute is about 100 requests per class, well under 500 per day for `gemini-3.5-flash-lite`
- Reminder: PulseCheck is not a medical device. Don't send real personal health data to the free tier

## Answer Key

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
