---
marp: true
theme: tac

week: 16
category: lectures
title: IFTTT
---

<!-- headingDivider: 2 -->

# IFTTT

### If **This**, Then **That**

## IFTTT: If This, Then That

* Free platform for interconnecting various internet service
* Create very simple recipes (called applets) using conditional logic such as
  * "If I am within 5 miles from home, then start the A/C"
  * "If I take a photo, then automatically save it to my Dropbox"
  * "If I publish a temperature with the Photon 2, then add the time and temperature to a Google spreadsheet"

## Usefulness of IFTTT

* IFTTT is a free consumer service, but also has a business service
* Consider it as an extension of prototyping
  * Great to explore creative solutions
  * Replace with more secure, robust tool in production
* Later in the semester we will look at a more enterprise platform

## Key Terms

* Trigger: **THIS**
  * The event that causes IFTTT to do something
* Action: **THAT**
  * The resulting task that IFTTT performs
* Recipe / Applet: 
  * The combined **THIS** + **THAT**
* Ingredients: 
  * Data that is passed from Trigger. This will be information from Particle events that we publish

## Using Particle as Trigger (THIS)

* Event is published (uses **publish**)
* Variable state changes (uses **variable**)
* Monitor function result (uses **function**)
* Check device status

## Using Particle as Action (THAT)

* Publish an event (need to **subscribe**)
* Call a function (uses **function**)

## Lab

<img src="lecture_ifttt.assets/Screenshot 2024-07-28 at 5.20.52 PM.png" alt="Screenshot 2024-07-28 at 5.20.52 PM" style="width:500px;"/>

## Documentation

* [Particle IFTTT Tutorial](https://docs.particle.io/tutorials/integrations/ifttt/#introduction)
