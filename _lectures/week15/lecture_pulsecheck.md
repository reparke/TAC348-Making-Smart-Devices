---
marp: false
theme: tac

week: 15
category: lectures
title: PulseCheck - Smart Devices and AI
---

<!-- headingDivider: 2 -->

# PulseCheck - Smart Devices and AI

## What Is PulseCheck?

- Smart watches and rings send your heart rate, steps, and sleep data to AI models for summaries and alerts
- In PulseCheck, the Photon 2 plays the smart watch
  - It sends an hour of heart rate and step data to **Google Gemini**
  - Gemini decides what you are doing and whether anything looks wrong
  - The Photon 2 shows the answer on its LED
- The data is fake, so no sensors or wiring are needed
- Exercise: [`_exercises/week15/pulsecheck`](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_exercises/week15/pulsecheck)

## How It Works

```
Photon 2                      Particle Cloud                  Gemini
--------                      --------------                  ------
make fake data
Particle.publish(event)  -->  webhook adds the prompt   -->   reads the data
                              and the API key                 returns JSON
onWebhookReply()         <--  hook-response event       <--   {"state", "alert", "msg"}
set the LED
```

- The Photon 2 never talks to Gemini directly. It just publishes an event
- The **webhook** does the AI call, then sends Gemini's answer back as a `hook-response` event
- A reply takes about 1 second

## Why a Webhook?

- The webhook holds your Gemini **API key**, so it never goes on the device
- **Important!** Keep your API key private: never put it in your code, a commit, a screenshot, or a chat
  - Anyone with your key can use up your quota
  - If it leaks, delete it in Google AI Studio and make a new one

## The Data

- One heart rate and one step reading per minute, for the last 60 minutes
- Sent as plain text

```
hr_bpm=[68,70,66,...] steps_per_min=[0,3,1,...] interval=1min
```

- Note: no double quotes in the data, or it breaks the webhook's JSON

## Five Scenarios

- Each tap of MODE sends the next scenario

| Scenario | What the data looks like | Correct answer |
|----------|--------------------------|----------------|
| resting | Heart rate about 68, almost no steps | resting |
| walking | Heart rate about 98, about 100 steps per minute | walking |
| workout | Heart rate climbs from 110 to 155, about 150 steps per minute | workout |
| sleep | Heart rate about 54, no steps | sleep |
| anomaly | Heart rate jumps to about 145 while sitting still | resting **+ alert** |

- The scenario name is **not** sent to Gemini
- The serial monitor prints it next to Gemini's answer, so you can grade the model

## Gemini's Answer

- The webhook tells Gemini exactly what to send back

```json
{"state": "workout", "alert": false, "msg": "Great pace, avg 132 bpm!"}
```

- `state`: one of `sleep`, `resting`, `walking`, `workout`
- `alert`: true when something looks concerning
- `msg`: a short note for a small watch screen
- The Photon 2 still checks every reply. Anything unexpected turns the LED magenta
  - Never trust the model's output blindly

## Your Job

- `pulsecheck_setup.h` does the plumbing: fake data, publishing, reading the reply, timeouts
  - You only change `EVENT_NAME` at the top
- In `pulsecheck.cpp`:
  - **TODO 1**: show Gemini's answer on the LED in `onGeminiReply()`
  - **TODO 2** (optional): write your own `safetyRule()`

## When Gemini Gets It Wrong

- Gemini got walking, workout, sleep, and resting right
- It missed the most important one: heart rate jumps to 145 while sitting still
  - Gemini: "Great workout!" and no alert
  - It looked at heart rate and ignored the steps
- It also reported an average heart rate of 135 for an hour that averaged about 99
  - Language models are not reliable at math over 60 numbers

## Fixing the Prompt

- Adding one sentence to the prompt fixed the label

> Decide the state from the steps first: if steps stay near zero, the state is resting or sleep, never walking or workout, even when heart rate is high.

- A better prompt makes the right answer more likely
- But it is not a guarantee

## Safety Rule

- The guarantee comes from plain code on the Photon 2: `safetyRule()`
- Alert when **both** are true
  - the last 15 minutes' heart rate is 30+ bpm above the first 30 minutes
  - steps stay under 10 per minute
- The alert turns on even if Gemini says no, or the webhook fails
- `defaultSafetyRule()` in `pulsecheck_setup.h` is a ready-made version
- Let the model interpret the data. Keep safety checks in code you can test

## Free Tier Limits

<img src="lecture_pulsecheck.assets/gemini-free-tier-limits.webp" alt="Gemini API rate limit page in Google AI Studio, free tier" style="width:700px;" />

| Model | Requests per minute | Requests per day |
|-------|---------------------|------------------|
| `gemini-3.5-flash-lite` | 15 | 500 |
| `gemini-3.6-flash` | 5 | 20 |
| `gemini-2.5-flash` | 5 | 20 |

- Use `gemini-3.5-flash-lite`: one tap a minute is about 100 requests per class
- Limits are per Google project, so use a key from your own Google account
- The daily limit resets at midnight Pacific time
- Ran out (error 429)? Switch the webhook to another model. Each model has its own quota

## Going Further

- **More signals**: real rings also track heart rate variability, skin temperature, blood oxygen, breathing, and sleep stages
  - Adding these did not stop Gemini from missing the anomaly. The safety rule still caught it
- **Real data**: try a public Fitbit dataset
  - Gemini mixes up lying awake and sleeping, since heart rate and steps alone can't tell them apart
- **Real sensors**: replace `generateFakeData()` in `pulsecheck_setup.h` with readings from your smart watch build
- Note: PulseCheck is not a medical device. Do not send real personal health data to the free tier
