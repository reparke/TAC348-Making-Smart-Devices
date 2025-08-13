#### 	Things to implement

* assignment 1: change wifi setup instructions to just describe "claiming a device" a second time

#### General Feedback (Fall 2019)

* Assignment 0 is given out week 1, day 1; due week 2, day 1; that is the pattern
* Develop a way to post readings on website
* Try to integrate lectures, readings, assignments all on one webpage under "weeks"
* students like being show a small bit of using a sensor, and then extending it on their own
* students like hands-on

  

0. #### Pre-semester

    - [ ] Send students installation instructions
    - [x] purchase items (see Evernote pre-semester tasks)
    
    - Reading
      - Enabling the Internet of Things https://web.eecs.umich.edu/~prabal/teaching/resources/eecs582/want15iot.pdf
    
- Day 1 
  - Lecture
    - Course introduction / syllabus (PDF file)
    - Ice breaker *(see slides in local TAC 348 Docs folder)*
    - Introduction to IoT
    - Possibly show this [mind map](https://www.mindmeister.com/1308604904?t=O0Vcty0Uys) from Boris Tomas
  - Lab
    - none
- Day 2
  
  - Lecture
  
    - Pass out argons
       - students are responsible for returning devices if they drop before drop deadline
    - Kit Overview
    - Software tools
       - Workbench (open and discuss)
       - Fritzing (open and show example project)
    - Safety
    - *Explain what particle does, cloud, flash (no slides)*
   - Lab
     
     - Paper circuits
     - Then ask student to complete a creative expression with multiple LEDs
  - Assignment
    - Due start of current week: none
    - Given out start of current week: A0 - Software and tool installation
  - ==Feedback==
    - Day 2 "making project" was fun; ping pong balls and glue guns were a hit
  

2. #### Electricity, Microcontrollers, LEDs
   
   - Reading
     - http://www.tigoe.com/pcomp/code/circuits/understanding-electricity/
     - https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law/all
     
   - Day 1
     
     - Support
       - TA and I spent some time class helping install
       - Demonstrate how to reset device and go to safe mode
     - Lecture
       * C++ Syntax
       * Argon Microcontroller
     - Lab
       * Have students work in pairs to answer datasheet questions from Argon Microcontroller slide
     - Lecture
       - Electricity and Ohm's Law
     - Lab
       - Walk students through connecting LED + Resistor to VUSB on Argon
         - Ask students how they would connect more than 1 LEDs
         - Ask students how they would make LEDs blink
       - ==Feedback==
         - 1/3 students had seen C++ already (skipped over c++ slides quickly)
         - Most students were familiar with electricity principles, units (kilo, milli) so the electricity presentation very simple
         - Didn't get to finish Electricity lecture or get to lab; should have gone faster
     
   - Day 2
     - Lecture: Open Workbench
       * IDE like PyCharm
       * Create project
       * explain folder structure
       * Walk through command palette
       * Login, Target project
     - Lecture
       * Argon program structure
       * Show students how to download and install fritzing parts
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
     
     - Due start of current week: A0 - Software and tool installation
     - Given out start of current week: A1 - Blink
   
   - Feedback
     
     - Day 2 generally went well; students wired three LEDs for about 20 minutes; should refine Ohms Law and explain math examples a little more
   
3. #### ADC, Potentiometers, Serial Monitor

   - Reading
     - https://learn.sparkfun.com/tutorials/analog-vs-digital/all
     - https://learn.sparkfun.com/tutorials/pulse-width-modulation/all
     - https://www.youtube.com/watch?v=GQLED3gmONg
   - Day 1
     - mention quiz topics for next week short in-class quiz
     - Review calculation for choosing resistor for LED (if not done last week)
     - Lecture
       - Serial monitor
     - Guided activity
       - Do simple example where there is a global variable that gets incremented and display its value with Serial monitor
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
   - Day 2
     - Lecture
       * C++ `for` loops
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
     
     - Due start of current week: A1 - Blink
     - Given out start of current week: A2 - Light Sculpture (have students bring to class; ==bring camera==)
   
4. #### Buttons, RGB LEDs

   - Reading
     - https://learn.sparkfun.com/tutorials/pull-up-resistors
   - Day 1
     - ==Have students present light sculpture== Start class with presentations
     - Guided activity
       - Ask them to **digitalRead()** on D2; use serial monitor to read with no connection (will be floating); then directly connect to **3.3v**, then GND
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
     - Feedback
       - Seemed to drag: Students finished first lab task and we reviewed solution. Would be better to go faster through slides and let them play, then have more time for other things
   - Day 2 ==(skipped this lecture, and jumped to RGB LEDs; w5d1 was cancelled so this material wasn't covered)==
     - Guided activity
       - Latching button and debouncing (if time)
     - Lecture
       - Latching button and debouncing (==need to make slides==)
     - Lecture
       - Switch (==need to make slides==)
         * connect middle pin to argon
         * connect outer pins to power and ground
         * when moving the switch, it connects either left two, or right two pins
     - Guided activity
       * Connect switch to enable: middle pin to enable pin, outer pin to power and ground
       * enable and reset are active low
   - Assignment
     - Due start of current week: A2 - Light Sculpture 
     - Given out start of current week: A3 - Cylon light 
   - Feedback day 1
     - 
   
5. #### Week 5
   
   - Reading
     - https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all
   - Day 1
     - **Have Quiz**
     - Discussion
       - how come when we turned the potentiometer on the cylon light, the blinking frequency didn't change right away? Get them to thinking delay / blocking
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
       - TMP36
     - Lab (in slides)
       * Connect a TMP36 and output the current temperature to the serial monitor
       * Consider what type of input is this signal? How will this value be read by Argon
   - Assignment
     - Due start of current week: A3 - Cylon light 
     - Given out start of current week: A4 - Electronic dice 
   
6. #### Week 6

   - Reading (==Send this to students before class to watch==)
     - https://www.khanacademy.org/science/ap-physics-1/ap-circuits-topic/kirchhoffs-loop-rule-ap/v/ee-kirchhoffs-voltage-law

   - Day 1
     - Lecture
       - Libraries
       - Discuss OLED
     - Lab
       - Have students connect OLED to display "Hello World"
     - Guided Activity
       - Walk students through wiring
     - Lab
       - Have students create an Etch-A-Sketch with OLED

   - Day 2
     - Lecture
       - Reading resistors (lab exercise is built into slides)
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
   - Assignment
      - Due start of current week: A4 - Electronic dice 
      - Given out start of current week: A5 - Reaction Timer
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
     - Due start of current week: A5 - Reaction Timer
       - Warn students that it was time consuming
       - **==IDEA==** make reaction timer a statemachine assignment and move forward (replace other assigment)
     - Given out start of current week: ==CREATE NEW ASSIGNMENT==
   
8. #### Week 8

   - Reading
     - ==Send wiring diagram out ahead of time==
   - Day 1
     - Lecture
       - Switch and enum
       - Finite state machines
     - Lab
       - Starting with sample code
       - walk through NS light state transitions (length, state)
       - use delay() (not millis)
     - Feedback
       - next day cover millis, then rest of light blinking
       - some students enjoyed the complexity of all parts, other seemed bored
   - Day 2
     - Continued with FSM
   - Feedback
     - Students felted overwhelmed with FSM, switch, and enum all at once
     - Better to introduce them slowly over time and build up to complicated stoplight example
   - Assignment
     - Due start of current week: ==CREATE NEW ASSIGNMENT== (if one is created)
     - Given out start of current week: A7 - Shared particle cloud temperature monitor
   
9. #### Week 9 - Soldering and Speaker

   * Day 1
      * Soldering demo in EE lab
      * had students build sparkfun flashlight
      * Then Neftali did a quick demo of how to lay out a simple PCB in Fritzing
   * Feedback
     * Took about 1 hour
     * soldering was fun but really simple. It would be cool to have a second, more complex circuit
   * Day 2
     * Lecture
       * Speaker
       * Tone
       * Pitches
   * Assignment
      * Due start of current week: A7 - Shared environment monitor
      * Given out start of current week: A8 - Alarm clock
   
10. #### Week 10 - Motors and Servos

   - ==need to order fan blades for students==
   - Reading
     
     - notes on motors: [https://www.electronicproducts.com/Electromechanical_Components/Motors_and_Controllers/Motor_control_design_an_introduction_to_motors_and_controllers.aspx](https://www.electronicproducts.com/Electromechanical_Components/Motors_and_Controllers/Motor_control_design_an_introduction_to_motors_and_controllers.aspx)
   - Day 1
     - Lecture
       - DC Motors
     - Lab
       - Students copy sketch to make fan blade rotate direction
       - Do experimental exercise to determine min / max PWM values
     - Feedback
       - Students seemed to enjoy making the motor + fan work, but this only took 1 hour
       - Improvised lecture by demonstrating analog joystick to control fan blade and rotation
        - Lecture
          - Servo motors
          - Very short presentation
     
     - Lab
       - Connect servo to DC motor
       - control fan speed and direction with two potentiometers
- Feedback
- Day 2
  - Lecture
    - Losant
  - Lab (together)
    - Create application
    - Create devices
    - Create integrations
    - Create workflows
- Feedback
  - start by sending one piece of data before using split to send multiple
- Assignment

  * Due start of current week: A8 - Alarm clock
  * Given out start of current week: ==A9 - Bluetooth car==
  * ==This wouldn't have worked because the would have been given car assigment BEFORE covering the car and bluetooth==

11. #### Week 11

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
    - Example - ble_uart_rgb_accel_example
      - Distribute github link to download (post on slides)
      - Describe project goals
      - explain **onDataReceived()**
      - explain **updateRGBvalues()**
      - explain **changeRgbLight()**
      - Demo device with code
    - Feedback - Day 1
    - 
   - Day 2
       - Lecture
          - car bluetooth
      - Lab
         - build BT controls from Adafruit app
     - Feedback Day 2
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
     - Due start of current week: ==A9 - Bluetooth car (this doesn't work in terms of placement)==
     - Given out start of current week: 
11. #### Week 11

- Reading
  - 
- Day 1
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
- Day 2
  - ==cancel==
- Assignment
  - Due start of current ==week: ?==
  - Given out start of current week: Proposal

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
       - Due start of current week: A10 - Bluetooth car 
       - Given out start of current week: 
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
   - Day 2 
     - Lecture
       - ==Guest lecture==
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



---



**Skipped / Eliminated****

- BLE Health service
  - The goal was to send a temperature from Argon to Bluefruit app but it rarely worked
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
  - - 
 - 