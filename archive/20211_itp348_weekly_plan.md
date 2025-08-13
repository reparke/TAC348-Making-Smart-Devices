## 		Things to implement

* [ ] Improvements
  * [ ] add late days column to Brightspace
  * [ ] create ["cheat sheet"](https://education.github.com/git-cheat-sheet-education.pdf) or video about basic workbench operations (flash, create project, import library)
  * [ ] tell students not to unclaim device
  * [ ] distribute grading among TAs
  * [ ] have TAs not attend every class
  * [ ] create better rubric for assignments by breaking down things like "game logic" to be more explicit so students can go down the checklist [like this](https://bytes.usc.edu/files/ee109/labs/lab4v/Lab4_Checkoff.pdf)
  * [ ] use something other than Brightspace for submissions
  * [ ] give list of items students should include in videos each week
  * [ ] summary of info. Things like what do wires do I connect to what pins for <whatever sensor> or  what is the generic formula for button-pushing detection? "living document". Whether that's a required part of assignments or a group doc different students add to each week, I've found that when students have to be accountable for something beyond their own notes, we tend to put  effort into it.
* [ ] need to order
  * [x] trimpots
  * [x] microservos
  * [x] microoled
  * [ ] particle argons
  * [ ] kit components for fall
* [ ] change kit: replace SPI OLED with [I2C OLED](https://www.sparkfun.com/products/14532)
* [ ] revise proposal: give a format template to include exactly how their devices meet the requirements
* [x] recruit guest lecturers (x2)
* [ ] wk6: subscribe doesn't work with public events anymore :( so revise or eliminate partner magnetic switch example (summer)
* [ ] wk9-11: consider timing of car assignment and in-class work. Students are building car so they build something else. Maybe JSON cloud work can be covered during that time
* [ ] Re-evaluate Blynk--this seems to trigger lots of device disconnections
* [ ] Re-evaluate timer assignment--this caused significant device disconnection issues due to while loops
* [x] wk 0: create social issue assignment
* [x] wk 0: Create "behavioral norms"
* [ ] wk1: record software tools for reference
* [x] wk1: record c++ review and create bb quiz
* [x] wk3: create latch slides
* [ ] wk3: change die assignment to explicitly suggest on array for the pin labels, and multiple array for the dice labels (Summer) 
* [x] wk4: revise photoresistor slides / change questions
* [x] wk5: revise dashboard slides and exercise to reflect sending SINGLE values
* [x] wk 5: announce quiz for following week
* [ ] wk 5: use millis in next assignment (summer)
* [ ] wk 5: move enum and switch videos to week 6 (summer)
* [x] wk 6: create Bb quiz
* [x] wk5: add API graphic illustration for webhook
* [x] wk5: revise lab and slides to show TMP36, not photoresistor
* [x] wk6: revise Blynk lab
* [x] wk7: create lecture / lab activities for FSM day 2
* [x] wk8: revise alarm clock assignment to use FSM **and** Blynk (for blynk, use either simple buttons or "time input" to set alarm time)
* [x] wk11: may be too much dashboard content; consider moving single data point for initial state to earlier week
* [ ] wk10: review initial state code. need if JSON needs to be covered first
* [ ] wk11: inquire about future class TAs and kit TA
* [ ] wk12: revise Brightspace project grading rubric (sensors and actuators worth 10 points each, remove UI)
* [x] general: try to incorporate `enum` or `switch` earlier in semester
* [x] wk11: building smart watch: need to text and pictures to use velcro
* [x] account for wellness days in schedule
* [x] account for extra two weeks in schedule
* [x] replace IFTTT with Blynk

## **Videos and Wiring Diagrams Needed to Publish**

- [x] Week 1
- - [x] C++ syntax
- [x] Week 2
- - [ ] PWM (skip and leave for class)
  - [x] Analog input
  - [x] Potentiometers
- [x] Week 3
- - [x] Buttons 
  - [x] Digital input (?)
  - [x] RGB LEDS
- [ ] Week 4
- - [ ] Multi-tasking
  - [x] Photoresistor
  - [x] Cloud Overview 
  - [ ] Publish (skip)
- [ ] Week 5
- - [x] OLED
  - [x] TMP36
  - [ ] Webhooks / APIs (Initial State can be live)
- [ ] Week 6
- - [ ] Blynk
  - [x] magnetic switch
  - [x] cloud subscribe

- [x] Week 7
  - [x] Switch / enum
  - [x] State machines

- [ ] Week 8
- - [x] Sound
	- [ ] Motors

- [x] Week 9
- - [x] Bluetooth
  - [x] LiPo batteries
  - [x] Ultrasonic sensor (in case we have time)

- [x] Week 10
  - [x] Ultrasonic sensor (again in case)

- [ ] Week 11
  - [x] OLED graphics
  - [ ] JSON / APIs (need to re-record)
  
- [x] Week 12
  - [x] Debouncing
  - [x] Heart rate sensors

- [x] Week 13
  - [x] RFID

- [ ] Week 14
  - [ ] Accelerometer

- [x] Week 15
  - [x] PIR

## General Feedback (Spring 2021)

- [ ] Assignment 0 and 1 are given out week 1, day 1; due week 2, day 1; that is the pattern
- [x] Develop a way to post readings on website
- [x] Try to integrate lectures, readings, assignments all on one webpage under "weeks"
- [ ] students like being show a small bit of using a sensor, and then extending it on their own
- [ ] students like hands-on

  

## Pre-semester

- [ ] Send students installation instructions / video
- [x] purchase items (see Evernote pre-semester tasks)

- Reading
  - Enabling the Internet of Things https://web.eecs.umich.edu/~prabal/teaching/resources/eecs582/want15iot.pdf

## 1. Intro, Microcontrollers, LEDs

### Reading / Video

* [http://www.tigoe.com/pcomp/code/circuits/understanding-electricity/](http://www.tigoe.com/pcomp/code/circuits/understanding-electricity/)
* [https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law/all](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law/all)
* Video discussion of C++ review (make little videos for functions); curate or record
* Have short Brightspace quiz

### Day 1

#### Quote

- Making and the maker movement is the physical manifestation of all your academic learning - how you apply your education to real-world problems (*Dr. Dorothy Jones-Davis*)

#### Lecture

- Course introduction / syllabus
- Ice breaker *(see slides in local TAC 348 Docs folder)* 
- Introduction to IoT
- Kit Overview
- Possibly show this [mind map](https://www.mindmeister.com/1308604904?t=O0Vcty0Uys) from Boris Tomas
- Safety
- Explain course website

#### Lab

- Paper circuits
- Time permitting
  - (on ground) ask student to complete a creative expression with multiple LEDs
  - (online) have student connect Argon to USB and connect an LED to 3.3v
  - Walk students through connecting LED + Resistor to VUSB on Argon
    - Ask students how they would connect more than 1 LEDs
    - Ask students how they would make LEDs blink
  - just ask the question: Compare 10k ohm vs 330 ohm resistor

### Day 2

#### Lecture

- Pass out argons 
   - students are responsible for returning devices if they drop before drop deadline
   - If online, students will already have these
- Software tools
   - Workbench (open and discuss)
   - Fritzing (open and show example project)

#### Lecture

* C++ Syntax (skip)

#### Lecture

- Electricity and Ohm's Law
- Argon program structure
- LED and Digital output

#### Lab

- turn on LED

#### Lecture (Skipped in Spring 2021)

- Look at LED datasheet; calculate ideal resistance for LED

#### Activity (on ground)

- Day 2 "making project" was fun; ping pong balls and glue guns were a hit

#### Feedback

- Most students were familiar with electricity principles, units (kilo, milli) so the electricity presentation very simple
- Online: skipped making project and did LED blink together

- Skipped all coding completely since students still didn't have kits with LEDs. Instead we assembled our Argons + antennas and wired an LED to 3.3v and ground

### Assignment

- Due start of current week: none
- Given out start of current week: A0 - Software and tool installation; A1 - Blink

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

### Day 1

#### Notes

- TA and I spent some time class helping install
- Demonstrate how to reset device and go to safe mode

#### Lecture

* Argon Microcontroller

#### Lab

* Have students work in pairs to answer datasheet questions from Argon Microcontroller slide

#### Lecture

- Analog vs. digital (video)
- Pulse width modulation (lecture, PWM pins, analogWrite 

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

- Potentiometer, voltage dividers

#### Lab

- Have students connect pot to 3.3v, gnd, and A0; display the values on serial monitor

#### Lecture

- Analog to digital conversion; explain the math / conversion between voltage and input values

#### Lab

- Use potentiometer to control light level

#### Lecture

- Using multimeter (if time)

#### Lab

- Have students measure resistance of pot when its out of a circuit

- Show fritzing drawing, and have them measure voltage

#### Feedback

- didn't have time for pot to control LED with PWM

#### Assignment

- Due start of current week: A0 and A1 - Blink
- Given out start of current week: A2 - Light Sculpture (have students bring to class; ==bring camera==) 

## 3. Buttons, Digital Input, RGB

### Reading

- https://learn.sparkfun.com/tutorials/pull-up-resistors
- https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all

### Day 1

- ==Have students present light sculpture== Start class with presentations

#### Guided activity

- Ask them to **digitalRead()** on D2; use serial monitor to read with no connection (will be floating); then directly connect to **3.3v**, then GND
- connect button with pullup
- Ask what is the voltage at pin when button pressed and not pressed

#### Lecture

- Using multimeter

#### Lab

- Have students measure resistance of pot when its out of a circuit
- Show fritzing drawing, and have them measure voltage

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

#### Lecture (==if time==)

- Reading resistors (lab exercise is built into slides)

#### Feedback

- 

### Day 2

#### Lecture

- Switch
  * connect middle pin to argon
  * connect outer pins to power and ground
  * when moving the switch, it connects either left two, or right two pins

#### Guided activity

* Connect switch middle pin to digital input pin, outer pin to power and ground
* use serial monitor to display switch value

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

#### Lecture

- Libraries

#### Lab

- Have students find and install `rgb-controls`
- Ask them to create some colors effects on their own
- Then walk through example together
- If time, introduce a button to control states (idea of a state machine)


#### Feedback

### Assignment

- Due start of current week: A2 - Light Sculpture 
- Given out start of current week: A3 - Cylon light 

### Feedback 

- overall worked well but over zoom, we didn't have time for **libraries or functions or switch or multimeters**

## 4. Photoresistors, Multitasking

### Reading

* [Kirchoff's Voltage Law](https://www.khanacademy.org/science/ap-physics-1/ap-circuits-topic/kirchhoffs-loop-rule-ap/v/ee-kirchhoffs-voltage-law)

### Day 1

#### 2021 Spring Idea

* modify photoresistor lab to remove handout exploration, and make it a group lab that also reviews some elements from prior weeks
  * buttons, RGB LEDs, LEDs, potentiometers / ADC, PWM
* ==Consider covering functions and libraries on Day 1, and leaving publishing for day 2==

#### Lecture

* Photoresistor (video)

#### Lab

* Calibrate photoresistor

#### Lecture (skip)

- (if time) show derivation of mathematically deriving exact resistor to calibrate. Explain this is an important part of engineering

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

- Show students wiring picture (two buttons and an LED); give them 5 minutes to connect
- Multitasking with millis. 

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

- fall 2020: students seemed VERY confused about millis() and delay

#### Lecture

* If time, cover multimeter or reading resistors

### Assignment

- Due start of current week: A3 - Cylon light 
- Given out start of current week: A4 - Electronic dice

## 5. TMP36, OLED

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

### Assignment

- Due start of current week: A4 - Electronic dice 
- Given out start of current week: A5 - Reaction Timer
- ==Consider revising Reaction Timer to something involving millis()==
- Alternate ideas: use TMP36 to measure temperature and display colors on RGB LED. Use potentiometer to control brightness of RGB LED. Display results on serial monitor. **Optional** use button for diagnostic or to change cel/fahr 

## 6. Particle Cloud Subscribe; Blynk

### Reading

- Have students create an [Blynk](https://blynk.io/) account
- Have students come to class with RGB LED wired (Tues) and then add magnetic switch (thurs)

### Day 1

#### Lecture

- Magnetic switch (video)

* Particle Cloud: Subscribe (video)

#### Guided Activity

* See subscribe notes for "Exercise"
* Rob publishes event that triggers their RGB LED

#### Lecture

* Switch and enum
* Rewrite above code with switch and enum

#### Lab part 1

- Wire switch and RGB LED
- Publish switch event in console (this won't take very long)

#### Lab part 2

* Create function to change LED colors: white switch is closed, red switch is open
* subscribe to variable -- work in pairs 
  - create unique event TAC348/Door/<<UNIQUE_NAME>>

## Feedback

- Going through project and publishing lab took most of the time

### Day 2

#### Lecture

* Fall 2020
  - take time to review questions, OLED, particle functions
  - have students brainstorm project ideas
* Review some pasts projects for preliminary project idea
  - https://robparke.com/tag/itp348_projects/
  - https://5cf99969afabc800087c618c.onlosant.com/photon_temperature
  - https://iot.app.initialstate.com/#/tiles/bkt_13hhui7kc4h38hz

#### Lecture

- Blynk

#### Guided activity

- set up Blynk
- Install iOS / Android app
- Demonstrate basic Blynk integration
- **Ask students to work in pairs and come up with a cool idea**

#### Lab

- Using RGB and switch, use app to control RGB color and get notification for switch

#### Lecture

* ==may need more here==

#### Feedback

#### Assignment

- Due start of current week: A5 - Reaction Timer
  - Warn students that it was time consuming
  - **==IDEA==** make reaction timer a state machine assignment and move forward (replace other assignment)
- Given out start of current week:  A6 - Preliminary Proposal Ideas
  - This seems early for this, but the semester is shortened by 2 weeks
  - Could consider moving this later in a future semester

## 7. Finite State Machines 

### Reading

- ==Send wiring diagrams out ahead of time==

### Day 1

#### Lecture

- Finish Blynk overview
- Discuss state machines

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

### Day 2

#### Lecture

- Finite state machines (video)

#### Lab

- Starting with sample code
- walk through NS light state transitions (length, state)
- use delay() (not `millis`)

### Feedback

- next day cover `millis`, then rest of light blinking
- some students enjoyed the complexity of all parts, other seemed bored

## Feedback

- 

### Assignment

- Due start of current week:   A6 - Preliminary Proposal Ideas
- Given out start of current week: A7 - Shared environment monitor



## 8. Motors, Servos

### Reading

- Motors
  - [https://www.electronicproducts.com/Electromechanical_Components/Motors_and_Controllers/Motor_control_design_an_introduction_to_motors_and_controllers.aspx](https://www.electronicproducts.com/Electromechanical_Components/Motors_and_Controllers/Motor_control_design_an_introduction_to_motors_and_controllers.aspx)

### Day 1

#### Lecture

* Speaker
* Tone
* Pitches

### Day 2

#### Lecture

- DC Motors

#### Lab

- Connect motor to 3v3

#### Lecture

- Servo motors

#### Lab

- Connect servo to DC motor
- control fan speed and direction with a potentiometers (do one version where it controls rotation of servo, then one where it controls motor speed)

#### Feedback

- students followed remotely and enjoyed building the fan
- I skipped the separate servo part and went directly to using the servo to control the fan
- Next year, start with DC fan, then immediately wire servo to spin, then pot
- ==Need to change the DC motor slides. They are too technical==
- ==**Idea for next semester**==: create assignment using motors and bluetooth (something like the fan)

### Assignment

- Due start of current week:   A7 - Shared environment monitor
- Given out start of current week: A8 - Bluetooth car part 1 (due in one week)
- Given out start of current week: ==A9 - Timer with Blynk (due in two weeks)==

## 9. Bluetooth

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

### Day

#### Lecture

- LIPO battery

#### Lecture

- car bluetooth - gave overview of coding -- no specifics but  pseudocode design for carForward, leftMotor, etc. (students will build  this for their)

#### Lecture

- ==**Consider moving ultrasonic sensor for extra time**==

### Feedback

### Assignment

* Due start of current week: A8 - Bluetooth car part 1 (due in one week)
* Given out start of current week: none, but continue to work on  A9 - Timer with Blynk 



## 10. Ultrasonic Distance Sensor; OLED Graphics

### Reading

- 

### Day 1 ==**Wellness day**==

### Day 2

#### Lecture

- project overview
- Ultrasonic distance sensor 
- OLED graphics

#### Lab

- Student design range finding with ultrasonic sensor. Provide starting project (same one that uses OLED later)

### Feedback Day 1

- Went generally well. Ran out of time to talk about graphics.

### Assignment

- Due start of current week: A9 - Timer with Blynk
- Given out start of current week: A10 - Bluetooth car part 2
- Given out start of current week: A11 - Smart Watch Assembly



## 11. Cloud Dashboards; APIs; Weather;  (==**This may be too much content**==)

### Reading

- Create [Initial State](https://www.initialstate.com/) account
- Create [Weather Stack account](https://weatherstack.com/)

### Day 1

#### Lecture

- JSON overview
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

- JSON Parsing
- Discuss [weather stack](https://weatherstack.com/) show example call
- Walkthrough integration
- Write json code together

#### Lab

- Create [weather stack](https://weatherstack.com/) account (hopefully they have already done this)
- Have them use their own API key to view JSON in a browser (use formatter online if necessary
- Create webhook in Particle
- Copy code from particle publishing and subscribing
- Test: publish request and see if subscribe code retrieves JSON data

- Show students an example of how the code works for JSON parser

- Have students show description, temp, location, rainfall

#### Idea

- find another API to show
- Show students how to use GPS coordinates

### Assignment

- Due start of current week: A10 - Bluetooth car part 2
- Due start of current week: A11 - Smart Watch Assembly
- Given out start of current week: Proposal

## 12. Smart Watch, Heart Rate Sensor

### Reading

- 

### Day 1

#### Activity

* Alternative idea: ==**project discussion**==
* Depending on time, have class meet in a large group or in 3 person groups
* Each person describes their proposal (==need to develop some framework and questions audience can ask== )
* Consider covering debouncing by itself today, then talking about project as a class

#### Lecture 

* Overview of smart watch program structure
* Debouncing

#### Lab

- create State enum and state transistions
- set up debouncing

#### Lecture

* Heart rate rate sensor

### Day 2

#### Lecture

* Review debouncing
* Review heart rate sensor

#### Lab

* Program heart screen

#### Lecture

* Time

#### Lab

* how to work with the clock

#### Lecture

* Connect to weather

### Assignment

- Due start of current week: Proposal
- Continue working on project 

## 13. Accelerometer + RFID

### Reading

- 

### Day 1

#### Lecture

- Accelerometer 

#### Lab

- Do basic wiring together
- ask students to enable longer delay-to-off time

### Day 2

#### Activity

- Check milestone 

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

### Assignment

- Due start of current week: nothing
- Continue working on project 

## 14. Guest Lecture + Wellness Day

### Reading

- 

### Day 1

#### Lecture

- ==**Google Guest Lecture on Accessibility**== 

### Day 2

#### Lecture

- **==WELLNESS DAY==**

### Assignment

- Due start of current week: nothing
- Continue working on project 

## 15. PIR, DHT

### Reading

- 

### Day 1

#### Lecture

- PIR sensor

#### Lab

- Do basic wiring together
- ask students to enable longer delay-to-off time

#### Lecture

- accelerometer

#### Lab

- Copy example code for display graphs
- Use **tap** feature
- Use **portrait / landscape** detection
- Use accelerometer to control RGB LED (if time)

### Day 2

#### Lecture

- Discuss [what happens after prototyping](https://docs.particle.io/tutorials/learn-more/beyond-prototpying/)
- Work on project 
- DHT 22

#### Lab

- Use **tap** feature
- Use **portrait / landscape** detection
- Use accelerometer to control RGB LED

### Assignment

- Due start of current week: nothing
- Continue working on project 

## 16 - Final Project Presentation



---

# **Use when extra time**

## Week 5

#### Lecture

- Particle Cloud functions

#### Lab

- Connect RGB LED and have students remotely control it

#### Lecture

* Consider covering `switch` to handle cloud function calls

## Week 5 - Photoresistor

#### Experiential Learning

- Photoresistor part 1
- Discuss
- Photoresistor part 2
- Discuss
- Photoresistor part 3
- Discuss and show code

#### Feedback

- some students enjoyed the exploration; others seemed a little lost
- change some things on the handout that were worded poorly
- create some short, simple photoresistor wiring notes
- One good thing was this followed learning about using the multimeter since the activity required it

## Week 8 - Soldering

### Day 1

#### Lab

* Soldering demo in EE lab
* had students build sparkfun flashlight
* Then Neftali did a quick demo of how to lay out a simple PCB in Fritzing

### Feedback

* Took about 1 hour
* soldering was fun but really simple. It would be cool to have a second, more complex circuit

## Losant part 1

### Day 2

#### Lecture

- Losant

#### Lab (together)

- Create application
- Create devices
- Create integrations
- Create workflows

## Losant part 2 + Rate

### Day 1

#### Activity

- Race competition

#### Lecture

- Losant

#### Lab

- Review workflow (make sure everyone is getting data in device by going to overview)
- Create dashboard
- Create web application

### Feedback

- make sure to set up voting ahead of time for best customization for voting
- [Create bracket online](https://challonge.com/tournament/bracket_generator)

### Day 2

#### Lecture

- Discuss controlling devices from Losant

#### Lab

- Revise firmware and Losant environment to support input controls (blink light on / off)

### Assignment

- Due start of current week: A10 - Bluetooth car 
- Given out start of current week: 

---



# **Skipped / Eliminated**

## BLE Health Service

- The goal was to send a temperature from Argon to Bluefruit app but it rarely worked

#### Lab - ble_health_temp_start

- Distribute github link to download (post on slides)
- Describe project goals
- Explain **argon_ble_setup.h** at a high level
  - Have students change **DEVICE_NAME**
- Draw picture of how temperature data is organized
  - 6 bytes total
  - byte 1: 8 bits of flags
  - bytes 2-5: 4 byte floating point number
  - byte 6: temperature type
- Define constants and globals
  - UPDATE_INTERVAL_MS
  - prevUpdate = 0;  // time of last update in millis()
  - float prevTempF = -1.0;        // previous temperature in Fahr
  - uint8_t batteryLevel = -1;     // battery level percentage [0-100]
- Write **loop()** together
- Write **getTemp()** together
  - Call       **update_ble_temperature**
- Write **getBatteryLevel()** together
  - call update_ble_battery_level



## LCD screen

#### Lecture

- I2C LCD
- Ultrasonic distance sensor

#### Lab

- exercises in slides

### Feedback

- Fail.
- The LCD devices only worked for half the students (either faulty devices or bad libraries). Definitely DO NOT use LCDs again
- Ultrasonic sensor worked mostly

## ThingSpeak 

### Day 2

### Lecture

- OLED graphics
- walk through of Thingspeak (==need to make slides==)
  - Create webhook in Particle
  - send temperature data through `Particle.publish` to thingspeak

### Feedback day1

- Recommend **NOT** using thingsspeak again. Thingspeak integration with webhook is fairly simple. It is also possible to discuss JSON to send multiple values.
- However, thingsspeak doesn't have a way to send commands to Argon (have to use something like IFTTT)

### Assignment

- Due start of current week: A8 - Alarm clock
- Given out start of current week: ==A9 - Bluetooth car== part 1 (build chassis only)

### Day 1 (following week)

#### Lecture

- Finish ThingSpeak integration with multiple values as JSON

#### Lab

- Finish ThingSpeak integration with multiple values as JSON walk through example

#### Lecture

- Explain what APIs are; show them a few public ones
- Discuss [weather stack](https://weatherstack.com/) show example call
- show JSON slides
- walkthrough integration
- write json code together

#### Lab

- Create [weather stack](https://weatherstack.com/) account
- Have them use their own api key to view JSON in a browser (use formatter online if necessary
- Create webhook in Particle
- Copy code from particle publishing and subscribing
- Test: publish request and see if subscribe code retrieves JSON data

## IFTTT

#### Lecture

- IFTTT

#### Guided activity

- set up IFTTT [https://ifttt.com/create](https://ifttt.com/create)
- Install iOS / Android app
- how do create an alarm?
  - If Particle - Publish <event name> open
  - Then send notification
  - Could enhance by using your location
  - set up location trigger to enter or exit that sets a variable
  - then change publish event
- Create button
- **Ask students to work in pairs and come up with a cool idea**

#### Lecture

* ==may need more here==
* Also could work on reaction timer because it is challenging
* Could cover [IFTTT webhooks](https://ifttt.com/maker_webhooks) but they require HTML / JS editing to work, and they require JSON to send text values

#### Feedback

- Some of the IFTTT got a little bumpy but generally this was a good amount of material and worked well