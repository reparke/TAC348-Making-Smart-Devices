#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
    EVERYTIME we make a new project, we have to do the following:
    1) configure project for device (cmd palette) cmd or control + shift + p
    
    2) create pin label
      --> GLOBAL CONSTANTS which refer ANY pins we plan to use in our project / code
      --> global means defined OUTSIDE of a function at the TOP of our code
            accessible EVERYWHERE in our code
        (in contrast, LOCAL variables are defined INSIDE a function and ONLY EXIST in that function)

    3) set up your pin modes
      --> tell photon whether each pin we are using is INPUT or OUTPUT
      do this in setup()

*/
/*
  LED is a output device--let's treat as digital
    send 3.3v to the anode, led turns on    (HIGH)
    send 0v to anode,       led turn off    (LOW)
*/

/* structure of photon code
  setup() runs ONCE at the start (do pinMode)
  loop() run FOR.....EVA!  
*/

/*
  Serial Monitor! how we can have "print statements" or debug messages
  To use output messages, 3 steps!
  1) in setup()
    Serial.begin(9600);
  2) in loop()
    Serial.println(.......);
  3) open the serial monitor see message
    cmd palette: Serial Monitor

*/


//make pin labels for led and pot
const int PIN_LED = A2;
const int PIN_POT = A0;

//global var for brightness
int brightness = 0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_POT, INPUT);
  Serial.begin(9600);   //starts the serial object
}

void loop() {
  // int brightness = 0;  //wouldn't work because it would reset to 0 EVERY LOOP cycle
  // v1 - digital write
  // digitalWrite(PIN_LED, HIGH); //send 3.3v to pin A2 (anode of the LED ) to make it turn on
  // delay(1000); //1 sec or 1000 ms
  // digitalWrite(PIN_LED, LOW);   //send 0v to pin A2 to make it turn off
  // delay(2000);  //2 sec or 2000 ms


  //v2 - analog write
  // 0 - 255 control how long the voltage to the LED is high vs. low
  //    "duty cycle"  PWM 0 --> 0%  and PWM 255 --> 100% always on
  //    --> effect of this is that 0-255 will make the LED brighter or less bright

  //   analogWrite(PIN_LED, 0)    --> same as digitalWrite(PIN_LED, LOW)      -->  LED OFF
  //   analogWrite(PIN_LED, 255)    --> same as digitalWrite(PIN_LED, HIGH)   --> LED ON (full brightness)
  // analogWrite(PIN_LED, 255);    //full bright
  // delay(500);
  // analogWrite(PIN_LED, 127);    //half bright
  // delay(500);
  // analogWrite(PIN_LED, 0);
  // delay(500);


  /*
    v3 auto increase
      --> have led off, slowly increase in brightnesss until max, then go back to off, repeat

    how do we do this?
    1) for loop           -- perfectly valid
    2) loop with increment **** 
    3) while loop     -- DONT EVER USE THIS


    create a global var to store brightness
    in loop()
      use analog write
      increase brightness
      check if we need to reset brightness
  */
 Serial.println(brightness);
 Serial.println("The brightness is " + String(brightness));
 
  analogWrite(PIN_LED, brightness);
  delay(100);
  brightness = brightness + 20;
  if (brightness > 255) {
    brightness = 0;
  }

}
