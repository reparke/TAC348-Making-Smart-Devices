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

Follow along with the [PulseCheck lecture](lecture_pulsecheck.html). Don't look at **Check Your Answers** until you finish each part.

## Plan Your Prompt

Before you write your prompt in the webhook body, plan the five parts of your prompt. One short sentence each is enough.

| Part | Your sentence |
|------|---------------|
| Role: who is Gemini in this job? | |
| Input: what is the data, and in what units? | |
| Choices: what answers are allowed for `state`? | |
| Rules: how should it decide, and when should `alert` be true? | |
| Output: what should `msg` look like? | |

<!-- e.g. Role: You are the analysis engine for a fitness tracker. Input: heart rate in beats per minute and steps per minute, one value per minute. Choices: exactly one of sleep, resting, walking, workout. Rules: alert only if the heart rate is concerning for the activity. Output: msg is a friendly note of at most 40 characters. -->

## Part 1: Five Mystery Datasets

1. Open `src/pulsecheck_setup.h` and look at the heart rate and step numbers for datasets A to E. **Before you press the button**, write your own guess for each one in the table below.

2. Press the button once per dataset (wait 10 seconds between presses). Copy Gemini's answer from the serial monitor.

| Dataset | Your guess: state | Your guess: alert? | Gemini: `state` | Gemini: `alert` | Gemini: `msg` | Correct? |
|---------|-------------------|--------------------|-----------------|-----------------|---------------|----------|
| A | | | | | | |
| B | | | | | | |
| C | | | | | | |
| D | | | | | | |
| E | | | | | | |

<!-- A walking false | B sleep false | C resting true (safety rule fires) | D resting false | E workout false -->

3. On which dataset did the safety rule fire ("Safety rule: alert" in the serial monitor)? __ <!-- C -->

4. Did Gemini get any dataset wrong? Which one, and what do you think confused it? __ <!-- Most often C: a high heart rate looks like a workout unless the prompt says to decide from steps first. B vs D can also be mixed up: both have zero steps -->

5. Copy the sentence in your prompt that tells Gemini how to choose the state. __ <!-- e.g. "Decide the state from the steps first: if steps stay near zero, the state is resting or sleep..." -->

6. Gemini's `msg` often mentions the average heart rate. Work out the real average heart rate for dataset E: __ <!-- 1562 / 10 = 156.2 bpm --> Did Gemini's number match? __ <!-- Often close but not exact: language models are not reliable at math -->

## Part 2: More Signals

7. What does a METs value of 1.0 mean? __ <!-- sitting still --> What about 14? __ <!-- very hard exercise -->

8. Datasets F, G, and H all have **zero steps** the whole time. Look only at `HR_PART2` and `STEPS_PART2` for G. What would you guess? __ <!-- a dangerous heart rate spike at rest: about 190 bpm with no steps --> Now look at `METS10_PART2` for G. What changes your mind? __ <!-- METs of 9 to 14 mean hard exercise, like cycling, so it's a workout -->

9. Set `PART` to `2`, flash, and run F, G, H **with your Part 1 prompt** (don't change it yet). Then update your prompt to explain `mets` and `sleep`, and run them again.

| Dataset | Your guess: state / alert | Gemini, Part 1 prompt: `state` / `alert` | Gemini, updated prompt: `state` / `alert` | Correct? |
|---------|---------------------------|------------------------------------------|-------------------------------------------|----------|
| F | | | | |
| G | | | | |
| H | | | | |

<!-- F sleep true (safety rule fires) | G workout false | H resting true (safety rule fires) -->

10. Copy the sentences you added to your prompt for `mets` and `sleep`. __ <!-- e.g. "mets is energy use: 1.0 is still, 3+ is exercise even with zero steps. sleep says asleep, restless, or awake each minute; if mostly asleep, the state is sleep." -->

11. In Part 2, the safety rule checks METs instead of steps. Why? __ <!-- Steps miss exercise like cycling or rowing. A rule based on steps could raise a false alarm during a bike ride; METs show the body is working -->

## Wrap Up

12. On which datasets did the safety rule fire in total? __ <!-- C, F, H -->

13. Should a smart watch let Gemini alone decide when to raise a health alert? Why or why not? __ <!-- No. A better prompt makes the right answer more likely but is not a guarantee. Let the model interpret the data; keep safety checks in plain code you can test -->

14. Name one more signal a real watch or ring could send that would help, and which dataset it would help with. __ <!-- e.g. heart rate variability, skin temperature, blood oxygen, breathing rate, time of day (would help tell B sleep from D resting) -->
