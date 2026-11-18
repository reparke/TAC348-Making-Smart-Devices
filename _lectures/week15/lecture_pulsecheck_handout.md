---
marp: false
theme: tac

week: 15
category: lectures
title: PulseCheck - Student Handout
---

<!-- headingDivider: 2 -->

Name _________________________________________  Partner _________________________________________

# PulseCheck Handout

Follow along with the [PulseCheck lecture](lecture_pulsecheck.html). Your instructor goes over the answers at the end of each part.

## Plan Your Prompt

Before you write your prompt in the webhook body, plan the five parts of your prompt. One short sentence each is enough.

| Part | Your sentence |
|------|---------------|
| Role: who is Gemini in this job? | |
| Input: what is the data, and in what units? | |
| Choices: what answers are allowed for `state`? | |
| Rules: how should it decide, and when should `alert` be true? | |
| Output: what should `msg` look like? | |


## Create the Webhook

Check off each step. The screenshots are in [Creating the Webhook](lecture_pulsecheck.html#creating-the-webhook) on the lecture page.

- [ ] Create a Gemini API key. Keep it private: it goes in the Particle console only
- [ ] In `pulsecheck_webhook_body_starter.json`, replace `TODO PROMPT` with your prompt (no double quotes inside it)
- [ ] Replace `TODO STATES` with `"sleep", "resting", "walking", "workout"`
- [ ] In the Particle console, go to **Cloud services > Integrations > Add new integration** and choose **Custom Webhook**
- [ ] On the **Webhook Builder** tab, fill in

| Field | Value |
|-------|-------|
| Name | `PulseCheck` |
| Event name | `pulsecheck` |
| URL | `https://generativelanguage.googleapis.com/v1beta/models/gemini-3.5-flash-lite:generateContent` |
| Request type | `POST` |
| Request format | `JSON` |

- [ ] Open **Extra settings**. Under **JSON data**, choose **Custom**, delete what is there, and paste your whole body file
- [ ] Under **HTTP headers**, add the key `x-goog-api-key` with your Gemini API key as the value
- [ ] Under **Response template**, paste

```
{% raw %}{{#candidates}}{{#content}}{{#parts}}{{{text}}}{{/parts}}{{/content}}{{/candidates}}{% endraw %}
```

- [ ] Click **Enable integration**
- [ ] Complete TODO 1 in `pulsecheck.cpp`, flash, and press the button. The LED turns white, then a color

If the LED turns magenta: __

## Part 1: Five Mystery Datasets

1. Open `data/fitbit_windows.csv` (it opens in Excel or Google Sheets) and look at the heart rate and step numbers for datasets A to E. **Before you press the button**, write your own guess for each one in the table below.

2. Press the button once per dataset (wait 10 seconds between presses). Copy Gemini's answer from the serial monitor.

| Dataset | Your guess: state | Your guess: alert? | Gemini: `state` | Gemini: `alert` | Gemini: `msg` | Correct? |
|---------|-------------------|--------------------|-----------------|-----------------|---------------|----------|
| A | | | | | | |
| B | | | | | | |
| C | | | | | | |
| D | | | | | | |
| E | | | | | | |


3. On which dataset did the safety rule fire ("Safety rule: alert" in the serial monitor)? __

4. Did Gemini get any dataset wrong? Which one, and what do you think confused it? __

5. Copy the sentence in your prompt that tells Gemini how to choose the state. __

6. Gemini's `msg` often mentions the average heart rate. Work out the real average heart rate for dataset E: __ Did Gemini's number match? __

## Part 2: More Signals

7. What does a METs value of 1.0 mean? __ What about 14? __ What does an intensity of 3 mean? __

8. Datasets F, G, and H all have **zero steps** the whole time. In `data/fitbit_windows.csv`, look only at the heart rate and steps columns for G. What would you guess? __ Now look at G's calories, intensity, and METs. What changes your mind? __

9. Set `PART` to `2`, flash, and run F, G, H **with your Part 1 prompt** (don't change it yet). Then update your prompt to explain the four new signals, and run them again.

| Dataset | Your guess: state / alert | Gemini, Part 1 prompt: `state` / `alert` | Gemini, updated prompt: `state` / `alert` | Correct? |
|---------|---------------------------|------------------------------------------|-------------------------------------------|----------|
| F | | | | |
| G | | | | |
| H | | | | |


10. Copy the sentences you added to your prompt for the new signals. __

11. In Part 2, the safety rule checks METs instead of steps. Why? __

## Wrap Up

12. On which datasets did the safety rule fire in total? __

13. Should a smart watch let Gemini alone decide when to raise a health alert? Why or why not? __

14. Name one more signal a real watch or ring could send that would help, and which dataset it would help with. __
