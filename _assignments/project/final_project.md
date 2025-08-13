---
week: 11
number: 12
category: assignments
title: Project
date_due: Proposal due Sun Nov 9 @ 11:59 pm; Milestone due Sun Sun Nov 30 @ 11:59 pm; Finished device and presentation during Final Period (in person) Fri Dec 12 for MW class and Tue Dec 18 for TTh class
---

Final Project
=============

[Submit on Brightspace](https://brightspace.usc.edu/)

Goals
-----

-   Create a connected device prototype of your own design
-   Device should demonstrate mastery of the concepts discussed in the course
-   Device should include elements not explicitly covered in class

Overview
--------

The project is to create a prototype of a connected device. The final submission
does not need to be “ready for manufacturing” but it must work and demonstrate
the key functioning elements. Here is a [partial list of components and services](sample_components) covered in class.

## Project Requirements

* Be designed and built by you solely. Inspiration may be taken from online and other sources, but sources must be cited and final project must be substantially different.
* Use at least four major components. Major component include
  * Sensor
  * Servo / Motors
  * Components not covered in class will be probably count but the need to be approved
  * LEDs and buttons count but together only count as one component
  * A switch connected the EN pin does not count as  component

* Use at least two component to interact with environment (e.g. switch, button, etc.)
* Use cloud / internet connectivity in a meaningful way
* Must send data to a cloud system and display a dashboard 
  * Examples of acceptable tools
    * [Initial State](https://www.initialstate.com/)
    * [Losant](https://www.losant.com/)
    * [ThingSpeak](https://thingspeak.com/)
  * Blynk does not meet the dashboard requirement
* Must have interface app (web or mobile) and be able to receive feedback from app to produce effects in the physical world (i.e. control device remotely)
  -   Examples of acceptable tools
      -   Blynk cloud app
      -   [Intial State](https://www.initialstate.com/) (must use [input controls](https://www.initialstate.com/blog/input-controls/) not just dashboard tools)
      -   [Losant](https://www.losant.com/)
      -   If using Bluetooth, the [Bluefruit](https://learn.adafruit.com/bluefruit-le-connect) app will be considered as long as it is substantially different from car assignment
  -   Not acceptable 
      -   Particle app 
* Comment your code and follow consistent coding convention
* Developer and user documentation (see below)
* Your project has to compile and run *(projects that fail to run will receive a 50% penalty)*
* No late submission will be accepted
* Note: in the coming weeks we will discuss the following components in case
  you want to include them in your project
  * Heart rate sensors
  * Digital temperature and humidity sensor
  * Ultrasonic distance sensor
  * Accelerometer

### Possible Project Ideas

* Head-mounted collision-detection and navigation wearable
* Earthquake monitor
* Retrofitted children’s toy
* Home monitoring station
* [Sample past projects](https://robparke.com/tag/itp348_projects/)

Deliverables
------------

### Proposal Deliverables

* Write a proposal document with following details:
  * Describe the problem or need you have identified, why you believe it is
    necessary to address, and how your device would address this need.
  * Describe the target audience
  * List the key features, sensors, interaction patterns (e.g. how will
    users interact with the device), and internet / cloud platforms
  * Rough budget for how much it would cost to build your device. You should
    include items in your kit as well as items not in your kit (e.g.
    building supplies, other sensors, etc.)
* *Note: You can modify your project later but you must submit a revised proposal for approval. Failure to do will lose 10%*

* [Sample proposal](https://reparke.github.io/ITP348-Physical-Computing/assignments/project/samples/project_proposal_sample.pdf)

### Project Milestone Deliverables

* Complete Fritzing diagram

### Project - Final Deliverables 

**The remaining items are to be submitted on Brightspace**

-   Workbench project with firmware code
-   Video of functioning device
-   User interface web app (submit link on Brightspace)
-   Developer documentation
    -   Assume a future ITP348 student is taking the course and told to make a
        specific change to your project (add a feature, fix an error, etc.).
    -   Provide instructions how to setup your device and then explain key
            elements (include any other helpful documentation like sequence
            diagrams, Fritzing diagrams, etc.)
    -   Consider the following:
        -   What would they need to know to setup your project and get it running?
        -   What would they need to know to modify it? (Assume that they don’t want to read through all your code - they want some sort of a quick start guide that will help them identify where they should start looking/working first)    
        -   Give a general overview of all aspects of your project with
                sufficient detail for them to know where to look to make
                modifications.
    -   [Sample developer documentation](https://reparke.github.io/ITP348-Physical-Computing/assignments/project/samples/project_developer_guide_sample.pdf)
-   User documentation
    -   Assume a non-technical person would like to use your device. What do
        they need to know to get started and to use specific features? (You can
        omit initial setup)
    -   [Sample user documentation](https://reparke.github.io/ITP348-Physical-Computing/assignments/project/samples/project_user_guide_sample.pdf)

### Project - Final Presentation (10 min)

-   This is a required in-person demonstration of your functioning device scheduled during our final exam time
-   You may create a short video introduction highlighting your project (***please keep your video under 2 minutes***)
-   The presentation should address the following:
    -   What your device does / what problems are you solving
    -   How your device satisfies each requirement in the grading rubric 
        -   Four key components
        -   Remote control / Blynk / Bluetooth functionality
        -   Dashboard
    -   What was the most challenging or interesting aspect of the project
-   You will then demonstrate all the functionality of your device. If it isn't feasible to show it live, you can pre-record this part

## Submission Instructions

* Submit all documents via Brightspace
* Bring device to in-person project demonstration

Grading
-------

| Item                                                      | Points |
| --------------------------------------------------------- | ------ |
| **Device proposal**                                       |        |
| Motivation / Need / Audience                              | **4**  |
| Features                                                  | **4**  |
| Budget                                                    | **4**  |
|                                                           |        |
| **Project Milestone / Schematic**                         | **10** |
|                                                           |        |
| **Final Device**                                          |        |
| Sensors / produce interaction with environment            | **20** |
| Sending data to cloud platform / dashboard                | **10** |
| Controlling device from remotely (via cloud or Bluetooth) | **10** |
| In-person demonstration                                   | **10** |
| Coding style and organization                             | **5**  |
| Features represent a coherent and complete device         | **10** |
|                                                           |        |
| **Documentation**                                         |        |
| Developer documentation                                   | **5**  |
| User documentation                                        | **5**  |
| **Total**                                                 | **97** |

## Acknowledgements

-   Thanks to Bill Siever for project format ideas
    (<https://classes.engineering.wustl.edu/cse222s/schedule/>)
