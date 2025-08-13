Assignment 5 – Reaction Timer Game
==================================

*[Submit on Brightspace](https://brightspace.usc.edu)*


Goals
-----

-   Control RGB LEDs

-   Use push button for digital input

-   Process timed events

## Overview

<img src="a5_reaction_timer.assets/IMG_1609-2.jpg" style="width=700px;" />

This assignment is to create a simple reaction timer game. Two players will each
have two buttons (“red” and “blue”). A RGB LED will flash white three times, and
then it will flash either red or blue. The player that presses their correct
button the faster will win that round. The cumulative score will be displayed on
the serial monitor.

The exact layout of this project is left unspecified so you can come up with
your own design and modifications

## Components

-   Argon

-   Breadboard

-   1 x RGB LED (and any associated resistors)

-   4 x push button (and any associated resistors)

-   Jumper wire 

## Requirements

-   Create a Fritzing breadboard prototype layout of your design

-   Once you’re satisfied with the design, build the device and create firmware
-   General game setup
    -   Two players each control two push buttons

    -   Each button represents either “red” or “blue”

    -   Between the two rows of buttons is a RGB LED
-   Algorithm for each round

    -   RGB LED will flash white three times. Use a delay in between each flash
        with a random value

    -   RGB LED will then flash either red or blue (randomly chosen)

    -   Argon will wait for either player 1 or player 2 to press the correct
        button

    -   The first player to press the correct button scores **+100** points;
        incorrect presses result in **-100** point deduction

    -   After each round, the winner of the round is displayed on the serial
        monitor. The cumulative scores of both players are also displayed on the
        serial monitor.

    -   Press reset on the argon to reset the game

**Naming convention **

*(replace \# with the current assignment number)*

-   **Project Name**: `tac348_a#_lastname_firstname`

-   **Zip File** (project folder): `tac348_a#_lastname_firstname.zip`

## Video Submission Checklist

*To receive credit, your submitted video must clearly demonstrate the following:*

- [ ] RGB LED flash white three times with delay
- [ ] RGB LED changes to red or blue
- [ ] Player 1 guesses correctly and displays on serial monitor
- [ ] Player 1 guesses incorrectly and displays on serial monitor
- [ ] Player 2 guesses correctly and displays on serial monitor
- [ ] Player 2 guesses incorrectly and displays on serial monitor

Deliverables
------------

*[Submit on Brightspace](https://brightspace.usc.edu)*


1. Fritzing layout file

2. A compressed file containing your project. Follow the guidelines for full
   credit.

   *Here are the instructions for submission*


   - Navigate to your project folder.

   - Include the *entire* folder in a zip file

   - Rename the zip file based on naming convention

   - Upload zip file to Brightspace site for our course

3. A photograph of your device connected to USB with the blue light on.

4. A video demonstrating your project functioning (either upload this to separate from the zip file, or upload to YouTube / Google Drive / Dropbox and provide the link in your submission). 

Grading
-------

| Item                                        | Points |
| ------------------------------------------- | ------ |
| **Fritzing layout**                         | 5      |
| **Components**                              |        |
| RGB LED configuration                       | 5      |
| Button configuration                        | 5      |
| **Game logic**                              |        |
| RGB LED flashes                             | 2      |
| RGB LED randomly chooses color              | 2      |
| First correct answer gives +100 points      | 4      |
| Incorrect answer gives -100 points          | 4      |
| Serial monitor displays cumulative results  | 4      |
| Reset button clears results and resets game | 4      |
|                                             |        |
| Total                                       | 35     |
