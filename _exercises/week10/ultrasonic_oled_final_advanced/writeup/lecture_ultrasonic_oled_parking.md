---
marp: true
theme: itp

week: 10
category: lectures
title: Ultrasonic Sensor + OLED Parking Sensor
---

<!-- headingDivider: 2 -->

# Ultrasonic Sensor + OLED
## Parking Sensor

## Overview

* Build a **parking sensor** display using the ultrasonic sensor and OLED
* The sensor distance controls what is drawn on screen in real time
* Two new ideas
  * **Continuous mapping**: a sensor value drives a graphic directly instead of choosing between fixed screens
  * **Signal smoothing**: average the last several readings to reduce noise

## What We're Building

* The OLED shows three things at once
  * A **zone label** (FAR / NEAR / STOP!)
  * The **distance** in inches
  * A **bar graph** that fills as your hand gets closer

* Three zones based on distance
  * **FAR**: more than 24 inches away
  * **NEAR**: between 4 and 24 inches
  * **STOP!**: closer than 4 inches

## OLED Layout

```
┌────────────────────────┐
│ FAR                    │  ← zone label
│ 18.5 in                │  ← distance
│                        │
│ ┌──────────────────┐   │  ← bar outline
│ │███████           │   │  ← fill grows as hand approaches
│ └──────┬───────────┘   │
│        ^-- STOP tick   │
└────────────────────────┘
```

* The tick mark on the bar shows where the STOP zone begins

## Discrete vs. Continuous Display

* In the previous exercise, each zone had its **own separate screen**
  * FAR screen → one set of shapes
  * NEAR screen → different shapes
  * CLOSE screen → different shapes again

* In this exercise, there is **one screen** — but the bar changes with every reading
  * The bar width is *calculated* from the distance
  * It is not chosen from a list of fixed options

* This is how real data visualizations work

## The `map()` Function

* `map()` converts a value from one range to another

```c++
map(value, fromLow, fromHigh, toLow, toHigh)
```

* Example: convert a distance (0–24 in) to a bar width (0–60 px)

```c++
int barFill = map(inches, 0, 24, 60, 0);
//  inches = 0  →  barFill = 60  (full bar — hand is right here)
//  inches = 24 →  barFill = 0   (empty bar — hand is far away)
```

* Notice `toLow` and `toHigh` are **reversed** — as distance increases, bar shrinks

## Clamping Before `map()`

* `map()` does **not** clamp — if the input is out of range, the output will be too

```c++
// Without clamping, a reading of 30 in would give a negative barFill
int barFill = map(30, 0, 24, 60, 0);  // result: -15 — bar overflows!
```

* Always clamp the input first

```c++
if (displayIn > FAR_THRESHOLD_IN) displayIn = FAR_THRESHOLD_IN;

int barFill = map((int)displayIn, 0, FAR_THRESHOLD_IN, BAR_W - 2, 0);
```

* If you skip this step the bar will visibly draw outside its outline box

## Sensor Noise

* Ultrasonic sensors occasionally return bad readings
* The sound pulse can reflect off a **wall or surface behind your hand** and come back late
* Example: hand is 10 inches away, but sensor reads 145 inches

* Two kinds of bad readings
  * `sensorTime == 0` — no echo came back at all (object too far or out of range)
  * Distance is unreasonably large — a ghost echo from somewhere else

## Rolling Average

* Instead of using a single reading each loop, we store the **last 5 readings** in an array and average them

* If one reading is bad, it only has 1/5 the effect on the displayed value

* We call this a **rolling average** (or sliding window average)
  * The window "slides" forward with each new reading
  * Old readings fall off the back; new readings come in the front

## How the Array Works

* Store readings in a fixed-size array; track where the next one goes with `readIndex`

```c++
readings[readIndex] = distanceIn;
readIndex = readIndex + 1;
if (readIndex >= NUM_READINGS) {
    readIndex = 0;              // wrap back to the start
}
```

* After storing the new reading, compute the average

```c++
float total = 0;
for (int i = 0; i < NUM_READINGS; i++) {
    total = total + readings[i];
}
return total / NUM_READINGS;
```

## Handling Bad Readings

* If `sensorTime == 0` or the distance is above `MAX_RANGE_IN`, **skip the array update**
* Return the current average anyway — the display always gets a valid number

```c++
if (sensorTime != 0) {
    // compute distance...
    if (distanceIn <= MAX_RANGE_IN) {
        readings[readIndex] = distanceIn;
        // advance readIndex...
    }
}
// always compute and return the average
```

* This eliminates the need for a special "bad reading" value like `-1`

## Lab: Parking Sensor

* Use the ultrasonic sensor and OLED to build a parking sensor display
* Download the starting code
  * Go to [https://tinyurl.com/ProjectZipGH](https://tinyurl.com/ProjectZipGH)
  * Paste the following link into the top right
    `https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_exercises/week10/ultrasonic_oled_start`

## Lab: Parking Sensor (part 1)

* Specifications
  * Display the zone label at the top of the screen (FAR / NEAR / STOP!)
  * Display the distance in inches below the label
  * Draw a bar graph outline at the bottom of the screen

## Lab: Parking Sensor (part 2)

* Specifications
  * Calculate `barFill` using `map()` so the bar grows as the hand approaches
  * Clamp `displayIn` before calling `map()` so the bar never overflows
  * Fill the bar using `oled.rectFill()`
  * Optional challenge: add a tick mark on the bar at the STOP threshold position

## Lab: Parking Sensor (part 3)

* Specifications
  * Add a rolling average using an array of 5 readings
  * Skip the array update if `sensorTime == 0` or distance exceeds `MAX_RANGE_IN`
  * Observe: how does the display behave differently with and without averaging?

## Lab Wiring Guide

```
OLED
  GND  → GND
  VDD  → 3.3V
  SDA  → SDA
  SCL  → SCL

Ultrasonic Sensor
  VCC  → VUSB (5V)
  Trig → D6
  Echo → D5
  GND  → GND
```

## References

* [SparkFun Micro OLED Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/micro-oled-breakout-hookup-guide)
* [HC-SR04 Ultrasonic Sensor Datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)

## Credits

* Images created with [Fritzing](https://fritzing.org/home/)
