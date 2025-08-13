
## 		Things to implement

**Definite**

* [ ] week 8
  * [ ] Create bluetooth fan example could covered during bluetooth lecture
  * [ ] Maybe A9 blynk should change because it is hard and Rob thinks it is "fun"
* [ ] week 10
  * [ ] combine A8 and A10 (bluetooth car).
  * [ ] future semester: consider permanently putting motors here; add something else for week 9
* [x] wk9-11: consider timing of car assignment and in-class work. Students are building car so they build something else. Maybe JSON cloud work can be covered during that time

Week 10 idea: 

* [ ] Tues is ultra sonic sensor + project overview; show BRIEFLY how to load images
* [ ] Thurs is using JSON to send multiple values to Initial State; consider recording a video for json overview and moving early
* [ ] week 10 / 11: may need to record JSON videos for clarity
* [ ] week 10 / 11: may need to include a subscribe video or lectu

* [ ] consider moving A9 earlier to be closer to material (even if prelim proposal and A9 overlap)
* [ ] consider removing week 10 OLED graphics, replace with...? JSON, softpot, piezo motion sensor

---

**Maybe**

* [ ] TA recommendations

  * [ ] have small assignment where they layout PCB for a built project; then later in the semester the soldering workshop uses that design (talk to kristof about this so we don't step on 388)
  * [ ] submissions: 
    * [ ] make single zip for upload with code and fritzin
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

  * [ ] 
* [x] **Revise A5 reaction timer. Remove any need for a while loop**
* [ ] create ["cheat sheet"](https://education.github.com/git-cheat-sheet-education.pdf) or video about basic workbench operations (flash, create project, import library)
* [ ] 5v voltage regulator: [5V Step-Up Voltage Regulator U3V40F5](https://www.pololu.com/product/4012)
  * [ ] also [SparkFun Buck-Boost Converter]( https://www.sparkfun.com/products/15208)
* [ ] tell students not to unclaim device
* [ ] recruit guest lecturers (x2)

**Possible**

* [ ] use something other than Brightspace for submissions

* [ ] summary of info. 

  - Maybe a page of "tips" - cool work-around or example of something not completely covered in class. 
- Maybe a page of "oops" - mistakes to be avoided
  - Maybe a page of troubleshooting - there were a few tricky situations people posted on Piazza, a record of that would be cool
  - Maybe a page of ideas - problems to solve. Maybe something you and the TAs add, challenges of all levels for fun
  
  
  
  

**Videos and Wiring Diagrams Needed to Publish**

- [ ] Week 1
- - [ ] record software tools for reference
- [ ] Week 2
- - [ ] PWM (skip and leave for class)
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
  - [ ] record video to explain car ( no specifics but  pseudocode design for carForward, leftMotor, etc. (students will build  this for their)
  - [ ] Revise JSON in week 10. Try using ArduinoJSON instead of RK. The generation of RK is very tough. This would mean re-recording the parsing video to use ArduinoJSON
- [ ] Week 12
  - [ ] wk12: revise Brightspace project grading rubric (sensors and actuators worth 10 points each, remove UI)

## General Feedback (Spring 2021)

- [ ] Assignment 0 and 1 are given out week 1, day 1; due week 2, day 1; that is the pattern
- [ ] students like being show a small bit of using a sensor, and then extending it on their own
- [ ] students like hands-on

  

## Pre-semester

- [ ] Send students installation instructions / video
- [ ] purchase items (see Evernote pre-semester tasks)

- Reading
  - Enabling the Internet of Things https://web.eecs.umich.edu/~prabal/teaching/resources/eecs582/want15iot.pdf

## 1. Intro, Microcontrollers, LEDs

### Reading / Video

* [http://www.tigoe.com/pcomp/code/circuits/understanding-electricity/](http://www.tigoe.com/pcomp/code/circuits/understanding-electricity/)
  * [https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law/all](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law/all)

* Video discussion of C++ review (make little videos for functions); curate or record
* Have short Brightspace quiz

### Assignment

- Due start of current week: none
- Given out start of current week: A0 - Software and tool installation; A1 - Blink

### Day 1

#### Quote

* ==Students need to pick up kit from ITP office BEFORE Wed class==

- Making and the maker movement is the physical manifestation of all your academic learning - how you apply your education to real-world problems (*Dr. Dorothy Jones-Davis*)

#### Lecture

- Course introduction / syllabus
- Ice breaker *(see slides in local TAC 348 Docs folder)* 
- Introduction to IoT
- Kit Overview
- Possibly show this [mind map](https://www.mindmeister.com/1308604904?t=O0Vcty0Uys) from Boris Tomas
- ==Explain course website==
- Explain how to use envelopes
- Explain how to identify kit parts

#### Lecture

* C++ Syntax (optional at the end)

#### ~~Lab~~

- ~~Paper circuits~~
- ~~Time permitting~~
  - ~~(on ground) ask student to complete a creative expression with multiple LEDs~~
  - ~~(online) have student connect Argon to USB and connect an LED to 3.3v~~
  - ~~Walk students through connecting LED + Resistor to VUSB on Argon~~
    - ~~Ask students how they would connect more than 1 LEDs~~
    - ~~Ask students how they would make LEDs blink~~
  - ~~just ask the question: Compare 10k ohm vs 330 ohm resistor~~

### Day 2

#### Lecture

- Kits
   - students are responsible for returning devices if they drop before drop deadline
   - If online, students will already have these
- Safety
- Software tools
   - Workbench (open and discuss)
   - Fritzing (open and show example project)

#### Lecture

- Electricity and Ohm's Law
- LED (covered) and Digital output (moved to week 2 after argons are set up)

#### Lab

- turn on LED

#### ~~Lecture (Skipped in Spring 2021)~~

- ~~Look at LED datasheet; calculate ideal resistance for LED~~

#### ~~Activity (on ground)~~

- ~~Day 2 "making project" was fun; ping pong balls and glue guns were a hit~~

#### Feedback

- Most students were familiar with electricity principles, units (kilo, milli) so the electricity presentation very simple
- Online: skipped making project and did LED blink together

- Skipped all coding completely since students still didn't have kits with LEDs. Instead we assembled our Argons + antennas and wired an LED to 3.3v and ground



## 2. Pulse Width Modulation, ADC

### Reading

- Video: Software tools
  - Lecture: Open Workbench
    * IDE like PyCharm
    * Create project
    * explain folder structure
    * Walk through command palette
    * Login, Target project
  - Show students how to download and install fritzing parts

#### Assignment

- Due start of current week: A0 and A1 - Blink
- Given out start of current week: A2 - Light Sculpture (have students bring to class; ==bring camera==) 

### Day 1

#### Notes

- TA and I spent some time class helping install
- Demonstrate how to reset device and go to safe mode

#### Lecture

* Argon Microcontroller
* LED (covered week 1) and Digital output
* Start with LED example

#### Lab

* Have students work in pairs to answer datasheet questions from Argon Microcontroller slide

#### Lecture

- Analog vs. digital (video)
- Pulse width modulation (lecture, PWM pins, analogWrite)

#### Lab

- Make light fully bright for 2 sec, half as bright for 2 sec, 1/3 as bright for 2 sec, 
- Challenge: Increase light level of LED automatically

#### Lab

- Have students use for loop to sweep the brightness of an LED

#### Lecture

* C++ `for` loops (video)

#### Feedback

- spend time reviewing LEDs + resistors since we went quickly in previous week

### Day 2

#### Lecture

- Serial monitor

- Guided activity
- Do simple example where there is a global variable that gets incremented and display its value with Serial monitor

#### Lecture

- Potentiometer, voltage dividers (skip derivation)

#### Lab

- Have students connect pot to 3.3v, gnd, and A0; display the values on serial monitor

#### Lecture

- Analog to digital conversion; explain the math / conversion between voltage and input values

#### Lab

- Use potentiometer to control light level



## 3. Buttons, Digital Input, RGB

### Assignment

- Due start of current week: A2 - Light Sculpture 
- Given out start of current week: A3 - Cylon light 
### Reading

- https://learn.sparkfun.com/tutorials/pull-up-resistors
- https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all

### Day 1 ==Labor Day Holiday--maybe move RGB LED to next week with photoresistor?==

#### Guided activity

- Ask them to **digitalRead()** on D2; use serial monitor to read with no connection (will be floating); then directly connect to **3.3v**, then GND
- connect button with pullup
- Ask what is the voltage at pin when button pressed and not pressed

#### Lecture

- Digital Input (video)
- Push buttons: component, schematic, pull-up resistors (video)

#### Guided activity

* Fritzing explain
* Create button with resistors in Fritzing

#### Guided activity

- Connect button with resistor on Argon

#### Lab (students work on)

- Turn LED on while button pressed
- Turn LED off after button pressed
- Connect two LEDs

#### Guided activity

- Latching button (if time) **==identify way to program this==**
- Connect 3 LEDs and control on/off with button presses (3 states)

#### Lecture

- No slides for latch. Instead draw pictures with square wave

#### Feedback

- 

### Day 2

#### ~~Lecture (==skip Fall 2022==)~~

- ~~Switch (==skip Fall 2022==)~~
  * ~~connect middle pin to argon~~
  * ~~connect outer pins to power and ground~~
  * ~~when moving the switch, it connects either left two, or right two pins~~

#### ~~Guided activity (==skip Fall 2022==)~~

* ~~Connect switch middle pin to digital input pin, outer pin to power and ground~~
* ~~use serial monitor to display switch value~~

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

#### ~~Lecture  (==skip Fall 2022==)~~

- ~~Libraries~~

#### ~~Lab~~

- ~~Have students find and install `rgb-controls`~~
- ~~Ask them to create some colors effects on their own~~
- ~~Then walk through example together~~
- ~~If time, introduce a button to control states (idea of a state machine)~~

### Fall 2022 Holiday Plan

* Discuss scanning light assignment 
* Lecture: digital input
* Draw and discuss button
* Guided: Wire RGB and Button with this [image](https://reparke.github.io/TAC348-Making-Smart-Devices/lectures/week03/lecture_rgb_leds.assets/image-20210204155745432.png)
* Guided: make button turn on D7
* discuss RGB LED
* have students make RGB LED turn on white when pressed only
* Have students press show red for 1/2 sec, green for 1/2 sec, blue for 1/2 sec, then orange for 1/2 sec
* show toggle
* show random and have button press be random (if time)
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

#### Lab

* Calibrate photoresistor

#### ~~Lecture (skip)~~

- ~~(if time) show derivation of mathematically deriving exact resistor to calibrate. Explain this is an important part of engineering~~

#### Lecture

- Particle Cloud Publish

#### Lab

- publish photoresistor value and "state" (for example bright, ambient, or dark to Particle cloud)

#### ~~Lecture~~

- ~~Reading resistors (we had time in Fall 2021)~~

### Feedback

* Started with review
* This was a good amount of material; we had time to introduce functions to use RGB

### Day 2

#### Lecture

* ==Announce Brightspace quiz during week 6 (ask for feedback if it should be on the weekend or after monday)==
* ==Announce survey==

- Show students wiring picture (two buttons and an LED); give them 5 minutes to connect
- Multitasking with millis

#### Guided Activity

- Start: Blink one LED on and off, display serial message when button presed
- Walk through blocking example with button
- Demostrate millis example with one light blinking

#### Lab

- Use delay to register button press (without toggle) and blink **LED1** 
- Use `millis()` to fix blocking in #1 (we'll do #1 and #2 together)
- Enable toggle button to turn **LED2** on and off on the **rising edge**
- Track number of button presses and use `millis()` to publish number of button presses every **1000 ms**

#### Feedback

- 

#### ~~Lecture~~

* ~~If time, cover multimeter or reading resistors or switches~~



## 5. TMP36, OLED

### Assignment

- Due start of current week: A4 - Electronic dice 
- Given out start of current week: A5 - Reaction Timer
- Alternate ideas: use TMP36 to measure temperature and display colors on RGB LED. Use potentiometer to control brightness of RGB LED. Display results on serial monitor. **Optional** use button for diagnostic or to change cel/fahr 


### Day 1

#### Lecture

- ==Announce Brightspace quiz during week 6 (ask for feedback if it should be on the weekend or after monday)==\
- ==Announce survey==
- ==Remind students about extra credit for posting on social issues==
- Quiz is open Thurs 2/18 after class (6 pm PST) until Monday 2/22 at 11:59 pm PST. Once you start it, you will have 60 minutes but it might take you 15 min.
- TMP36

#### Lab (in slides)

* Connect a TMP36 and output the current temperature to the serial monitor
* Consider what type of input is this signal? How will this value be read by Argon

#### Lecture

- APIs and webhooks
- Data visualization for single values (stop before slide 7 and do the demo live)

#### Guided Activity

- Create InitialState account
- Create webhook in Particle
- Send TMP36 value`Particle.publish` to InitialState

- Use Initial state to send temperature data

### Day 2

#### Lecture

- Libraries
- Discuss OLED

#### Lab

- Have students connect OLED to display "Hello World"

#### Guided Activity

- Walk students through wiring

#### Lab

- Have students create an Etch-A-Sketch with OLED

### Feedback

* This took longer than expected since there was much debugging needed. We finished basic setup of OLED but didn't have time to introduce lab for etch-a-sketch


## 6. Magnetic Switch; Blynk

#### Assignment

- Due start of current week: A5 - Button Timer
- Given out start of current week:  A6 - Preliminary Proposal Idea

### Reading

- Have students create an [Blynk](https://blynk.io/) account
- Have students come to class with RGB LED with magnetic switch (Tues) and again for (thurs)

### Day 1

#### Lecture

- Magnetic switch (video)

#### Lab

- Wire switch and RGB LED
- Publish switch event in console (this won't take very long)

  - create unique event TAC348/Door/<<UNIQUE_NAME>>
- Create function to change LED colors: white switch is closed, red switch is open

#### Lecture

- ​	Start Blynk

#### Guided activity

- Note: Blynk template "Week 6 Lab" can be used for exercise and lab. Use following pins
  - On board LED - **V5**
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



## 7. Finite State Machines 

### Reading

- ==Send wiring diagrams out ahead of time==
- ==**Try to start Sound earlier due to fall break**==


### Assignment

- Due start of current week:   A6 - Preliminary Proposal Ideas
- Given out start of current week: A7 - Shared environment monitor



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

  - add state duration
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


## 8. Sound, Motors, Servos

### Reading

- Motors
  - [https://www.electronicproducts.com/Electromechanical_Components/Motors_and_Controllers/Motor_control_design_an_introduction_to_motors_and_controllers.aspx](https://www.electronicproducts.com/Electromechanical_Components/Motors_and_Controllers/Motor_control_design_an_introduction_to_motors_and_controllers.aspx)

### Assignment

- Due start of current week:   A7 - Shared environment monitor
- Given out start of current week: A8 - Tea State Machine with Blynk (due in two weeks)


### Day 1

#### Lecture

* Speaker
* Tone
* Pitches

### Day 2 ==Fall Break==

Have students build fan and circuit before class

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

#### Feedback

- students followed remotely and enjoyed building the fan
- I skipped the separate servo part and went directly to using the servo to control the fan
- ==**Idea for next semester**==: create assignment using motors and bluetooth (something like the fan)


## 9. Bluetooth and Motors

- ==idea: Day 1 covers motors by directly building fan with potentiometer; Day 2 cover bluetooth and control can with bluetooth==

### Idea / Feedback

* for Fall 2022, wk 8 day 2 was canceled. For w8d1, we covered sound and rushed explaining bluetooth. Everyone got their device connected to Bluefruit, but that was it. This may not have been helpful
* Wk9d1, we covered motors and servos, and built the fan
* w9d2, we reintroduced bluetooth. Start with blinking D7 on and off, then go 

### Assignment

* Due start of current week: none
* Given out start of current week: none, but continue to work on  A8 - Timer with Blynk 

### Before class

- Send wiring guide with full fan circuit 
- ask students to have a narrow bottle of water and some tape
- Have students install Bluetooth phone apps
  - [Adafruit Bluefruit](https://learn.adafruit.com/bluefruit-le-connect)
  - [Nordic Semiconductor nRF Toolbox](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Toolbox)

### Reading

- Bluetooth
  * [https://learn.sparkfun.com/tutorials/bluetooth-basics/all](https://learn.sparkfun.com/tutorials/bluetooth-basics/all)
  * [https://learn.adafruit.com/introduction-to-bluetooth-low-energy/](https://learn.adafruit.com/introduction-to-bluetooth-low-energy/)

### Day 1

#### Lecture

- Bluetooth
- Argon BLE syntax
- Show Bluefruit app (skip nRF Toolbox)

#### Lab - ble_uart_control_start

- Distribute github link to download (post on slides)
- Describe project goals
- Explain **argon_ble_setup.h** at a high level
  - Have students change **DEVICE_NAME**
- Pull up Bluefruit [documentation](https://learn.adafruit.com/bluefruit-le-connect/controller) and explain button signal
- Code together blinking D7 when **press 1**
- Have students code on their own D7 on with **press up** and D7 off when **release up**
- (If time) have students code play tone when **press right **
- Have students try using color picker to change RGB colors

#### Lab - ble_uart_control_start

- Have students try to control servo and fan motor on their own

#### Example - ble_uart_rgb_accel_example

<!--skip for time -->

- Distribute github link to download (post on slides)
- Describe project goals
- explain **onDataReceived()**
- explain **updateRGBvalues()**
- explain **changeRgbLight()**
- Demo device with code

### Day 2

#### Lecture

- LIPO battery

#### Lecture

- 

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
- InitialState integration (multiple values)

#### Lab

* Send photoresistor value and light level threshold`Particle.publish` to InitialState

#### Lab

- As review, we spent the entire class period reviewing how to send data to initial stack
- Students worked in breakout rooms to create webhook and send GPS and a battery value to initial state
- This took the entire class period

### Day 2

#### Lecture / Lab

- Finish InitialState Integration (if necessary)

#### Lecture

- JSON Parsing (video with JSONParserGeneratorRK)
- Retrieving JSON from API (video)
- Have students use [https://api.sunrise-sunset.org](https://api.sunrise-sunset.org) to determine sunrise and sunset time based on lat and long (*no API key required)*)
- Discuss [weather stack](https://weatherstack.com/) show example call
- Walkthrough integration
- Write json code together

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

### Day 2

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

- Create blank project and install library `SparkFun-MAX3010x`
- Demonstrate heart rate function

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

#### Lab

* Use weather API to display local weather (if time)

### Day 2

#### Activity

- Check milestone 

#### Lecture

- Accelerometer 

#### Lab

- Copy example code for display graphs
- Use **tap** feature
- Use accelerometer to control RGB LED (if time)
- Try interrupts for tap 

## 14. RFID + Thanksgiving

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
