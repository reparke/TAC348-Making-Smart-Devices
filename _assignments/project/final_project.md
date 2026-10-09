---
week: 11
number: 12
category: assignments
title: Final Project
description: "Final project requirements for TAC 348 Making Smart Devices, including a proposal, technical milestone, connected device, documentation, and demonstration."
date_due: Proposal due Sun Nov-08 @ 11:59 pm; Milestone due Sun Nov-29 @ 11:59 pm; Finished device and presentation during the Final Exam Time listed in the Schedule of Classes (in person) Fri Dec-11 @ 11am-1pm for MW class and Tue Dec-15 @ 8-10am for TTh class
---

<span id="final-project"></span>

[Submit on Brightspace](https://brightspace.usc.edu/)

Goals
-----

- Identify a human need and develop requirements for a connected device.
- Design and build a device that senses its environment, communicates data, and produces a physical response.
- Create two-way communication between a device and a cloud, web, mobile, or approved Bluetooth interface.
- Refine the project idea and design using feedback from external reviewers and the instructor.
- Explain design decisions and document the project for technical and nontechnical audiences.

Overview
--------

The project is to create a prototype of a connected device. The final submission
does not need to be “ready for manufacturing” but it must work and demonstrate
the key functioning elements. Here is a [partial list of components and services](sample_components) covered in class.

## Project Design Process

The project has several stages. At each stage, you will show your progress, receive feedback, and revise your design.

| Stage | What you submit or present | Feedback / next step |
| --- | --- | --- |
| Preliminary ideas | Two ideas that address different needs | Instructor feedback helps identify a feasible direction. |
| Project proposal | Need, audience, features, system plan, components, budget, and risks | The instructor reviews and approves the project direction. |
| External design review | Short presentation of the need and proposed design | Outside experts provide supportive feedback. |
| Design-review response | Short reflection on the most useful feedback | You identify one change you plan to make. |
| Technical milestone | Schematic, one working part, and a short status update | Instructor feedback helps identify problems while there is still time to revise. |
| Final prototype | Device, interface, dashboard, documentation, and demonstration | You demonstrate the finished system and explain your decisions. |

## Project Requirements

* Be designed and built by you solely. Inspiration may be taken from online and other sources, but sources must be cited and the final project must be substantially different.
* Use at least four major components. Major components include:
  * Sensors
  * Servos / motors
  * Components not covered in class will probably count, but they need to be approved
  * LEDs and buttons count, but together they count as only one component
  * A switch connected to the EN pin does not count as a component
* Use at least two components to interact with the environment (e.g., a switch or button)
* Use cloud / internet connectivity in a meaningful way
* Must send data to a cloud system and display a dashboard
  * Examples of acceptable tools
    * [Initial State](https://www.initialstate.com/)
    * [Losant](https://www.losant.com/)
    * [ThingSpeak](https://thingspeak.com/)
  * Blynk does not meet the dashboard requirement
* Must have an interface app (web or mobile) that can send commands to the device to produce effects in the physical world (i.e., control the device remotely)
  - Examples of acceptable tools
    - Blynk cloud app
    - [Initial State](https://www.initialstate.com/) (must use [input controls](https://www.initialstate.com/blog/input-controls/) not just dashboard tools)
    - [Losant](https://www.losant.com/)
    - If using Bluetooth, the [Bluefruit](https://learn.adafruit.com/bluefruit-le-connect) app will be considered as long as it is substantially different from the car assignment
  - Not acceptable
    - Particle app
* Comment your code and follow consistent coding conventions
* Written and video documentation (see below)
* Your project has to compile and run *(projects that fail to run will receive a 50% penalty)*
* No late submissions will be accepted
* Note: In the coming weeks, we will discuss the following components in case
  you want to include them in your project:
  * Heart rate sensors
  * Digital temperature and humidity sensor
  * Ultrasonic distance sensor
  * Accelerometer

### Possible Project Ideas

* Head-mounted collision-detection and navigation wearable
* Earthquake monitor
* Retrofitted children’s toy
* Home monitoring station
* [Sample past projects](past_projects)

Deliverables
------------

### Proposal Deliverables

* Write a proposal document with the following details:
  * Describe the problem or need you have identified, why you believe it is
    necessary to address, and how your device would address this need.
  * Describe the target audience
  * List the key features, sensors, interaction patterns (e.g., how
    users interact with the device), and internet / cloud platforms
  * Provide a rough budget for how much it would cost to build your device. You should
    include items in your kit as well as items not in your kit (e.g.,
    building supplies, other sensors, etc.)
* *Note: You can modify your project later but you must submit a revised proposal for approval. Failure to do so will result in a 10% deduction*

* [Sample proposal](https://reparke.github.io/TAC348-Making-Smart-Devices/assignments/project/samples/project_proposal_sample.pdf)

### External Design Review and Design-Review Response

After submitting the proposal, you will present your project to a panel of outside experts. Their feedback will help you identify risks and improve the design before building most of the project.

After the review, submit a short response (about one paragraph) that:

- Summarizes the most useful feedback you received.
- Identifies at least one change you plan to make.

### Project Milestone Deliverables

Submit the following:

- A complete and current Fritzing diagram.
- A photograph, data, or a short video showing that one important part of the project works. Examples include reading a sensor, sending data to the cloud, receiving a remote command, or controlling an actuator.
- A few sentences describing what is working and your next step.

The part you demonstrate does not need to be polished or integrated into the complete device at this stage.

### Project - Final Deliverables

**The remaining items are to be submitted on Brightspace**

- Workbench project with firmware code
- Screenshots of dashboard and interface web app
- Technical walkthrough video (include YouTube link in submission)
  - Clear and simple video demonstrating each feature working (no need for fancy editing)
  - Must show that each project requirement has been met.
- Developer documentation
  - Assume a future TAC 348 student is taking the course and has been told to make a
    specific change to your project (add a feature, fix an error, etc.).
  - Provide instructions for how to set up your device and then explain the key elements (include any other helpful documentation such as sequence diagrams, Fritzing diagrams, etc.)
  - Consider the following:
    - What would they need to know to set up your project and get it running?
    - What would they need to know to modify it? (Assume that they don’t want to read through all your code; they want some sort of a quick start guide that will help them identify where they should start looking/working first)
    - Give a general overview of all aspects of your project with sufficient detail for them to know where to look to make modifications.
  - [Sample developer documentation](https://reparke.github.io/TAC348-Making-Smart-Devices/assignments/project/samples/project_developer_guide_sample.pdf)
- Sizzle reel / product highlight video (include YouTube link in submission)
  - A short, polished video that showcases your device (30–60 seconds)
  - Demonstrates the device’s purpose and major features in a visually appealing way
  - Think of this as something for your portfolio

### Project - Final Presentation (10 minutes)

- This is a required in-person demonstration of your functioning device scheduled during our final exam time
- You may create a short video introduction highlighting your project (***please keep your video under 2 minutes***)
- The presentation should address the following:
  - What your device does / what problem it solves
  - How your device satisfies each requirement in the grading rubric
    - Four key components
    - Remote control / Blynk / Bluetooth functionality
    - Dashboard
  - What was the most challenging or interesting aspect of the project
- You will then demonstrate all the functionality of your device. If it isn't feasible to show it live, you can pre-record this part

## Submission Instructions

* Submit all documents via Brightspace
* Bring the device to the in-person project demonstration

Grading
-------

Each criterion will be evaluated using the following performance levels:

- **Exemplary:** Complete, reliable, and well justified.
- **Proficient:** Meets the requirement with minor limitations.
- **Developing:** Partially meets the requirement, but important problems remain.
- **Beginning:** Shows limited progress toward the requirement.
- **No evidence:** The required element is absent or cannot be evaluated.

| Criterion | Evidence of achievement | Points |
| --- | --- | ---: |
| **Proposal and Design Review** |  |  |
| **Proposal: need and audience** | Identifies the need, audience, and why the device is an appropriate response. | **3** |
| **Proposal: goals and system plan** | Explains the project goals, inputs, outputs, components, interactions, and connected services. | **4** |
| **Proposal: feasibility** | Includes a realistic budget, scope, risks, schedule, and fallback plan. | **3** |
| **Design-review response** | Summarizes the most useful feedback and identifies one planned change. | **3** |
|  |  |  |
| **Project Milestone** |  |  |
| **Milestone: schematic** | Includes a complete and accurate Fritzing diagram of the current design. | **5** |
| **Milestone: progress** | Shows that one important part works and identifies the next step. | **5** |
|  |  |  |
| **Final Device** |  |  |
| **Environmental interaction** | Inputs and physical outputs function reliably and serve the device’s purpose. | **14** |
| **Cloud data and dashboard** | The device sends useful data to the cloud and displays it in a clear dashboard. | **8** |
| **Remote control** | An approved interface reliably changes the device’s physical behavior. | **8** |
| **Integration and reliability** | Hardware, firmware, connectivity, and interface operate together reliably. | **14** |
| **Coherent and complete device** | Features work together and address the need identified in the proposal. | **8** |
| **Code quality** | Code is organized, consistent, commented, and understandable. | **5** |
|  |  |  |
| **Final Presentation** |  |  |
| **In-person demonstration** | Explains the project and demonstrates the required functionality. | **10** |
|  |  |  |
| **Documentation** |  |  |
| **Developer documentation** | Allows a future TAC 348 student to set up, understand, and modify the project. | **4** |
| **Technical walkthrough video** | Shows each required feature working and explains the key technical elements. | **3** |
| **Product highlight video** | Clearly communicates the device’s purpose and major features. | **3** |
| **Total** |  | **100** |

## Acknowledgements

- Thanks to Bill Siever for project format ideas
  ([CSE 222S course schedule](https://classes.engineering.wustl.edu/cse222s/schedule/))
