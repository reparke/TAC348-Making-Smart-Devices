---
marp: true
theme: itp
paginate: true

week: 1
category: lectures
title: Photon 2 Microcontroller


---

<!-- headingDivider: 2 -->

# Photon 2 Microcontroller

![bg opacity:.75](lecture_photon_2_microcontroller.assets/PHOTON2-EVT-ISO_1200x.webp)

## Microcontroller

* Microcontrollers (MCU) are **embedded** computers
* They are often designed for a specific purpose (e.g. microwave, RC car, TV remote)
* Microcontrollers can take input, process it, store a value, and produce output  (like on your computer)
* Unlike your computer (or even your phone), a microcontroller has very limited processing power and storage 
* Ex: The newer smartphones have 100,000 times more storage than the Photon 2

## Particle Photon 2

* We will develop projects for a microcontroller called an **Photon 2** made by **Particle**
* The Photon 2 is able to wirelessly connect to the internet and to Bluetooth 
* Particle also has a cloud communication system we will explore later in the semester

## Datasheet

* One important skill of building smart devices is learning to understand a datasheet
* A datasheet explains how a component functions, how to use it, what conditions it will operate, etc.
* Don't worry about understanding everything in a datasheet, but learn to pull out key information

- [Photon 2 Datasheet](https://docs.particle.io/reference/datasheets/wi-fi/photon-2-datasheet/)

## Work in groups and answer the following

1. What voltage does the Photon 2 operate at?
2. Which IC (integrated circuit) is the "main" processor?
3. What is the difference between pins `3v3` and `VUSB`?
4. How many digital input pins are there? 
5. How many analog output pins are there?
6. How many ground pins are there?
7. What is the voltage that the input pins can handle?
8. Can we power the Photon 2 with battery?

<!-- recommended supply voltage: 3.3v, Supply Input Voltage: up to 6.2v -->

<!-- main: realtek RTL8721DM  -->

<!-- 3v3 is always 3.3v; VUSB is 5v when connected to USB-->

<!-- 20 digital GPIO; 6 analog IN; 0 analog out; 1 ground pin -->

<!-- Input high voltage: GPIO can operate at 3.3V max so be caution with higher voltage devices -->

<!-- show other communication pins -->       

## Datasheet 


- [Photon 2 Pinouts](https://docs.particle.io/assets/images/photon2-rendering.png)

- [Photon 2 Datasheet](https://docs.particle.io/reference/datasheets/wi-fi/photon-2-datasheet/)

<!-- recommended supply voltage: 3.3v, Supply Input Voltage: up to 6.2v -->

<!-- main: realtek RTL8721DM  -->

<!-- 3v3 is always 3.3v; VUSB is 5v when connected to USB-->

<!-- 20 digital GPIO; 6 analog IN; 0 analog out; 1 ground pin -->

<!-- Input high voltage: GPIO can operate at 3.3V max so be caution with higher voltage devices -->

<!-- show other communication pins -->        



## Structure of Photon 2 Programs

* We will use Particle Workbench as our IDE
* We will write software code that runs on the Photon 2
* Programs that run on microcontrollers are called **firmware** 

## Important Note

* Your Photon 2 folder name cannot contain any spaces at all
  - `C:\Users\Rob\TAC-348\Projects` is ok
  - `c:\Users\Rob Parke\TAC 348\Cool Projects` is not

## Key features

* Photon 2 programs are written in C++ *(please see review link on course website for C++)*
* Every Photon 2 program **must** have these two functions *(you can other ones too)*
  - `void setup()`
  - `void loop()`
* In addition, most programs will also have
  - global variable declarations
  - library includes

## Example program

```c++
#include "OLED_screen.h"	//library

const int MAX_PRESSES = 4;	//globcal constant
int numPresses = 0;			//global variable

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
```

*Note: There will be other default code at the top of the file when you create a new project. This code is needed to configure the Photon, but we can mostly ignore it*

## Libraries

```c++
#include "OLED_screen.h"
```

* Similar to `import`
* Allows us to access additional code and functions
* We will use this to communicate with certain devices like LCD screens
* Notice the `#`

## Variable Declaration

```c++
const int MAX_PRESSES = 4;	//globcal constant
int numPresses = 0;			//global variable
```

* Typically, many of our variables will be global (declared outside a function in the global namespace)
* In C++, every variable must *explicitly* declare it's

## `setup()` Function

```c++
void setup() {
  // put your setup code here, to run once:
}
```

* The `setup()` function will ***only run once***
  - Runs after each powerup or reset the Photon 2
* Use it to initialize variables, pin modes, start using libraries, etc.

## `loop()` Function

```c++
void loop() {
  // put your main code here, to run repeatedly:
}
```

* After `setup()` is called once, the`loop()` function is called endlessly 
  - Basically an infinite loop
* Use it for the main functionality of your program