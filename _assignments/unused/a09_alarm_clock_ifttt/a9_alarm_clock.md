Assignment 8 – Alarm Clock
==========================

[Submit on Brightspace](https://brightspace.usc.edu/)

Goals
-----

-   Connect speaker and play tones
-   Connect device to Particle cloud
-   Connect to IFTTT and control device

## Overview

This assignment is to create an alarm clock that has a speaker that can play a
song or a buzzer sound as well as a snooze button. The alarm set time and
whether it is enabled / disabled will be controlled from a mobile device via
IFTTT.

## Components

-   Argon
-   Breadboard
-   1 x speaker
-   1 x LED
-   2 x push buttons (plus any necessary resistors)
-   Jumper wire

## Requirements

-   Create a Fritzing breadboard prototype of your design. No sample is provided so it is up to you to layout the components
-   Once you are are finished, build the device
-   It is recommended to code the device in stages, and test at each stage

### Global variables

-   You can create other variables as needed, but these are required
-   `int melodyNotes[16]` and `int melodyNotesDuration[16]` to store the
    pattern of notes for the melodies your alarm will play

### Stage 1: Speaker and Tones

-   Connect the speaker, LED, and push buttons (push buttons discussed later)
-   Create two different “songs” for the alarm. Each should have distinct melodies (at least 16 notes). You can use the list of musical notes and frequencies (or do something different).
-   Test your device by playing the notes
-   The LED should flash when the alarm is going off

### Stage 2: Configure Alarm Settings via IFTTT

-   Create an IFTTT applet that allows a button press to enable / disable the
    alarm on the argon. This means if the alarm time arrives but the alarm
    status is disabled, then the alarm will NOT sound
    -   Hint: Using the IFTTT **Button widget** trigger
-   Create a IFTTT applet that allows you to cycle between the songs or the
    buzzer sound that will play on the argon when the alarm goes off
	-   Hint: Using the IFTTT **Button widget** trigger

### Stage 3: Set Alarm Time via IFTTT

-   Create an IFTTT applet to set a time and start an alarm on the argon.
    -   Hint: Using the IFTTT **Date & Time** trigger, you can create a
        **Particle** function action)
-   IFTTT only allows time triggers at :00, :15:, :30, and :45 minutes each
    hour. It is recommended (not required) to create another **Button widget**
    trigger that you can use for testing

### Stage 4: Configure operations two physical buttons (Stop and Snooze)

-   The logic of alarm is as follows: 
    -   If alarm is disabled
        -   Snooze button, stop button, and alarm time trigger have no effect
    -   If alarm is enabled
        -   If alarm time trigger goes off
            -   The selected song will play indefinitely until the stop button
                is pressed
            -   If the snooze button is pressed, the song will be paused for a
                5 minutes (for testing you can use a few seconds)

### Timing

* For playing melody notes, you can use `delay()` for a few milliseconds
* For managing the timing of events, however, use `millis()` instead of
  `delay()` 

## Extra Credit

-   IFTTT does not allow for arbitrary alarm times. Use the Particle console (or
    app) to set an arbitrary alarm time (e.g. 4:58 pm).

Deliverables
------------

1.	Your Workbench project with firmware source code
2.	A short video demonstrating all the functionality of your project

## Submission Instructions

*Please follow the guidelines below for full credit.*

* Navigate to your project folder.
* Include the *entire* folder in a zip file
* Rename the zip file based on naming convention
* Upload zip file to Brightspace site for our course
* Separately, upload your video Brightspace (or submit the link to a video hosted elsewhere)

**Required naming convention** (replace \# with the current assignment number)

-   **Project Name**
    -   `tac348_a#_lastname_firstname`
-   **Zip File** (include entire project folder)
    -   `tac348_a#_lastname_firstname.zip`

Grading
-------

| Item                                        | Points |
|---------------------------------------------|--------|
| Fritzing layout                             | 5      |
| Stage 1: Speaker and Tones                  | 10     |
| Stage 2: Configure Alarm Settings via IFTTT | 5      |
| Stage 3: Set Alarm Time via IFTTT           | 5      |
| Stage 4: Configure timing and buttons       | 15     |
| Total                                       | 40     |



## Recommendation: Music Notes as Constants

* You can play all tones directly as frequencies for this assignment
* However, it can be helpful to create melodies with musical notes instead of frequencies. 
* The following code file lists the musical notes as frequencies:
  [pitches.h](pitches.h) 
* Download `pitches.h` to the `src` folder for your project.
* In your main `.ino` sketch, you can then include this file and use the constants to play musical notes.
* Example

```c++
#include "pitches.h"

// example
tone(D6, NOTE_D4, 500);	//play the D note above middle C
```
