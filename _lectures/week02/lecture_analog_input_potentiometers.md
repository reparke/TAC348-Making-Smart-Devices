---
marp: false
theme: tac

week: 2
category: lectures
title: Analog Input with Potentiometers

---

<!-- headingDivider: 2 -->

# Analog Input

## Plan

* Analog vs. digital
* Potentiometer
* Voltage dividers
* Reading analog input




## Analog vs. Digital
<img src="lecture_analog_input_potentiometers.assets/analog-clock.png" alt="analog clock" style="width:500px" /> <img src="lecture_analog_input_potentiometers.assets/clock-997589_960_720.jpg" alt="digital clock" style="width:500px" />


## Analog vs. Digital

| Analog                                                       | Digital                                                      |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| <img src="lecture_analog_input_potentiometers.assets/analog-clock.png" alt="analog clock" style="width:300px" /> | <img src="lecture_analog_input_potentiometers.assets/clock-997589_960_720.jpg" alt="digital clock" style="width:300px" /> |
| **infinite** variations / states                             | **discrete** (or **finite**) states                          |



## Potentiometer (Pot)

<img src="lecture_analog_input_potentiometers.assets/515deb26ce395f3959000000.png" style="width:500px" alt="potentiometers" />

* Variable resistor with 3 pins
  - power, ground, **wiper**

## Potentiometer (Pot)
<img src="assets/1565313560201.png" style="width:300px" alt="potentiometer schematic symbo" />  

* **Wiper** pin connects to circuit
  - As wiper moves, resistance varies from 0 Ohms to max (e.g. our kit has 10K Ohms pots)


## Where do we find pots?

## Where do we find pots?

<img src="assets/potentiometer-482082_960_720.jpg" style="width:550px" />

* Also car stereo knobs, dimming light switches, etc.


## How a Potentiometer Works

<img src="lecture_analog_input_potentiometers.assets/511ac8f5ce395f5846000000.png" alt="Schematic symbol for a potentiometer" style="width:600px" />


## How a Potentiometer Works

<img src="lecture_analog_input_potentiometers.assets/511ac8f5ce395f5846000000.png" alt="Schematic symbol for a potentiometer" style="width:200px" />

* **Vout** is the wiper (middle pin; connects to Photon 2 analog input)
* Inside the potentiometer is a resistor
* As the knob moves, the wiper divides the resistor, and the ratio of resistance between ***Vin-and-Wiper*** and ***Wiper-and-Gnd*** varies
* This is called a **variable voltage divider** *(more on this later)* 


## Question

<img src="lecture_analog_input_potentiometers.assets/511ac8f5ce395f5846000000.png" alt="Schematic symbol for a potentiometer" style="width:400px" />

* With a 10K Ohm pot, if the wiper is exactly halfway, what is the resistance between **Vout** and **Gnd**?

<!-- middle: 5K Ohms; 
top: 10K ohms because it is the R between Vout and Gnd
-->

## Voltage Dividers

<img src="lecture_analog_input_potentiometers.assets/511ac8f5ce395f5846000000.png" alt="Schematic symbol for a potentiometer" style="width:400px" />

* Photon 2 input pins can measure **voltage**, not **resistance**
* By connecting **Vin** (3.3v), **Gnd**, and **Vout** (wiper), we can now vary the **voltage** difference ***Vin-and-Wiper*** and ***Wiper-and-Gnd***

## Voltage Dividers

<img src="lecture_analog_input_potentiometers.assets/511ac8f5ce395f5846000000.png" alt="Schematic symbol for a potentiometer" style="width:400px" />


* If the wiper is exactly halfway, what is the voltage between **Vout** and **Gnd**?
* If the wiper is all the way to the top, what is the voltage between **Vout** and **Gnd**?

<!--  middle: 1.67v because the wiper is "seeing" halfway through the drop of 3.3v across the entire resistor; 
bottom: 0v because Vout and Gnd are directly connected;
top: 3.3v because vout is connected to 3.3v, which is being dropped over 10K resisor;-->

## Voltage Divider

* As those resistances changes, so does the **voltage** difference between ***Vin-and-Vout*** and ***Vout-and-Gnd***
* This is known as a **voltage divider**
  ![bg right:50% fit](lecture_analog_input_potentiometers.assets/photoresistor_wiper_equals_vin.png)  
  ![bg fit](lecture_analog_input_potentiometers.assets/photoresistor_wiper_equals_zero.png)
  <!-- 
  <img src="lecture_photoresistor.assets/511ac8f5ce395f5846000000.png" alt="Schematic symbol for a potentiometer" style="width:350px" /> -->


## Setting up Analog Input

Syntax

```c++
const int PIN_POT = A0;		//input pin
int potValue = 0;			//value from read

void setup() {
    pinMode(PIN_POT, INPUT);
}

```

* Pins A0-A5 are analog input
* *Technically, analog pins are **input by default** but I like to do this for clarity and consistency*

## Reading Analog Input

Syntax

```c++
void loop() {
    potValue = analogRead(PIN_POT);
}
```



## Wiring Diagram 

<img src="lecture_analog_input_potentiometers.assets/wiring.png" style="zoom:25%;" />

* Using **Vin=3.3v** and a 10k potentiometer, what do you expect for the range of values of **potValue**?

<!-- we would expect a range of 0-3.3v, but we will see with
ADC that that is not what we get
-->

## Credit

- [Pixabay](https://pixabay.com/photos/potentiometer-guitar-electric-guitar-482082/)
- [Pixabay](https://pixabay.com/vectors/variable-resistance-resistors-36565/)
- [Sparkfun](https://learn.sparkfun.com/tutorials/resistors#types-of-resistors)
- [Sparkfun](https://learn.sparkfun.com/tutorials/voltage-dividers)
- Diagrams created with [Fritzing](https://fritzing.org)