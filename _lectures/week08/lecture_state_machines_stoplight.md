---
marp: true
theme: itp

week: 8
category: lectures
title: State Machines Part 2 - Stoplight Example

---
<!-- headingDivider: 2 -->

# State Machines
## In class Exercise - Stoplight and Pedestrian Signal

<img src="lecture_state_machines_stoplight.assets/stoplight.jpg" alt="stoplight" style="height:500px;" /> <img src="lecture_state_machines_stoplight.assets/ped_signal.jpg" alt="ped_signal" style="width:400px;" />

## In class Lab - Stoplight and Pedestrian Signal

* We are going to build a stoplight and pedestrian signal for a intersection.
* Car traffic goes North-South.
* Pedstrian traffic goes East-West
* Green lights, red lights, and the walk signal will stay on for 5 sec (`LONG_LIGHT_DURATION`)
* Yellow lights and the don't walk signal will stay on for 2 sec (`SHORT_LIGHT_DURATION`)
* Here is how this type of intersection works

## 

![bg contain](lecture_state_machines_stoplight.assets/traffic_go.png)
## 

![bg contain](lecture_state_machines_stoplight.assets/traffic_slow.png)

## 

![bg contain](lecture_state_machines_stoplight.assets/ped_walk.png)
## 

![bg contain](lecture_state_machines_stoplight.assets/ped_dont_walk.png)

## 



## In class Exercise - Stoplight and Pedestrian Signal


* Download starting code
  * Go to [https://bit.ly/ProjectZip](https://bit.ly/ProjectZip)
  * Paste the following link into the top right
  
  `https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_exercises/week07/stop_light_rgb_leds_oled_start`

* Wire device as shown below

## Wiring Diagram

<img src="lecture_state_machines_stoplight.assets/Screenshot 2024-06-19 at 12.07.42 PM.png" alt="Screenshot 2024-06-19 at 12.07.42 PM" />

## Components
* 1 RGB LEDs
* MicroOLED
* 3 x 330 Ohm resistors



## Wiring Pin Guide

| RGB LED               | Photon 2 Pins |
| ---------------------------- | ---- |
| NorthSouth RGB LED - Red | A2 |
| NorthSouth RGB LED - Green | A5    |
| NorthSouth RGB LED - Blue | D15 (MO) |

| MicroOLED (Qwiic cable) | Photon 2 Pins |
| ----------------------- | ------------- |
| GND                     | GND           |
| 3V3                     | 3V3           |
| SDA (Blue)              | SDA           |
| SCL (Yellow)            | SCL           |



## Lab Stages

1. Create cycle with only traffic (North-South) stop lights

2. Add Pedestrian Walk / Don't Walk (East-West) message to OLED 

3. Make Don't Walk light blink when it is on (if time)

   

* We will work through stage 1 together


## General Approach

* We will need to create a way to represent the states using `enum`
* We will need to track state transitions with **variables** for state
* We will need to control timing with `millis()`

* What does `loop()` do
  * calculate new state
  * output traffic signal LEDs based on state
  * independently flash walk signal *(later)*

## Credits

* [Bill Siever](http://siever.info) - [CS132 FSM](http://siever.info/cse132/guides/intro-to-FSMs.html)  (Washington University at St. Louis) 
* [Bill Siever](http://siever.info) - [CS132 Delta Timing](http://siever.info/cse132/weeks/3/)  (Washington University at St. Louis) 
* [USC EE109 State Machines](http://bits.usc.edu/files/ee109/)
* Photo by Laurie Parke
* Photo by [Michael Olsen](https://unsplash.com/@mganeolsen)</a> on [Unsplash](https://unsplash.com/)
* Photo by [Free To Use Sounds](https://unsplash.com/@freetousesoundscom?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText) on [Unsplash](https://unsplash.com/?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText)
* Photo by [NON](https://unsplash.com/@non_creation?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText) on [Unsplash](https://unsplash.com/?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText)