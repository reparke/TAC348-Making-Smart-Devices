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
  - Press the button to send 10 minutes of real Fitbit heart rate and step data to **Google Gemini**
  - Gemini decides what the wearer is doing and whether anything looks wrong
  - The Photon 2 shows the answer on an RGB LED

## How It Works

```
Photon 2                      Particle Cloud                  Gemini
--------                      --------------                  ------
button pressed
Particle.publish(event)  -->  webhook adds the prompt   -->   reads the data
                              and the API key                 returns JSON
onWebhookReply()         <--  hook-response event       <--   {"state", "alert", "msg"}
set the RGB LED
```

- The Photon 2 never talks to Gemini directly. It just publishes an event
- The **webhook** does the AI call, then sends Gemini's answer back as a `hook-response` event
- A reply takes about 1 second

## Why a Webhook?

- The webhook holds your Gemini **API key**, so it never goes on the device
- **Important!** Keep your API key private: never put it in your code, a commit, a screenshot, or a chat
  - Anyone with your key can use up your quota
  - If it leaks, delete it and make a new one
- Review
  - [APIs and Webhooks](/lectures/week05/lecture_api_webhook.html)
  - [Particle + Gemini Integration](/lectures/weekX/lecture_particle_gemini_integration.html) for creating your Gemini API key

## Wiring

| Part | Pin | Resistor |
|------|-----|----------|
| RGB LED red | SCL | 330 Ohm |
| RGB LED green | MISO (MI on the board) | 330 Ohm |
| RGB LED blue | MOSI (MO on the board) | 330 Ohm |
| Button | D5 | 10k Ohm |

- Same wiring as the RGB LED and button exercise
- The button reads `LOW` when pressed

## The Data

- Real Fitbit data from a public dataset of 30 people
  - Furberg, R., Brinton, J., Keating, M., & Ortiz, A. (2016). *Crowd-sourced Fitbit datasets 03.12.2016-05.12.2016*. Zenodo. [doi.org/10.5281/zenodo.53894](https://doi.org/10.5281/zenodo.53894) (CC BY 4.0)
- One heart rate and one step reading per minute, for 10 minutes
- Sent as plain text

```
hr_bpm=[72,70,71,72,75,74,75,72,73,75] steps_per_min=[0,0,0,0,0,0,0,0,0,0] interval=1min
```

- Note: no double quotes in the data, or it breaks the webhook's JSON

## Five Windows

- Each button press sends the next window

| # | Window | Heart rate (bpm) | Steps per minute |
|---|--------|------------------|------------------|
| 1 | resting | 70 to 75 | 0 |
| 2 | walking | 96 to 104 | 88 to 104 |
| 3 | workout | 153 to 160 | 166 to 174 |
| 4 | sleep | 42 to 43 | 0 |
| 5 | anomaly | 63 to 70, then 138 to 144 for the last 4 minutes | 0 |

- The window name is **not** sent to Gemini
- The serial monitor prints it next to Gemini's answer, so you can grade the model
- Note: the dataset has no real emergencies, so the anomaly is a real resting window with 75 bpm added to the last 4 minutes

## Answer Key

| # | Window | Correct `state` | Correct `alert` | Safety rule fires? |
|---|--------|-----------------|-----------------|--------------------|
| 1 | resting | `resting` | `false` | no |
| 2 | walking | `walking` | `false` | no |
| 3 | workout | `workout` | `false` | no |
| 4 | sleep | `sleep` | `false` | no |
| 5 | anomaly | `resting` | `true` | **yes** |

- Note: 42 bpm while asleep is normal for a fit person
- In our tests, Gemini 3.5 Flash-Lite matched this key on all five windows, three times each

## Gemini's Answer

- The webhook tells Gemini exactly what to send back

```json
{"state": "workout", "alert": false, "msg": "Great pace, avg 156 bpm!"}
```

- `state`: one of `sleep`, `resting`, `walking`, `workout`
- `alert`: true when something looks concerning
- `msg`: a short note for a small watch screen
- The Photon 2 still checks every reply. Anything unexpected turns the LED magenta
  - Never trust the model's output blindly
- Review
  - [JSON Overview](/lectures/week11/lecture_json_overview.html)
  - [Retrieving Data from APIs using Mustache Templates](/lectures/week11/lecture_retrieving_data_mustache_templates.html): the webhook's `responseTemplate` pulls Gemini's answer out of its reply the same way

## Your Job

- `pulsecheck_setup.h` does the plumbing: the Fitbit data, the button, publishing, reading the reply, timeouts
  - You only change `EVENT_NAME` at the top
- In `pulsecheck.cpp`:
  - **TODO 1**: show Gemini's answer on the RGB LED in `onGeminiReply()` with `changeLedColor(r, g, b)`
  - **TODO 2** (optional): write your own `safetyRule()`

## When Gemini Gets It Wrong

- With our first prompt, Gemini missed the most important window: heart rate jumps while sitting still
  - Gemini: "Great workout!" and no alert
  - It looked at heart rate and ignored the steps
- It also reported the wrong average heart rate
  - Language models are not reliable at math over a long list of numbers

## Fixing the Prompt

- Adding one sentence to the prompt fixed the label

> Decide the state from the steps first: if steps stay near zero, the state is resting or sleep, never walking or workout, even when heart rate is high.

- A better prompt makes the right answer more likely
- But it is not a guarantee

## Safety Rule

- The guarantee comes from plain code on the Photon 2: `safetyRule()`
- Alert when **both** are true
  - the heart rate of the last quarter of the window is 30+ bpm above the first half
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

- Use `gemini-3.5-flash-lite`: one press a minute is about 100 requests per class
- Limits are per Google project, so use a key from your own Google account
- The daily limit resets at midnight Pacific time
- Ran out (error 429)? Switch the webhook to another model. Each model has its own quota

## Going Further

- **More signals**: real rings also track heart rate variability, skin temperature, blood oxygen, breathing, and sleep stages
  - Adding these did not stop Gemini from missing the anomaly. The safety rule still caught it
- **More Fitbit data**: test more windows from the same dataset
  - Gemini mixes up lying awake and sleeping, since heart rate and steps alone can't tell them apart
- **Real sensors**: replace the Fitbit data with readings from your smart watch build
- Note: PulseCheck is not a medical device. Do not send real personal health data to the free tier
