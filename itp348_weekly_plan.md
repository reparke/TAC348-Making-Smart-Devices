---
        
layout: single
classes: wide
title: Weekly Plan
toc: false
toc_label: "Quick Links"
toc_icon: "bookmark"  # corresponding Font Awesome icon name (without fa prefix)
toc_sticky: true 

---


## 		Things to implement

**Definite**

* [ ] week 10
  * [ ] future semester: consider permanently putting motors here; add something else for week 9
* [ ] week 11Thank
  * [ ] ultra sonic and oled could be combined--it's not quite enough for 2 day
  * [ ] change bitmaps, code, and .h file so names are "no_large.bmp" and "no_small.bmp"
* [ ] change some old projects (or at least starting code) to use new workbench templat
* [ ] update graphics slides and videos to use PROGMEM (See exercis)

Week 10 idea: 

* [ ] Tues is ultra sonic sensor + project overview; show BRIEFLY how to load images
* [ ] Thurs is using JSON to send multiple values to Initial State; consider recording a video for json overview and moving early
* [ ] week 10 / 11: may need to record JSON videos for clarity
* [ ] week 10 / 11: may need to include a subscribe video or lectu

* [ ] consider moving A9 earlier to be closer to material (even if prelim proposal and A9 overlap)
* [ ] consider removing week 10 OLED graphics, replace with...? JSON, softpot, piezo motion sensor

---

**Maybe**

* [ ] JSON
  * [ ] could we cover creating JSON in week 6, then week 10 would just be parsing?
  * [ ] when sending json to initial state using POST, could we use query params for API/ Bucket instead of HTTP headers?

