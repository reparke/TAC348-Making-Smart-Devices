---
marp: true
theme: tac

week: 3
category: lectures
title: Switches

---

<!-- headingDivider: 2 -->

# Switches

<img src="lecture_switches.assets/image-20200710132427002.png" alt="image-20200710132427002" style="width:600px;" />

## Switches

* Similar to pushbuttons, switches open or close a circuit
* Pushbuttons are **momentary switches** because they close (complete) a circuit only while the button is pressed
* We are going to look at **maintained switches** that continue to close or open a circuit indefinitely
* We will typically just call these components "switches"

## Terminology

* **Poles**: The number of distinct circuits that can be controlled by using the switch
  * e.g. "single pole" (SP) or "double pole" (DP)
* **Throws:** The number of positions the switch allows the circuit to connect to
  * e.g. "single throw" (ST) or "double throw" (DT)

## Poles and Throws Explained

**SPST - Single Pole, Single Throw**

<img src="lecture_switches.assets/517ed955ce395f471d000000.png" style="zoom:50%;" />

* There is one single circuit (**single pole**)
* The input *1P* is either connected to output *1T* or to nothing (**single throw**)
* Notice there there are two connectors on the switch (input and output)

## Poles and Throws Explained

**SPDT - Single Pole, Double Throw** (This is what you have in your kit)

<img src="lecture_switches.assets/517edaface395f581d000001.png" alt="https://cdn.sparkfun.com/assets/2/7/c/c/c/517edaface395f581d000001.png" style="width:500px;" />

* There is one single circuit (**single pole**)
* The input (1P) is either connected to output *1T* or output *2T* (**double throw**)
* Notice there there are three connectors on the switch (1 input and 2 output)

## Poles and Throws Explained

**DPDT - Double Pole, Double Throw** 

<img src="lecture_switches.assets/517edbabce395fd51d000000.png" alt="https://cdn.sparkfun.com/assets/6/e/d/9/0/517edbabce395fd51d000000.png" style="widht:500px" />

* There are two circuit (**double pole**)
* Input 1P is either connected to output *1T* or output *2T* (**double throw**)
* Input 2P is either connected to output *1T* or output *2T* (**double throw**)
* Notice there there are six connectors on the switch (2 input and 4 output)

## SPDT - Single Pole, Double Throw

<img src="lecture_switches.assets/image-20200711010114011.png" alt="image-20200711010114011" style="width:300px;" />

<img src="lecture_switches.assets/image-20200711010308308.png" alt="image-20200711010308308" style="width:300px;" />

## Exercise

1. Connect switch to 3.3v, `A5`, and gnd
2. Use serial monitor to read and display switch value

## Credit

- [Sparkfun](https://learn.sparkfun.com/tutorials/switch-basics/all) has some great illustrations on this for a deep dive into switches
- Images created with [Fritzing](https://fritzing.org/home/)

