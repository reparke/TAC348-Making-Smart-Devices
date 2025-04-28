---
marp: false
theme: itp

week: 15
category: lectures
title: Open PIR (Passive Infrared Sensor)
---

<!-- headingDivider: 2 -->

# Open PIR - Passive Infrared Sensor

![13968-01](lecture_open_pir.assets/13968-01.jpg)  



## PIR 

* Human or animals will emit heat (as infrared radiation)
* Senses infrared waves to detect motion
* Uses
  * Alarms
  * Motion sensing cameras / lights
* Not a distance sensor

## PIR Specifications

* Distance range: up to 16 feet
* Detection range: ~110 degrees x 70 degrees
* Specifications vary by device and lens

## Components

* Main sensor is the small metal disc which detection infrared radiation

<img src="lecture_open_pir.assets/image-20240422104044162.png" alt="image-20240422104044162" width=300px/>

 ## Components
  * Clear / white lenses acts to focus a wider area of radiation onto the sensor to increase range 

<img src="lecture_open_pir.assets/13968-04.jpg" alt="13968-04" width=300px />

## Operation (Sparkfun PIR)

* Requires 1-2 sec delay in `setup()` to get initial reading from room
* Digital output from `OUT` pin
* `HIGH` when no movement detected
* `LOW` when movement detected
* Sensitive adjustment (screwdriver)
* Time adjustment (screwdriver)
* Single / dual swtich

## Sensitivity Adjustment (SEN) 

<img src="lecture_open_pir.assets/openpir_pots.png" alt="openpir_pots" style="zoom:50%;" />

* Sensitivity (potentiometer): how much motion triggers alarm
* Adjust the **view distance** of the OpenPIR
* Clockwise turn increase the distance the sensor sees
* you turn this trimpot, the further  your sensor should be able to see. When you receive the board, the  trimpot will be centered, and the sensor will react to a person moving  about in the 6 to 8 foot (2 to 2.5m) range. At the maximum sensitivity,  the sensor will detect a person walking by at about 16 feet (5m).Other PIR sensors have different configurable options

## Time Adjustment (OSC) 

<img src="lecture_open_pir.assets/openpir_pots.png" alt="openpir_pots" style="zoom:50%;" />

* Time adjust (potentiometer): how long after motion stops does signal remain active
* Adjust the length of time the output remains HIGH. This trimpot is used to adjust the oscillator  frequency of the NCS36000. 
* Clockwise increases the length of time OUT remains high
* Time range: 400 ms to 7.5 s
* Note this also controls how long the sensor stays in start up mode / blinking LED (clockwise is longer, counter clockwise is shorter)

## Retriggering

<img src="lecture_open_pir.assets/openpir_switch_1.png" alt="openpir_switch_1" style="zoom:50%;" />

* Retriggering (switch / jumper): controls if alarm stays active for the same movement
* Controls if alarm stays active for the same movement
* Single-pulse mode can be used to detect an object entering *or* exiting the PIR's field-of-view
* Dual-pulse detection can be used to detect an object entering *and* leaving the view area.

## Wiring

| Open PIR (Sparkfun) | Photon 2                  |
| ------------------- | ------------------------- |
| VCC                 | 3.3v                      |
| GND                 | GND                       |
| OUT                 | Any digital pin           |
| A                   | (Optional) Any analog pin |

*Note: The wire color and pin order is specific to the [Sparkfun OpenPIR](https://www.sparkfun.com/products/13968) sensor and not all PIR sensor*s

## Wiring

<img src="lecture_open_pir.assets/open_pir_sparkfun_sleep_button_bb.png" alt="Screenshot 2024-06-29 at 11.44.31 PM" style="width:800px;" />

*Note: button is not required*

## Exercise

- Part 1: Connect sensor; turn on on-board LED when motion is detected and turn off when motion stops
- Part 2: Adjust the potentiometers to experiment with the view distance and and hold length

## Credit

* [Sparkfun](https://www.sparkfun.com/products/13968)
* Diagrams created with [Frizting](https://fritzing.org)













