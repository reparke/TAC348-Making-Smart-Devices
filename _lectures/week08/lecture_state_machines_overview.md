---
marp: true
theme: itp

week: 8
category: lectures
title: State Machines Part 1 - Overview
---
<!-- headingDivider: 2 -->

# State Machines
### TAC 348 - Making Smart Devices

![bg opacity:.85 left:60%](lecture_state_machines_overview.assets/image-20200303153612762.png)

## Learning Objectives
* Understand what a state machine is
* Describe situations where a state machine is useful
* Analyze a real-world situation to create states, transitions, and input
* Implement a state machine in Photon 2 firmware

## What's the main point?

* Our devices should operate remotely without constant user intervention
* Our devices can receive various sensor data (**input**) in different situations (**states**), which results in different actions (**outputs**)
* Tracking and organizing all these possibilities can become very complicated
* **State machines** provide a way of thinking about and designing for the various situations that arise

## State Machine

* A state machine (or *finite state machine*) is mental **model** to help us make decisions
  * It is not just hardware or just software code
* Examine
  * What has happened previously (**state**)
  * What is happening currently (**input**)

* Then generate
  * Next **output**
  * Next **state** (transition)

## Example #1 Stoplight
![bg opacity:1 right contain](lecture_state_machines_overview.assets/stoplight.jpg)


## Example #1 Stoplight

* Consider a simplified stoplight without any pedestrians
* Lights changed after a fixed time
* What states are there?
* How do we transition to new states?

## Example #1 Stoplight Diagram
![bg opacity:1 right contain](lecture_state_machines_overview.assets/simple_stop_light_state_diagram.png)

<!-- draw state diagram
-->

## Example #1 Stoplight

| State            | Output (Stoplight Color) |
| ---------------- | ------------------------ |
| Traffic Flows    | Green                    |
| Traffic Stopping | Yellow                   |
| Traffic Stopped  | Red                      |

## Example #2 Sprinkles Cupcake ATM 
![bg opacity:.85 right:60%](lecture_state_machines_overview.assets/image-20200303153612762-1614475019108.png)

<!--
<img src="lecture_finite_state_machines.assets/image-20200303153612762.png" alt="image-20200303153612762" style="width:800px;" />
-->

<!-- draw state diagram
idle +start+ display 
display +select+ process
display -cancel- idle
display |selection empty| display 
process +credit card valid+ dispense
process |credit card valid| process
dispense |cupcake remains| dispense
dispense +cupcake taken| idle
-->

## Example #2 Sprinkles Cupcake ATM Diagram
* Similar to soft drink vending machine
* What states are there?
* How do we transition to new states?

## Example #2 Sprinkles Cupcake ATM

| State               | Input              | Next State          |
| ------------------- | ------------------ | ------------------- |
| Idle                | None               | Idle                |
| Idle                | Start button       | Display choices     |
| Display choices     | Choice available   | Process credit card |
| Display choices     | Choice unavailable | Display choices     |
| Display choices     | Cancel             | Idle                |
| Process credit card | Card valid         | Dispense cupcake    |
| Process credit card | Card invalid       | Process credit card |
| Dispense cupcake    | Cupcake taken      | Idle                |
| Dispense cupcake    | Cupcake remains    | Dispense cupcake    |


## State Machines in Photon 2

* In order to implement this in our firmware, what elements / functions do we need to create?
  * inputs 
  * outputs
  * state 
  * state transition logic 
* How could we implement these in firmware?


## State Machines in Photon 2

* inputs (e.g. `millis()` timer, `digitalRead`, `analogRead`)

* outputs (e.g. LED, speaker, OLED screen)

* state (create `enum` to track current state and next state)

* state transition logic
  * typically a function with conditional logic like `switch` or `if`
  * use current state and any input to determine the next state 

## State Transition Logic Example
* Let's look at just one piece of the Sprinkles vending machine, namely processing valid and invalid credit cards

| State               | Input        | Next State          |
| ------------------- | ------------ | ------------------- |
| Process credit card | Card valid   | Dispense cupcake    |
| Process credit card | Card invalid | Process credit card |

## State Transition Logic Example
* Input: credit card valid or invalid
  * global variable `bool cardValid`
* States: describe all possible states and track current state
  * `enum State {...}`
  * `State currentState;`
```c++
//Global variables
bool cardValid;   //is customer card valid
enum State {IDLE, DISPLAY, PROCESS, DISPENSE }; //all possible states
State currentState;   //state the machine is in right now 
```

## State Transition Logic Example
* State transition: conditional logic to move to next state based on `currentState` and `cardValid`
```c++
void updateNextState() {
   switch(currentState) { 
      case PROCESS:                 //current state is processing credit card
         if (cardValid == true) {   //credit cart is valid so start dispensing
            currentState = DISPENSE;
         }
         //if cardValid == false, remain in PROCESS state
         //no else block is needed
   }
}
```



## Credits

* [Bill Siever](http://siever.info) - [CS132 FSM](http://siever.info/cse132/guides/intro-to-FSMs.html)  (Washington University at St. Louis) 
* [Bill Siever](http://siever.info) - [CS132 Delta Timing](http://siever.info/cse132/weeks/3/)  (Washington University at St. Louis) 
* [USC EE109 State Machines](http://bits.usc.edu/files/ee109/)
* Photo by Laurie Parke
* Photo by [Michael Olsen](https://unsplash.com/@mganeolsen)</a> on [Unsplash](https://unsplash.com/)
* Photo by [Free To Use Sounds](https://unsplash.com/@freetousesoundscom?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText) on [Unsplash](https://unsplash.com/?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText)
* Photo by [NON](https://unsplash.com/@non_creation?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText) on [Unsplash](https://unsplash.com/?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText)