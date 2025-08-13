#### General Feedback

* Assignment 0 is given out week 1, day 1; due week 2, day 2; that is the pattern
* change A1 blink so that it gives out code to make D7 blink, or change the name of the assignment to something like **initial project**
* Develop a way to post readings on website
* Try to integrate lectures, readings, assignments all on one webpage under "weeks"
* Add to Assignment 0 how to install fritzing parts for Argon (from Rob github)
* students like being show a small bit of using a sensor, and then extending it on their own
* students like hands-on
* order
  * more LED colorsz
  * more M-F extension wires
  * 3M "plastic" velcro
* student kit could include more variety of colors / shapes of LED
* Include finite state machines; then assignment of simon says (could use buzzer)
* Include Fritzing installation of parts in A0 installation (beware Mac issues; for windows show how to import FZBZ file since students won't be able to double click )
* Week 11: move Losant up sooner
* Add "pre-proposal" to earlier in the semester
* Add class period (half?) for students to give feedback on proposal idea
* teach binary / decimal / hex conversion (briefly); useful for I2C addresses
* notes on motors: [https://www.electronicproducts.com/Electromechanical_Components/Motors_and_Controllers/Motor_control_design_an_introduction_to_motors_and_controllers.aspx](https://www.electronicproducts.com/Electromechanical_Components/Motors_and_Controllers/Motor_control_design_an_introduction_to_motors_and_controllers.aspx)

0. #### Pre-semester

   - [x] Send students installation instructions
   - [ ] Create Google slides presentations; ask students to create one intro slide
   - [x] purchase:
     - [x] small envelopes
     - [x] coin batteries
     - [x] paper circuits classroom kit
     - [x] construction paper
     - [x] conductive tape
     - [x] colored straws

1. #### Introduction

   - Reading
     - Enabling the Internet of Things https://web.eecs.umich.edu/~prabal/teaching/resources/eecs582/want15iot.pdf
- Day 1 
  - Lecture
    - Course introduction / syllabus
    - Student intro slides 
    - Ice breaker
    - Introduction to IoT
    - Possibly show this [mind map](https://www.mindmeister.com/1308604904?t=O0Vcty0Uys) from Boris Tomas
  - Lab
    - none
- Day 2
  
  - Lecture
  
    - Pass out argons
       - students are responsible for returning devices if they drop before drop deadline
       - Have students sign
    - Kit Overview
    - Software tools
       - Workbench (open and discuss)
       - Fritzing (open and show example project)
    - Safety
    - ==*Explain with slides what particle does, cloud, flash, etc. -- skip and do later==
   - Lab
     
     - Paper circuits
     - Then ask student to complete a creative expression with multiple LEDs
  - Assignment
    - A0 - Software and tool installation
  - ==Feedback==
    - update A1 to include code to make D7 blink (not available default)
    - Day 2 "making project" was fun; ping pong balls and glue guns were a hit
  

2. #### Electricity, Microcontrollers, LEDs
   
   - Reading
     - http://www.tigoe.com/pcomp/code/circuits/understanding-electricity/
     - https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law/all
   - Day 1
     - Lecture (fall 2019)
       - ==I walked through claiming a device== 
     - Lecture
       * C++ Syntax
       * Argon Microcontroller
     - Lab
       * Have students work in pairs to answer datasheet questions
     - Lecture
       - Electricity and Ohm's Law
     - Lab
       - Walk students through connecting LED + Resistor to VUSB on Argon
         - Ask students how they would connect more than 1 LEDs
         - Ask students how they would make LEDs blink
       - ==Feedback==
         - Fall 2019: 80% of students had seen C++ already (skipped over c++ slides quickly)
         - Practically all students were familiar with electricity principles, units (kilo, milli) so the electricity presentation very simple
   - Day 2
     - Lecture: Open Workbench
       * IDE like PyCharm
       * Create project
       * explain folder structure
       * Walk through command palette
       * Login, Target project
     - Lecture
       * Argon program structure
       * ==fall 2019 only== show students how to download and install fritzing parts
     - Lab
       * Let students try to complete blinking of three LEDs
       * Build three LEDs; 
       * show in Fritzing (students observe)
       * show formal coding with variables (students code together)
     - Lecture
       - LEDs
     - Lab
       - just ask the question: Compare 10k ohm vs 330 ohm resistor
     - Lecture
       - Look at LED datasheet; calculate ideal resistance for LED
   - Assignment
     - A1 - Blink
   - Feedback
     - Day 2 generally went well; students wired thtree LEDs for about 20 minutes; should refine Ohms Law and explain math examples a little more
   
3. #### ADC, Potentiometers, Serial Monitor

   - Reading
     - https://learn.sparkfun.com/tutorials/analog-vs-digital/all
     - https://learn.sparkfun.com/tutorials/pulse-width-modulation/all
     - https://www.youtube.com/watch?v=GQLED3gmONg
   - Day 1
     - Lecture
       - Serial monitor
     - Guided activity
       - Let them work for a few minutes first
       - Ask them to digitalRead() on D2; use serial monitor to read with no connection (will be floating); then directly connect to **3.3v**, then GND
     - Lecture
       - Analog vs. digital
       - Pulse width modulation, PWM pins, analogWrite 
     - Lab
       - Make light fully bright for 2 sec, half as bright for 2 sec, 1/3 as bright for 2 sec, 
       - Challenge: Increase light level of LED automatically
     - Lab
       - Have students use for loop to sweep the brightness of an LED
     - ==Feedback==
       - Need to add additional material; could have gone fast through PWM and done more than just fade a LED
       - Serial monitor exercise uses **digitalRead**, which isn't covered until following week. Either more serial to next week, or vice versa
   - Day 2
     - Lecture
       * C++ for loops
     - Lecture
       - Potentiometer, voltage dividers
     - Lab
     
       - Have students connect pot to 3.3v, gnd, and A0; display the values
     - Lecture
     
       - Analog to digital conversion; explain the math / conversion between voltage and input values
     - Lab
     
       - Use potentiometer to control light level
     - Extra
       - If extra time, pull material from using multimeters
     - Feedback
       - a little slow; spent 20 min asking for course feedback which was helpful
       - could have gone through multimeters
     
   - Assignment
     
     - A2 - Light Scupture (have students bring to class; ==bring camera==)
   
4. #### Buttons, RGB LEDs *(one class cancelled for Tapia)*

   - Reading
     - https://learn.sparkfun.com/tutorials/pull-up-resistors
   - Day 1
     - ==Have students present light sculpture==
     - Guided activity
       - connect button with pullup
       - Ask what is the voltage at pin when button pressed and not pressed
     - Lecture
       - Digital Input
       - Push buttons: component, schematic, pull-up resistors
     - Guided activity
       * Fritzing explain
       * Create button with resistors in Fritzing
     - Guided activity
       - Connect button with resistor on Argon
     - Lab (students work on)
       - Turn LED on while button pressed
       - Turn LED off after button pressed
       - Connect 3 LEDs and control on/off with button presses (3 states)
   - Guided activity
     - Latching button and debouncing (if time)
   - Day 2 - Class cancelled (==Future semesters this could be RGB LEDs, debouncing, or catch-up==)
     - Assignment
       - A3 - Cylon light 
     
   - Feedback day 1
     - 
   
5. #### Week 5
   
   - Reading
     - https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all
   - Day 1
     - Activity
       * Video chat with Cyane's class (1 hour) ==(cancelled)==
       * Cyane collaboration
         * first meeting: Tues 9/24 @ 4-5 pm PST
           * 5 students of each to discuss life in the area, outside interests, what are they hoping to get out of studies
           * ask for volunteers
         * Next meeting 11/5 or 11/7   4:00 - 6:00 PST (3:00 - 5:00 MST)
           * we model during class (maybe cyane and I each present to each other)
           * then provide them a form and technology team
     - Discussion
       - how come when we turned the potentiometer on the cylon light, the blinking frequency didn't change right away? Get them to thinking delay / blocking
       - mention quiz topics
     - Lecture
       - RGB LED lecture
     - Lab
       - Display random color
     - Lecture
       - Functions in C++ *(this should be review from week 2)*
     - Lab
       - Button press trigger random color
       - Rewrite sketch using `displayColor(r, g, b)` and `displayRandomColor()`
       - cycle button presses to display C (BG) M (RB) Y (RG)
     - Lecture
       - Libraries
     - Lab
       - Have students find and install `rgb-controls`
       - Ask them to create some colors effects on their own
       - Then walk through example together
       - If time, introduce a button to control states (idea of a state machine)
     - Feedback
       - All the content took most of the class, but it feel slow and dragged
       - Try adding more content, or combining with LEDs?
   - Day 2
     - Lecture
       - Using multimeter
     - Lab
       - Have students measure resistance of pot when its out of a circuit
       - Show fritzing drawing, and have them measure voltage
     - Lecture
       - Reading resistors (lab exercise is built into slides)
       - TMP36
     - Lab (in slides)
       * Connect a TMP36 and output the current temperature to the serial monitor
       * Consider what type of input is this signal? How will this value be read by Argon
     - Lecture
       * Switch (==need to make slides==)
         * connect middle pin to argon
         * connect outer pins to power and ground
         * when moving the switch, it connects either left two, or right two pins
     - Guided activity
       * Connect switch to enable: middle pin to enable pin, outer pin to power and ground
       * enable and reset are active low
   - Assignment
     - A4 - Electronic dice 
6. #### Week 6

   - Reading (==Send this to students before class to watch==)
     - https://www.khanacademy.org/science/ap-physics-1/ap-circuits-topic/kirchhoffs-loop-rule-ap/v/ee-kirchhoffs-voltage-law
   - Day 1
     - Experiential Learning
       - Photoresistor part 1
       - Discuss
       - Photoresistor part 2
       - Discuss
       - Photoresistor part 3
       - Discuss and show code
     - Feedback
       - some students enjoyed the exploration; others seemed a little lost
       - change some things on the handout that were worded poorly
       - create some short, simple photoresistor wiring notes
       - One good thing was this followed learning about using the multimeter since the activity required it
     - Lecture
       - (if time) show derivation of mathematically deriving exact resistor to calibrate. Explain this is an important part of engineering
   - Day 2
     - Lecture
       - Libraries
       - Discuss OLED
     - Lab
       - Have students connect OLED to display "Hello World"
     - Guided Activity
       - Walk students through wiring
     - Lab
       - Have students create an Etch-A-Sketch with OLED
   - Assignment
      - A5 - Reaction Timer
         - Alternate ideas: use TMP36 to measure temperature and display colors on RGB LED. Use potentiometer to control brightness of RGB LED. Display results on serial monitor. **Optional** use button for diagnostic or to change cel/fahr 
   
7. #### Week 7

   - Reading
     - [Particle Cloud Functions](https://docs.particle.io/reference/device-os/firmware/photon/#cloud-functions)
     - Have students create an [IFTTT account](https://ifttt.com/) 
   - Day 1
     - Lecture
       - Particle Cloud API
       - Magnetic switch (no slides)
       <!-- connect one pin with pullup resistor to power and argon; other pin to gnd; 
         HIGH means open circuit; 
         LOW means closed circuit-->
     - Lab
       - wire switch (show fritzing)
       - publish switch event in console
       - publish variable
       - create function to turn off/on LED
       - subscribe to variable -- work in pairs 
         - create unique event TAC348/Door/<<UNIQUE_NAME>>
   - Day 2
     - Lecture
       - Continue with Particle cloud
     - Lecture
       - IFTTT
     - Guided activity
       - set up IFTTT [https://ifttt.com/create](https://ifttt.com/create)
       - Install iOS / Android app
       - how do create an alarm?
         - If Particle - Publish <event name> open
         - Then send notification
         - Could enhance by using your location
         - set up location trigger to enter or exit that sets a variable
         - then change publish event
       - **Ask students to work in pairs and come up with a cool idea**
   - Feedback
     - Some of the IFTTT got a little bumpy but generally this was a good amount of material and worked well
   - Assignment
     - A6 - Shared particle cloud temperature monitor (==I think this assignment is supposed to be one week later--should cover PREVIOUS week's material ==)
8. #### Week 8

   - Reading
     - 
   - Day 1
     - Lecture
       - Multitasking
     - Lab
       - blink without delay
     - Lecture
       - audio
     - Lab
       - make simple tone
     - Feedback
       - Each one of these could have been a full class. We had to go through the material very quickly and didn't get much time with audio
       - A6 improvements
         - warn students that it was hard and time consuming
         - Rob should publish some random temperatures so students can test
         - Give students more time to with material. Ideally, assignment should come a week later
   - Day 2 ==(class cancelled for fall break)==
     - Lecture
       - 
     - Lab
       - 
     - Lecture
       - DHT 11
     - Lab
       - 
   - Assignment
     - A7 - postponed with holiday
9. #### Week 9 - Motors and Servos

   - Reading
     - ==need to order fan blades for students==
   - Day 1
     - Lecture
       - DC Motor (Ray)
     - Lab
       - Students copy sketch to make fan blade rotate direction
       - Do experimental exercise to determine min / max PWM values
     - Feedback
       - Students seemed to enjoy making the motor + fan work, but this only took 1 hour
       - Improvised lecture by demonstrating analog joystick to control fan blade and rotation
   - Day 2
     - Lecture
       - Servo motors (Ray)
       - Very short presentation
     - Lab
       - Finished discussing buzzer and playing musical notes
     - Feedback
       - Consider combining both lectures on motors into one day
   - Assignment
     - A7 - Alarm Clock
10. #### Week 10

   - ==**Before class**== - Have students install Bluetooth phone apps
           - [Adafruit Bluefruit](https://learn.adafruit.com/bluefruit-le-connect)
           - [Nordic Semiconductor nRF Toolbox](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Toolbox)
   - Reading
        - [https://learn.sparkfun.com/tutorials/bluetooth-basics/all](https://learn.sparkfun.com/tutorials/bluetooth-basics/all)
        - [https://learn.adafruit.com/introduction-to-bluetooth-low-energy/](https://learn.adafruit.com/introduction-to-bluetooth-low-energy/)
- Questions
  - Day 1 ==**Give students velcro and have them assemble chassis before Thurs**==
    - Lecture
      - Bluetooth
      - Show Bluefruit app and nRF Toolbox
    - Lab - ble_uart_control_start
      - Distribute github link to download (post on slides)
      - Describe project goals
      - Explain **argon_ble_setup.h** at a high level
        - Have students change **DEVICE_NAME**
      - Pull up Bluefruit [documentation](https://learn.adafruit.com/bluefruit-le-connect/controller) and explain button signal
      - Code together blinking D7 when **press 1**
      - Have students code on their own D7 on with **press up** and D7 off when **release up**
      - (If time) have students code play tone when **press right **
      - Have students try using color picker to change RGB colors
    - Lab - ble_health_temp_start
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
    - Example - ble_uart_rgb_accel_example
      - Distribute github link to download (post on slides)
      - Describe project goals
      - explain **onDataReceived()**
      - explain **updateRGBvalues()**
      - explain **changeRgbLight()**
      - Demo device with code
   - Feedback - Day 1
      - With lecture slides and assembly, we barely finished lab 1
   - Day 2
      - Feedback Day 2
         - health thermometer service was a bust. We couldn't connect to the Argon. I would eliminate this next semester
         - Car building went well. We just covered **carForward** and need to finish Bluetooth part next week. In the future we might be able to cover all of car in one day by eliminating health thermometer
     - Lecture
       - LIPO battery
     - Lab
       - Have students assemble chassis before class
       - Wire motor controller
       - Have students download starting code
       - Walk through BLE code
       - build `leftMotor()` and `rightMotor()`
       - build four direction and stop functions
       - **Test functions in `loop()` without BT**
       - create `onDataReceived()`
       - **Test BT**
       - Connect switch to enable
   - Assignment
     - A8 - ?
11. #### Week 11

- Reading
  - 
- Day 1
  - Lecture
    - car bluetooth
  - Lab
    - build BT controls from Adafruit app
  - Lecture
    - Losant
  - Lab (together)
    - Create application
    - Create devices
    - Create integrations
    - Create workflows
  - Feedback
    - give brief overview of nodeRed (block programming) and javascript
    - start by sending one piece of data before using split to send multiple
- Day 2
  - Activity
    - Race competition
  - Lecture
    - Losant
  - Lab
    - Review workflow (make sure everyone is getting data in device by going to overview)
    - Create dashboard
    - Create web application
- Feedback
  - make sure to set up voting ahead of time for best customization for voting
  - [Create bracket online](https://challonge.com/tournament/bracket_generator)
- Assignment
  - Proposal

12. #### Week 12

   - Reading
     - 
   - Day 1 -- ==**Google Guest Lecture on Accessibility**==
     - Lecture
       - Google guest lecture
     - Lab
       - After guest lecture, we all met in a circle and discuss project proposals and gave feedback
     - Lecture
       - 
     - Lab
       - 
   - Day 2
     - Lecture
       - Discuss DHT 22
       - Discuss controlling devices from Losant
     - Lab
       - Revise firmware and Losant environment to support input controls (blink light on / off)
     - Assignment
       - Work on project 
13. #### Week 13

- Reading
  - 
- Day 1 -- ==Class Cancelled==
  - Lecture
    - 
  - Lab
    - 
- Day 2
  - Lecture
    - I2C LCD
    - Ultrasonic distance sensor
  - Lab
    - exercises in slides
  - Feedback
    - Fail.
    - The LCD devices only worked for half the students (either faulty devices or bad libraries). Definitely DO NOT use LCDs again
    - Ultrasonic sensor worked mostly
- Assignment
  - project

14. #### Week 14

   - Reading
     - 
   - Day 1
     - Lab
       - Revisit ultrasonic sensor lab to show working code (didn't work for some students)
     - Activity
       - Check milestone
     - Lecture
       - accelerometer
     - Lab
       - Use **tap** feature
       - Use **portrait / landscape** detection
       - Use accelerometer to control RGB LED
   - Day 2 **==Class Cancelled due to Thanksgiving==**
     - Lecture
       - 
     - Lab
       - 
     - Lecture
       - 
     - Lab
       - 
   - Assignment
     - AX - 
15. #### Week 15

- Reading
  - 
- Day 1
  - Lecture
    - Work on project 
- Day 2
  - Lecture
    - Work on project 
- Assignment
  - AX - 

16. #### Week 16 - Final Project Presentation

   

[Two-Layer Chassis Assembly](https://youtu.be/L7-98Ejmb4M)

[Pictures of installation](https://learn.sparkfun.com/tutorials/assembly-guide-for-sparkfun-jetbot-ai-kit/1-circular-robotics-chassis-kit-two-layer-assembly) (only relevant through half of the first page)