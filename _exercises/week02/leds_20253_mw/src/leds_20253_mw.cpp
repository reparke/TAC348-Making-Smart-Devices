#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
  New projects -- what do we have to do
  1) Configure project for device (cntl or cmd  + shift + P)
  2) create pin label for any pins we are using
      --> GLOBAL CONSTANT to identify which pins we are using
  3) set the pin mode for all inputs and outpus
    --> tell Photon if the pins we are using are INPUT or OUTPUT
    --> in setup(), set pinMode
*/
/*
  Structure of Photon program
  -setup() runs ONCE when the device first turns on
        --> set your pin modes

  -loop() runs FOR...EVER, looping again and again
*/

//global variables or constants are defined ABOVE / OUTSIDE any functions like setup and loop
// usually at the top of our file

const int PIN_LED = A2;
const int PIN_POT = A0;

//declare global variable to store the current brightness
/*
  global var declared OUTSIDE functions and accessible EVERYWHERE  
  local var declared INSIDE func and ONLY EXISTS in that funct
*/
int brightness = 0;

void setup() {
  pinMode(PIN_POT, INPUT);
  pinMode(PIN_LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // // DIGITAL OUTPUT 
  // //digitalWrite is used to turn an LED ON (HIGH) or OFF (LOW)
  // digitalWrite(PIN_LED, HIGH);      // HIGH means 3.3v
  // delay(1000); //1000 ms or 1 s
  // digitalWrite(PIN_LED, LOW);       //LOW means ground GND 0v
  // delay(2000);  //2 s

  // //will loop again and again

  // //play with analog values
  // analogWrite(PIN_LED, 255);    //use PWM at full value (aka brightness or voltage)
  // delay(1000);
  // analogWrite(PIN_LED, 127);   // PWM with half brightness
  // delay(1000);
  // analogWrite(PIN_LED, 0);
  // delay(1000);

  /*
    how can we get the LED brightness to increase automatically?
        e.g slowly gets brighter, then resets to 0 and repeats
        
    1) for loop 
    2) while loop <--- don't use this
    3) we can use our void loop() LIKE A while loop
      declare a var with brightness
      increase the value each time we go through loop()
  */
 analogWrite(PIN_LED, brightness);
 delay(500);
 brightness = brightness + 20; //increase value
 //once we get above 255, reset
 if (brightness >= 255) {
  brightness = 0;
 }
 Serial.println("The brightness is " + String(brightness));

}