* [ ] TA recommendations
  * [ ] have small assignment where they layout PCB for a built project; then later in the semester the soldering workshop uses that design (talk to kristof about this so we don't step on 388)
  * [ ] submissions: 
    * [ ] make single zip for upload with code and fritzing
    * [ ] create google doc with photos embedded and video link; 
    * [ ] students should narrate
    * [ ] Rob announce and demostrates in first week
    * [ ] TAs ask for corrected videos if misssing
    * [ ] partial credit for some working
* [ ] Soldering workshop
  * [ ] Plan event in week3 for sometime before week 9
  * [ ] Consider holding during a class session to have more people attend
  * [ ] provide solder (or ask Allan in available)
  * [ ] consider more complicated soldering kit (or variations)
  * [ ] have people check soldering kits before hand for broken LEDs
  * [ ] Maybe we could show them a brief over view or short video of how to make a PCB board and order some from a supplier overseas through Fritzing and then have them solder their board? Or like maybe week 3/4 of school after they have familiarized themselves with fritzing, have students create a simple PCB that would wire some leds and maybe a potentiometer so students can turn the knob and have the soldered leds on the board turn dim/bright. Then the TAs could double check their Fritzing submission and make sure all power/GND wires are connected on the appropriate sides of the PCB then run some tests to make sure the connections are correct. Then wait for the custom boards to arrive and have students in class solder their custom boards. Theres a way to add names and labels to the PCB itself thats really cool
* [ ] create ["cheat sheet"](https://education.github.com/git-cheat-sheet-education.pdf) or video about basic workbench operations (flash, create project, import library)
* [ ] 5v voltage regulator: [5V Step-Up Voltage Regulator U3V40F5](https://www.pololu.com/product/4012)
  * [ ] also [SparkFun Buck-Boost Converter]( https://www.sparkfun.com/products/15208)
* [ ] tell students not to unclaim device
* [ ] recruit guest lecturers (x2)

**Possible**

* [ ] summary of info. 

  - [ ] Maybe a page of "tips" - cool work-around or example of something not completely covered in class. 

- [ ] Maybe a page of "oops" - mistakes to be avoided
  
  - [x] Maybe a page of troubleshooting - there were a few tricky situations people posted on Piazza, a record of that would be cool
  
  - [ ] Maybe a page of ideas - problems to solve. Maybe something you and the TAs add, challenges of all levels for fun
  
  
  



**Videos and Wiring Diagrams Needed to Publish**

- [ ] Week 3
- - [ ] a5: create new assignment that doesn't use while loop timing, consider using millis
- [ ] Week 4
- - [ ] Multi-tasking (maybe keep a)
  - [ ] Publish (skip)
  - [ ] re-record OLED with I2C slides
- [ ] Week 5
- - [ ] Webhooks / APIs (Initial State can be live)
  - [ ] wk 5: use millis in next assignment (summer)
  - [ ] wk 5: move enum and switch videos to week 6 (summer)
- [ ] Week 8
  - [ ] Motors
- [ ] Week 10
  - [ ] JSON / APIs (need to re-record)
  - [ ] wk11: inquire about future class TAs and kit TA
- [ ] Week 11
  - [ ] Revise JSON in week 10. Try using ArduinoJSON instead of RK. The generation of RK is very tough. This would mean re-recording the parsing video to use ArduinoJSON

## Pre-semester

- [ ] Send students kit pickup instructions
- [ ] purchase items (see Evernote pre-semester tasks)





## 1. Intro, Microcontrollers, LEDs

### Reading / Video

* [http://www.tigoe.com/pcomp/code/circuits/understanding-electricity/](http://www.tigoe.com/pcomp/code/circuits/understanding-electricity/)
  * [https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law/all](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law/all)

* Video discussion of C++ review (make little videos for functions); curate or record
* Video: Creating, configuring, and opening workbench projects
* Do poll

### Assignment

- Due start of current week: none
- Given out start of current week: A0 - Software and tool installation; A1 - Blink

### Day 1

#### Alternate Plan - Spring missing one day

- Spring 2024: I tried covering electricity today and it felt like too much for the first day. Rather than going faster in week 1 to prepare for missed day, it is probably better to make up the material in week 2 or 3

#### Lecture

* Remind: ==Students need to pick up kit from ITP office BEFORE Wed class==

- Course introduction / syllabus (PPTX)
- Ice breaker *(see slides in local ITP 348 Docs folder)* 
  
- Introduction to IoT
- Explain course website
- Kit overiew
  - Explain how to use envelopes
  - Explain how to identify kit parts


#### Lecture

* C++ Syntax (optional at the end)

### Day 2

#### Announcements

- Kits: students are responsible for returning devices if they drop before drop deadline
- Assignment 0 & 1 are due Sunday; OH help installing on Friday

#### Lecture

- Electricity and Ohm's Law
- Safety
- Photon 2 microcontroller

- Software tools: Workbench (open and discuss)
- LED 

#### Lab

- show how to put Photon 2 on breadboard and remove 
- turn on LED + resistor by connecting to 3v3 and ground
- show how to flash and make light blink (most people won't have their device claimed yet)

#### Feedback

- Most students were familiar with electricity principles, units (kilo, milli) so the electricity presentation very simple

  

## 2. Pulse Width Modulation, ADC ==Spring 2024 - MLK Holiday==

### Holiday Alternative Plan

- w2d1 - holiday
- w2d2
  - Review digital output (Blink 2 LED)
  - Review Workbench project
  - Pulse width modulation (lecture, PWM pins, analogWrite)
  - Serial monitor
  - Analog to digital conversion + potentiometer
- w3d1
  - buttons
  - latching
- w3d2
  - RGB leds
  - functions
  - libraries (if time)
  
  

### Announcements

- Reminder to order Sparkfun kit
- Reminder to watch course videos

### Reading

- Analog vs. digital (video)
- Analog input / potentiometers (video)
- C++ `for` loops (optional video)

#### Assignment

- Due start of current week: A0 and A1 - Blink
- Given out start of current week: A2 - Light Sculpture 

### Day 1

#### Notes

- TA and I spent some time class helping install
- Demonstrate how to reset device and go to safe mode

#### Lecture

* Quickly review LED / Digital output

### Lab

- Blink 2 LED
- Explain Workbench project

#### Lecture

- Pulse width modulation (lecture, PWM pins, analogWrite)

#### Lab

- Make light fully bright for 2 sec, half as bright for 2 sec, 1/3 as bright for 2 sec, 
- Challenge: Increase light level of LED automatically

#### Lab

- Have students use for loop to sweep the brightness of an LED
- Discuss `for` loops

#### Feedback

- spend time reviewing LEDs + resistors since we went quickly in previous week

### Day 2

#### Lecture

- Serial monitor


#### Guided activity

- Do simple example where there is a global variable that gets incremented and display its value with Serial monitor

- Have students connect pot to 3.3v, gnd, and A0; display the values on serial monitor

#### Lecture

- Analog to digital conversion

#### Lab

- Wire pot + LED
- Use potentiometer to control light level

#### If time (to get ahead for holiday)

* Quickly go through buttons slides and wire a button



## 3. Buttons, Digital Input, RGB

### Announcements

- Explain social issues assignment - sign ups in two weeks

### Assignment

- Due start of current week: A2 - Light Sculpture 
- Given out start of current week: A3 - Cylon light 
### Reading

- https://learn.sparkfun.com/tutorials/pull-up-resistors
- https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all
- Digital Input / Push buttons (video)
- RGB LEDs (video)

### Day 1

#### Guided activity

- Ask them to **digitalRead()** on D2; use serial monitor to read with no connection (will be floating); then directly connect to **3.3v**, then GND
- connect button with pullup
- Ask what is the voltage at pin when button pressed and not pressed

#### Guided activity

* Explain Fritzing software
* Create button with resistors in Fritzing

#### Guided activity

- Connect button with resistor on Photon 2

#### Lab (students work on)

- Turn LED on while button pressed
- Turn LED off after button pressed
- Connect two LEDs

#### Guided activity

- Latching button **==identify way to program this==**
- Connect 3 LEDs and control on/off with button presses (3 states)

#### Lecture

- No slides for latch. Instead draw pictures with square wave

#### Feedback

- 

### Day 2

#### Lecture

- RGB LED lecture

#### Lab

- Display random color

#### Lecture

- Functions in C++ *(this should be review from week 2)*

#### Lab

- Button press trigger random color
- Rewrite sketch using `displayColor(r, g, b)` and `displayRandomColor()`
- cycle button presses to display C (BG) M (RB) Y (RG)

#### Lecture  (==if time==)

- Libraries

#### Lab

- Have students find and install `rgb-controls`
- Ask them to create some colors effects on their own
- Then walk through example together
- If time, introduce a button to control states (idea of a state machine)

### Fall 2022 Holiday Plan

* Discuss scanning light assignment 
* Lecture: digital input
* Draw and discuss button
* Guided: Wire RGB and Button with this [image](https://reparke.github.io/ITP348-Physical-Computing/lectures/week03/lecture_rgb_leds.assets/image-20210204155745432.png)
* Guided: make button turn on D7
* cover latch (motivate)
* discuss RGB LED
* have students make RGB LED turn on white when pressed only
* Have students press show red for 1/2 sec, green for 1/2 sec, blue for 1/2 sec, then orange for 1/2 sec
* show random and have button press be random (if time)
* show sequence if time (see 20233 TTh code)
* show libraries if time
* consider modifying assignment 


### Feedback 

- overall worked well but over zoom, we didn't have time for **libraries or functions or switch or multimeters**

## 4. Photoresistors, Multitasking

### Assignment

- Due start of current week: A3 - Cylon light 
- Given out start of current week: A4 - Electronic dice

### Reading

* [Kirchoff's Voltage Law](https://www.khanacademy.org/science/ap-physics-1/ap-circuits-topic/kirchhoffs-loop-rule-ap/v/ee-kirchhoffs-voltage-law)

### Day 1

#### 2021 Spring Idea

* ==Consider covering functions and libraries on Day 1, and leaving publishing for day 2==

#### Lecture

* Photoresistor (video)

#### Exercise

* Calibrate photoresistor

#### Lecture

- Particle Cloud Publish

#### Lab

- publish photoresistor value and "state" (for example bright, ambient, or dark to Particle cloud)

### Feedback

* Started with review
* This was a good amount of material; we had time to introduce functions to use RGB

### Day 2

#### Lecture

* ==Announce Brightspace quiz during week 6 (ask for feedback if it should be on the weekend or after monday)==
* ==Announce survey==

- Multitasking with millis

#### Guided Activity

- Start: Blink one LED on and off, display serial message when button presed
- Walk through blocking example with button
- Demonstrate millis example with one light blinking

#### Lab

1. Use `delay` to blink **LED1** every 300 ms and then check for a button press (not a toggle); display Serial message if button pressed 
2. Use `millis()` to fix blocking in #1 (we'll do #1 and #2 together)
3. Use `millis()` to blink **LED2** every 146 ms
4. Enable toggle button to turn **ON BOARD LED** on and off on the **rising edge**
5. Track number of button presses and use `millis()` to publish number of button presses every **10000 ms**
6. Extra Challenge
     * Change **LED1** to be *on* for 300 ms and *off* for 700 ms
     * Change  code so that when the toggle button is pressed, **LED2** starts blinking every 146 **milliseconds**, and when the toggle button is pressed again, **LED2** stops blinking

#### Feedback

- 



## 5. TMP36, OLED

### Assignment

- Due start of current week: A4 - Electronic dice 
- Given out start of current week: A5 - Reaction Timer
- Alternate ideas: use TMP36 to measure temperature and display colors on RGB LED. Use potentiometer to control brightness of RGB LED. Display results on serial monitor. **Optional** use button for diagnostic or to change cel/fahr 


### Day 1

#### Lecture

- ==Announce Brightspace quiz during week 6 (ask for feedback if it should be on the weekend or after monday)==
- ==Announce survey==
- ==Remind students about extra credit for posting on social issues==
- Quiz is open Thurs 2/18 after class (6 pm PST) until Monday 2/22 at 11:59 pm PST. Once you start it, you will have 60 minutes but it might take you 15 min.
- TMP36

#### Exercise (in slides)

* Connect a TMP36 and output the current temperature to the serial monitor
* Consider what type of input is this signal? How will this value be read by Photon 2

#### Lecture

- APIs and webhooks
- Data visualization for single values (stop before slide 7 and do the demo live)

#### Guided Activity

- Create InitialState account (use *.edu)
- Create webhook in Particle (replace `data` in webhook with value you want in InitialState)
- Make sure to use `GET` and `Query Parameters` in the webhook se
- Send TMP36 value`Particle.publish` to InitialState

- Use Initial state to send temperature data

### Day 2

#### Lecture

- Libraries
- Discuss OLED

#### Lab

- Have students connect OLED to display "Hello World"

#### Lab

- Have students create an Etch-A-Sketch with OLED

### Feedback

* This took longer than expected since there was much debugging needed. We finished basic setup of OLED but didn't have time to introduce lab for etch-a-sketch

## 6. Magnetic Switch; Blynk ==Alt plan for holiday: Covering Sound==

==**Spring**== Presidents Day cancelled one day from Week 6. New Plan

- w6d1 holiday
- w6d2 sound
- w7d1 magnetic switch
- w7d2 blynk
- w8d1 FSM stoplight
- w8d2 FSM washing machine
- w9d1 motors with fan
- w9d2 motors with fan + bluetooth

#### Assignment

- Due start of current week: A5 - Button Timer
- Given out start of current week: A6 - Shared Environment Monitor

### Reading

- Have students create an [Blynk](https://blynk.io/) account
  - Have students come to class with RGB LED with magnetic switch (Tues) and again for (thurs)


### Day 1

#### Lecture

- Magnetic switch (video)

#### Lab

- Wire switch and RGB LED
- Publish switch event in console (this won't take very long)

- Create function to change LED colors: white switch is closed, red switch is open

#### Lecture

- Start Blynk
  - Tell students to cancel "Quick Start" 
  - Go to "Developer Zone" and make new template


#### Guided activity

- Note: Blynk template "Week 6 Lab" can be used for exercise and lab. Use following pins
  - Button Show Light - **V5**
  - Random number - **V6**
- set up Blynk
- Install iOS / Android app
- Demonstrate basic Blynk integration
- Try to finish exercise

### Feedback

- 

### Day 2

#### Lecture

* Review some pasts projects for preliminary project idea
  - https://robparke.com/tag/itp348_projects/
  - https://5cf99969afabc800087c618c.onlosant.com/photon_temperature
  - https://iot.app.initialstate.com/#/tiles/bkt_13hhui7kc4h38hz

#### Lecture

- Finish Blynk (if necessary)

#### Guided activity

- Finish exercise

#### Lab

- Using RGB and switch, use app to control RGB color and get notification for switch

#### Feedback



## 7. Sound ==Spring Presidents Day Holiday==

### Notes

- ==**Fall: Try to start Sound earlier due to fall break**==
  - ==idea: Day 1 covers motors by directly building fan with potentiometer; Day 2 cover bluetooth and control can with bluetooth==
- ==**Fall**==
  - w7d1 Sound
  - w7d2 holiday
  - w8d1, FSM stoplight 
  - w8d2 FSM washing machine
  - w9d1, we covered motors and servos, and built the fan
  - w9d2, we introduced bluetooth with fan 
- ==**Spring**== Presidents Day cancelled one day from Week 7. New Plan
  - w7d1 holiday
  - w7d2 FSM stoplight
  - w8d1 FSM washing machine
  - w8d2 sound
  - w9d1 motors with fan
  - w9d2 motors with fan + bluetooth

### Reading

- Spring: Announce Lab won't be due this week because one day is cancelled

### Assignment

- Due start of current week:   A6 - Shared Environment Monitor
- Given out start of current week:  A7 - Preliminary Proposal Idea

### Day 1

#### Lecture

* Speaker
* Tone
* Pitches

### Exercise

- Show basic tone example with `delay` (blocking)
- Ask students to try to blink on board LED every 100ms and also play a tone every 1000ms ( use `millis` and `noTone` to make non-blocking)
- Show students `pitches.h` and logic for creating music with tempo
- Have students try to create their own song

### Day 2 ==Fall Break==



## 8. Finite State Machines

### Reading

- 

### Assignment

- Due start of current week:   A7 - Preliminary Proposal Idea
- Given out start of current week: A8 - Tea State Machine with Blynk (due in two weeks)

### Day 1

#### Lecture

- Finite state machines (video)
- Discuss state machines

#### Lab

- Starting with sample code
- walk through NS light state transitions (length, state)

### Feedback

- some students enjoyed the complexity of all parts, other seemed bored

### Day 2

#### Lecture

- Washing machine example

#### Lab

- Draw state diagram

- Go through code to

- phase 1

  - create enum for cycle and for state
  - create current state global variable
  
  - phase 2
    - Cycle getCyclePosition()
  
  - phase 3
    - loop
  
  - phase 4
    - setoutputs for idle
  
  - phase 5
    - nextduration for idle
    - next state for idle
  
  - phase 6
    - setouputs, next duration, next state for economy
  
- 

## Feedback

- 

## 9. Bluetooth and Motors

### Reading

- Motors
  - [https://www.electronicproducts.com/Electromechanical_Components/Motors_and_Controllers/Motor_control_design_an_introduction_to_motors_and_controllers.aspx](https://www.electronicproducts.com/Electromechanical_Components/Motors_and_Controllers/Motor_control_design_an_introduction_to_motors_and_controllers.aspx)
- Bluetooth
  * [https://learn.sparkfun.com/tutorials/bluetooth-basics/all](https://learn.sparkfun.com/tutorials/bluetooth-basics/all)
  * [https://learn.adafruit.com/introduction-to-bluetooth-low-energy/](https://learn.adafruit.com/introduction-to-bluetooth-low-energy/)

### Assignment

* Due start of current week: none
* Given out start of current week: none, but continue to work on  A8 - Timer with Blynk 

### Day 1

- Have students build fan and circuit before class


#### Lecture

- DC Motors

#### Lab

- Demonstrate connecting motor to 3v3
- Start fan project by using potentiometer to control DC motor speed only

#### Lecture

- Servo motors

#### Lab

- Use potentiometer to direction 
- Use potentiometer to control fan speed while servo rotates automatically

#### Lecture

- LIPO battery

#### Feedback

- students followed remotely and enjoyed building the fan
- I skipped the separate servo part and went directly to using the servo to control the fan
- ==**Idea for next semester**==: create assignment using motors and bluetooth (something like the fan)

### Day 2

#### Lecture

- Bluetooth
- Photon 2 BLE syntax
- Show Bluefruit app (skip nRF Toolbox)

#### Lab - ble_fan_start

- Distribute github link to download (post on slides)

- Describe project goals

- Explain **particle_ble_setup.h** at a high level
  - Have students change **DEVICE_NAME**
  
- Pull up Bluefruit [documentation](https://learn.adafruit.com/bluefruit-le-connect/controller) and explain button signal

- Code together blinking D7 when **press 1**

- Have students code on their own D7 on with **press up** and D7 off when **release up**

  

#### Lab - ble_uart_control_start

- Distribute github link to download (post on slides)
- Describe project goals
- Explain **particle_ble_setup.h** at a high level
  - Have students change **DEVICE_NAME**
- Pull up Bluefruit [documentation](https://learn.adafruit.com/bluefruit-le-connect/controller) and explain button signal
- Code together blinking D7 when **press 1**
- Have students code on their own D7 on with **press up** and D7 off when **release up**
- (If time) have students code play tone when **press right **
- Have students try using color picker to change RGB colors

#### Lab - ble_uart_control_start

- Have students try to control servo and fan motor on their own

### Feedback



## 10. Cloud Dashboards; APIs; Weather;  (==**This may be too much content**==)

### Reading

- Create [Initial State](https://www.initialstate.com/) account
- Create [Weather Stack account](https://weatherstack.com/)


### Assignment

- Due start of current week: A8 - Timer with Blynk 
- Given out start of current week: A9 - Bluetooth Car

### Day 1

#### Lecture

- JSON overview (video)
- May need to introduce Bluetooth car assignment, starting code, and motor control logic
- Lecture: Sending Multiple Values to Initial State using JSON (first few slides)
- live demo to configure
- Show [API documentation for JSON](https://initialstateeventsapi.docs.apiary.io/#reference/event-data/events-json)
- Lecture: JSON creation with arduinojson

#### Exercise

* Send random temperature and humidity using `Particle.publish` to InitialState

#### Lab

- As review, we spent the entire class period reviewing how to send data to initial stack
- Students worked in breakout rooms to create webhook and send GPS and a battery value to initial state
- This took the entire class period
- USC GPS Coordinates
  - lat: 34.0224
  - lon: -118.2851

### Day 2 

* Turn in weather stack lab today

#### Lecture / Lab

- Finish InitialState Integration (if necessary)
- retrieving from api

#### Exercise - Sunrise API

- Have students use [https://api.sunrise-sunset.org](https://api.sunrise-sunset.org) to determine sunrise and sunset time based on lat and long (*no API key required)*)

- Use Query Params in API URL and Mustache in response *(Particle integration: **Sunrise Sunset with Mustache**)*

- Response template

  ```json
  {"sunrise":"{{{results.sunrise}}}","sunset":"{{{results.sunset}}}"}	
  ```

- USC GPS Coordinates

  - lat: 34.0224
  - lon: -118.2851

- show start of retrieiving json slides

- show sunrise api doc

- Show how to find gps coord, and create url

- create particle integration

- NB: Remove the Mustache from response template before showing students

- print out JSON and show what a mess it is

- copy JSON into website to format

- show mustache slides to explain parameters

- add response template

#### Lecture

- Discuss [weather stack](https://weastitherstack.com/) show example call

- Walkthrough integration

- Write json code together

- response template

  ```json
  {"name":"{{location.name}}", "temperature":"{{current.temperature}}","description":"{{current.weather_descriptions.0}}"}
  ```

Consider using this template with UV and weather code because we need them later with the water (or is better to have student review mustache templates when setting up the watch)
  ```json
  {"name":"{{location.name}}", "temperature":"{{current.temperature}}","description":"{{current.weather_descriptions.0}}","weather_code":"{{current.weather_code}}","uv_index":"{{current.uv_index}}"}
  ```

#### Lab

- Create [weather stack](https://weatherstack.com/) account (hopefully they have already done this)
- If there are API problems with weather stack, consider using [https://openweathermap.org/](https://openweathermap.org) except it take up to an hour for API to activate. In that case, just share API key
- Also consider [Air Now EPA air quality API](https://docs.airnowapi.org/webservices)
- Have them use their own API key to view JSON in a browser (use formatter online if necessary
- Create webhook in Particle
- Copy code from particle publishing and subscribing
- Test: publish request and see if subscribe code retrieves JSON data
- Show students an example of how the code works for JSON parser
- Have students show description, temp, location, rainfall

#### Lecture (if time)

- Have students use [https://openweathermap.org/api/air-pollution](https://openweathermap.org/api/air-pollution) to get AQI measure based on lat and long

## 11. Ultrasonic Distance Sensor; OLED Graphics

### Plan for Fall 2024

**==Combine OLED Graphics and ultra sonic in one day==**

==**Need more content here; could be spill over from last week**==

Could combine graphics and OLED in one day; spent time going over A9 whic

Note: need to update exercies (start and final) since trigger and echo pins changed

### Reading

- 

### Assignment

- Due start of current week: A9 - Bluetooth Car
- Given out start of current week: A10 - Smart Watch Assembly
- Given out start of current week: Proposal
### Day 1

#### Lecture

- project overview
- Ultrasonic distance sensor 

#### Lab

- Student design range finding with ultrasonic sensor. Provide starting project (same one that uses OLED later)

### Day 2 --

#### Lecture

- OLED graphics
- add sleep/wake from week 15 (need to add more)

#### Lab

- Student design range finding with ultrasonic sensor. Provide starting project (same one that uses OLED later)

### Feedback Day 1

- Went generally well. Ran out of time to talk about graphics.



## 12. Smart Watch, Heart Rate Sensor

### Reading

- 

### Assignment

- Due start of current week: Proposal
- Due start of current week: A10 - Smart Watch Assembly
- Continue working on project 

### Day 1

#### Activity

* ==**Design review**==
* Depending on time, have class meet in a large group or in 3 person groups
* Each person describes their proposal (==need to develop some framework and questions audience can ask== )

### Day 2

#### Lab

- Create blank project
- Demonstrate heart rate function by using the library example

#### Lecture 

* Overview of smart watch program structure

#### Lab

- create State enum and state transistions

#### Lecture

* Heart rate rate sensor

#### Lecture

* Review heart rate sensor

#### Lab

* Program heart screen



## 13. Smart Watch + Accelerometer

### Reading

- 


### Assignment

- Due start of current week: nothing
- Continue working on project 

### Day 1

#### Lecture

* Smart Watch - Time

#### Lab

* how to work with the clock

#### Lecture

* Smart Watch - weather
* ==NB: If students used mustache templates with WeatherStack, the response template will need to be update==

```json
{"name":"{{location.name}}", "temperature":"{{current.temperature}}","description":"{{current.weather_descriptions.0}}","weather_code":"{{current.weather_code}}","uv_index":"{{current.uv_index}}"}
```

* NB 2: With threading enabled, `setup()` runs before cloud connectivity is enabled. In order to get the weather initially when Photon 2 turns on, we need to set a boolean flag and do a check in `loop()`
  * [Particle community post](https://community.particle.io/t/cant-particle-publish-in-setup-with-cpp-file/66688/3?u=rob7)




#### Lab

* Use weather API to display local weather (if time)

### Day 2 - ==Need more material here--consider adding sleep==

#### Activity

- ~~Check milestone~~ 

#### Lecture

- Accelerometer 

#### Lab

- Copy example code for display graphs (`Sparkfun_ADXL345_Graph.ino`)
- Use **tap** feature
- Use accelerometer to control RGB LED (if time)
- Try interrupts for tap 

## 14. RFID + ==Thanksgiving==

### Reading

- 
### Assignment

- Due start of current week: nothing
- Continue working on project 


### Day 1

#### Lecture

- RFID

#### Lab

- install library
- run example code `DumpInfo` to display ids from cards; have students store those as `String`
- Explain that we need to scan the card to compare, not print to Serial
- Show how to go to definition of `PICC_DumpToSerial`; copy the for loop code to sketch
- Ask students how to modify for storing in `String`
- Print out value; show need to upper case and trim space
- now ask them to check for authorization for one card or the other

### Day 2 ==Thanksgiving==

#### Lecture

- ==**Guest Lecture or work on project?**==


## 15. PIR + Guest Lecture?

### Reading

- 

### Assignment

- Due start of current week: nothing
- Continue working on project 
- 
### Day 1

#### Lecture

- PIR sensor

#### Lab

- Do basic wiring together
- ask students to enable longer delay-to-off time

#### Lecture

- ==Probably need more here==

### Day 2

#### Lecture

- ==Guest lecture?==
- Discuss [what happens after prototyping](https://docs.particle.io/tutorials/learn-more/beyond-prototpying/)
- Work on project 

#### Lab

- 



## 16 - Final Project Presentation	
