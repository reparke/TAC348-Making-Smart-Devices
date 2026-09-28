---
marp: true
theme: tac

week: 3
category: lectures
title: Digital Input

---

<!-- headingDivider: 2 -->

# Digital Input

# Review

## Analog vs. Digital

  - Analog: **infinite** variations / states
  - Digital: **discrete** (or **finite**) states


## Digital

* Instead of being infinite, digital signals are **discrete** (or **finite**)

* Think binary: the switch is either **on** or **off** (not "a little bit on")

* Digital values often have more than just two states
  - Still have a fixed number of possible values (e.g. integer values 0-255)

## What are examples of digital output?

## Digital Output

```c++
void setup() {
    pinMode(SOME_PIN, OUTPUT);
}
void loop() { 
    digitalWrite(SOME_PIN, HIGH); //or LOW
```

* Most pins on the Photon 2 can be configured to SEND output (e.g. to turn on a light) or to RECEIVE input (e.g. a button press)

* **HIGH** / true is **5V** (pin VUSB) or **3.3V** (pin 3.3v)
* **LOW** / false is **0V** (ground)

## What about digital input?

* What are examples of digital inputs?


## Digital Input

* Pins D2-D8 can be used for digital input *(other pins can also be used)*
* Photon 2 will "read" the voltage on a pin and return HIGH (3.3V) or LOW (0V)
* **Never exceed 3.3V on input**
  - Be careful of other components that operate at 5V

## Reading Digital Input with `digitalRead` 

Syntax

```c++
int value = digitalRead(PIN_NUMBER);
//value is either HIGH or LOW (HIGH and LOW are defined as constants)
```
