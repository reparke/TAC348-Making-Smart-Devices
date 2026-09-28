---
marp: true
theme: tac

week: 16
category: lectures
title: Cloud Communication - Calling Functions
---

<!-- headingDivider: 2 -->

# Cloud Communication
<img src="lecture_particle_cloud_functions.assets/iot_cloud.jpg" alt="iot_cloud" style="width:800px;" />



## Review: Particle Cloud Features

**Does**

* Update device code and firmware
* Receive status messages 

* Read the values of variables
* Control device / execute function calls

## Review: Particle Cloud Features

**Does NOT**

* Store data from device 
* Run analytics
* Manage device with publicly-accessible web/mobile 

## Key operations in Particle Cloud

* Publishing (events part 1)
* Subscribing (events part 2)
* Accessing data (cloud variables)
* **Control device (cloud functions)**

## Cloud Functions

* Register / expose a C++ function in your Photon 2 code so it can be called online
* Up to 15 functions may be registered

## Cloud Function Process

1. Create a regular C++ function to perform a task
   * Function must take **exactly one** parameter of type `String` 
2. Call `Particle.function` within `setup()` to register the function

## Cloud Function Syntax

```c++
Particle.function(<<REGISTERED_NAME>>, <<ACTUAL_FUNCTION_NAME>>);
```

Example

```c++
int ledStatus(String command) {...}	//actual C++ function
    
void setup() {
  Particle.function("ledStatus", ledStatus); //register func
```

Function must return an `int` (typically -1 for fail)

## Calling Cloud Functions - [Particle Console](https://console.particle.io)

<img src="lecture_particle_cloud_functions.assets/1569448280222.png" alt="1569447605240" style="width:1200px;" />

## Calling Cloud Functions - App

<img src="lecture_particle_cloud_functions.assets/app_functions.jpg" alt="1569447605240" style="width:800px;" />

## Calling Cloud Functions - REST

* Functions can be called by any device or service via REST

* REST is very common protocol for sharing data across the internet

* REST call syntax

  `POST /v1/devices/{DEVICE_ID}/{FUNCTION}`

## Lab Wiring

<img src="lecture_particle_cloud_functions.assets/Screenshot 2024-07-28 at 5.29.47 PM.png" alt="Screenshot 2024-07-28 at 5.29.47 PM" style="width:800px;" />

## Lab

* Review Cloud Variables by sending current temperature as a Cloud Variable
* Connect at RGB LED
* Create a cloud function called `int changeLEDColor(String color)`
  * Function should take a string and then change the color (*red, green, blue, cyan, magenta, yellow, white, off, random*)
* Connect `changeLEDColor` to the cloud via `Particle.function`
* Control light color from your phone

## Quick Note: C++ and Strings

- Similar to Python, we **can** use `==` to compare the *contents* of two Strings

```c++
String str1 = "cat";
String str2 = "gato";
if (str1 == str2) {
 
```

- We can also compare strings by their capitalization using `equalsIgnoreCase`

```c++
String str1 = "cat";
String str2 = "CaT";
if (str1.equalsIgnoreCase(str2)) {
// statement will be true

```

  

## Documentation

* [Particle Cloud API](https://docs.particle.io/reference/device-os/firmware/#cloud-functions)
* [Publishing Events](https://docs.particle.io/reference/device-os/firmware/#particle-publish-)
* [Cloud Variables](https://docs.particle.io/reference/device-os/firmware/#particle-variable-)
* [Cloud Functions](https://docs.particle.io/reference/device-os/firmware/#particle-function-)
* [Subscribing to Events](https://docs.particle.io/reference/device-os/firmware/#particle-subscribe-)
