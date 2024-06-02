---
marp: true
theme: itp

week: 4
category: lectures
title: Cloud Communication - Overview
---

<!-- headingDivider: 2 -->

# Cloud Communication
<img src="lecture_particle_cloud_overview.assets/iot_cloud.jpg" alt="iot_cloud" style="width:800px;" />

## Review: What is the Cloud?

<!-- basically servers connected to the internet all around the world; not one single computer, but many different machines, services, and companies -->

## Internet of Things

- Things
  * "smart" devices that are programmed interact with environment 
- Internet
  * connect to the internet to send and receive data

## IoT Cloud Platforms

* Various services that allow you to enhance your device with internet capability

## Examples of IoT Cloud Services

* Update device code and firmware
* Receive status messages (like we do with Serial monitor)
* Read the values of variables
* Control device / execute function calls
* Store data from device (e.g. the hourly temperature for the past 6 months)
* Run analytics (e.g. how often does one of my 4,000 device fail)
* Manage device with publicly-accessible web/mobile 

## IoT Cloud Platform Companies

* Very competitive and growth space
* Established firms: [Google Cloud IoT](https://cloud.google.com/solutions/iot), [Microsoft Azure IoT](https://azure.microsoft.com/en-us/overview/iot/), [Amazon Web Services](https://aws.amazon.com/iot/)
* Startups: [Particle](https://particle.io), [Losant](https://www.losant.com/), [Ubidots](https://ubidots.com/), [Initial State](https://www.initialstate.com/), [Tinamous](https://www.tinamous.com/)
* Various: [Thingspeak](https://thingspeak.com/) (supports MATLAB), [IFTTT](https://www.ifttt.com)

## Particle Cloud Features

* Update device code and firmware
* Receive status messages (like we do with Serial monitor)
* Read the values of variables
* Control device / execute function calls

## Particle Cloud Does NOT

* Store data from device 
  * Ex. the hourly temperature for the past 6 months)
* Run analytics
  * Ex. how often does one of my 4,000 device fail)
* Manage device with publicly-accessible web/mobile 

## Particle Cloud

* Photon 2 has built in support for connecting to Particle Cloud
* Particle Cloud is essentially free (very generous free tier)
* Basically acts as a real-time communication system
  * i.e. the current temperature, but not temperature from last Tuesday
* For data storage and analysis, we will use a different service later in the course

## Quick Note

* All the features we will discuss are not unique to Particle Cloud
* It is possible to read variables and execute functions from most companies' platforms
* The syntax and mechanisms will vary from Particle Cloud, but the concepts are transferable

## Key operations in Particle Cloud

* Publishing (events part 1)
* Subscribing (events part 2)
* Accessing data (cloud variables)
* Control device (cloud functions)



## Documentation

* [Particle Cloud API](https://docs.particle.io/reference/device-os/firmware/#cloud-functions)
* [Publishing Events](https://docs.particle.io/reference/device-os/firmware/#particle-publish-)
* [Cloud Variables](https://docs.particle.io/reference/device-os/firmware/#particle-variable-)
* [Cloud Functions](https://docs.particle.io/reference/device-os/firmware/#particle-function-)
* [Subscribing to Events](https://docs.particle.io/reference/device-os/firmware/#particle-subscribe-)
