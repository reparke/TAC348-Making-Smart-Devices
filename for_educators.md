---
title: For Educators
layout: single
toc: true
toc_label: "On This Page"
toc_sticky: true
description: "Information for educators interested in adapting TAC 348 course materials for physical computing, smart devices, wearables, or IoT instruction."
---

TAC 348 is a four-unit, project-based course that introduces physical computing to students from a wide range of majors. The course assumes introductory programming experience, but no previous electronics or microcontroller experience.

## Course at a Glance

- **Students and prerequisites:** The course is designed for students from all majors. The [syllabus](tac348_syllabus.html) lists introductory programming prerequisites or equivalent knowledge.
- **Format and tools:** Students use this site for course content, assignments, and preparation, and submit work through Brightspace. The current assignments use the Particle Photon 2 and Particle Workbench.
- **Culminating work:** Each student proposes, builds, documents, and demonstrates an original connected device with sensing, physical output, and an interface.

## Course Design Commitments

- **Build and test in stages.** Assignments begin with circuits and embedded programming, then add components and connected interactions. Students typically submit code, schematics, photographs, test results, and a short demonstration video.
- **Connect code to physical behavior.** Assignment requirements pair inputs such as buttons and sensors with LEDs, displays, sound, motors, or other outputs.
- **Document decisions and limitations.** The final project requires a proposal, design review response, technical milestone, developer documentation, and demonstrations.
- **Consider accessibility in device design.** The syllabus asks students to identify usability and accessibility issues; its weekly breakdown names accessibility and prototype evaluation in Week 13.

The complete objectives, outcomes, prerequisites, and policies are in the [current syllabus](tac348_syllabus.html).

## How Learning Builds Across the Semester

These four groups summarize the [weekly schedule](schedule.html). Some assignments practice a skill across the transition between groups.

### 1. Foundations and Physical I/O

Students start with circuits, the Photon 2, embedded C++, and digital and analog input and output. [Basic Blink](/assignments/a01_blink/a1_blink.html), [Light Sculpture](/assignments/a02_light_sculpture/a2_light_sculpture.html), [Scanning Light](/assignments/a03_scanning_light/a3_scanning_light.html), and [Dice](/assignments/a04_dice/a4_dice.html) use LEDs, a potentiometer, or a button to produce physical output.

### 2. Sensing and Connected Data

The schedule introduces sensors, displays, cloud communication, webhooks, and dashboards. [Button Timers](/assignments/a05_button_timers/a5_button_timers.html) works with digital button input and timed RGB LED output; [Environment Monitor and Dashboard](/assignments/a06_environment_monitor/a6_environment_monitor.html) adds temperature and humidity sensing, an OLED display, cloud events, and a dashboard.

### 3. Interactive Systems

Students work with state machines, sound, motors, mobile control, and Bluetooth. [State Machine Tea Brewer](/assignments/a08_tea_brewer_state_machine_blynk_v3/a8_tea_brewer_state_machine_blynk.html) uses states and a Blynk interface; [Bluetooth Car](/assignments/a09_bluetooth_car/a9_bluetooth_car.html) requires a motorized car controlled from a smartphone over Bluetooth.

### 4. Integrated Device Design

Later weeks include JSON and APIs, multi-component devices, wearables, and final-project work. Students build a [Smart Watch](/assignments/a10_smart_watch_build/a10_smart_watch_build.html) and develop a [project proposal, technical milestone, and final device](/assignments/project/final_project.html). The final project requires connected data, physical output, an interface, documentation, and a demonstration.

## Representative Course Evidence

- [Weekly Schedule](schedule.html): Lists each week's preparation, lectures, and assignments, including project work later in the semester.
- [Environment Monitor and Dashboard](/assignments/a06_environment_monitor/a6_environment_monitor.html): Requires temperature and humidity readings, an OLED display, Particle cloud events, and a cloud dashboard.
- [State Machine Tea Brewer](/assignments/a08_tea_brewer_state_machine_blynk_v3/a8_tea_brewer_state_machine_blynk.html): Requires tea-brewing states and a Blynk interface for feedback and control.
- [Final Project requirements](/assignments/project/final_project.html): Specify a proposal, design review, working technical milestone, connected device and interface, documentation, and final demonstration.
- [Past Projects](/assignments/project/past_projects.html): Shows selected student final projects with links to their posts and demonstrations.

## Explore the Complete Materials

The public materials include:

- A [week-by-week schedule](schedule.html) connecting preparation, lectures, exercises, and assignments
- [Lecture materials](lectures.html) covering electronics, embedded C++, sensors, communication, and prototyping
- [Assignments](assignments.html) with requirements, diagrams, and build instructions
- [Pre-lecture videos and readings](readings.html)
- A component-based [technical reference library](reference.html)
- In-class [code exercises](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_exercises)
- Documentation for the custom [course kit](kit.html)

## Adapting the Materials

The materials on this site are shared as an open educational resource. Educators are welcome to use or adapt individual lessons, assignments, reference guides, or the broader course sequence under the terms of [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/).

The materials can be used at several scales:

- Link to a single reference guide or lecture from another course
- Adapt an assignment to a different microcontroller or component set
- Use the weekly sequence as a starting point for a physical computing course
- Combine selected modules into an IoT, prototyping, wearable computing, or embedded systems course

The current implementation uses the Particle Photon 2 and Particle Workbench. Many concepts and activities can be adapted to Arduino-compatible or other embedded platforms, although code, pin assignments, and cloud integrations will require revision.

## Course Evolution and Production

[Course History](course_history.html) gives a timeline of course changes. The public [GitHub repository](https://github.com/reparke/TAC348-Making-Smart-Devices) contains the source files; its [releases and tags](https://github.com/reparke/TAC348-Making-Smart-Devices/tags) provide version points.

## Licensing, Attribution, and Contact

Unless otherwise noted, the original course materials are licensed under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/). Some pages also include third-party images, code, or resources governed by their own licenses.

A suggested attribution is:

> Rob Parke, *TAC 348: Making Smart Devices*, University of Southern California, <https://makingsmartdevices.com/>, CC BY-NC-SA 4.0.

Questions, corrections, and suggestions about these materials are welcome.
