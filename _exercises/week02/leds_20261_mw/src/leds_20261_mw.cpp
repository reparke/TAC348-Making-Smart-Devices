#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
  EVERYTIME we make a new project, we have to do the following thingss
  1) configure this project for our specific device (cmd palette)

  2) create pin labels
    --> GLOBAL CONSTANTS which refer to ANY pins we plan to use in our code
    --> global means these are defined  OUTSIDE of a func and placed at the top
  of our code so they are accessible EVERYHWERE (local var are defined INSIDE a
  function and only exist in that func)

    3) set up pin modes
    --> tells the photon whether each pin is INPUT OR OUTPUT
      this happens in setup

    4) Handle serial
      a) put Serial.begin(9600) in setup()
      b) put Serial.println(...) in loop() as needed
      c) OPEN the serial monitor
          ->> cmd palette "Serial Monitor"

  ----

  LEDs are output device -- treat at DIGITAL
    send 3.3v to PIN_LED (anode), LED turn on  -- HIGH
    send 0v to PIN_LED (anode), LED turn off   -- LOW


  structure of photon firmware
  setup() runs ONCE when device turns on
  loop() runs FOREVER!

  remember:
  any var declared in setup or loop will disappear each those func stop
  --> SO any var that needs "memory" is going to need to be global
*/

// step 2 - pin labels
const int PIN_LED = A2;
const int PIN_POT = A0;

int loopCounter = 0; // global variable
int brightness = 0; //track analog write value

void setup() {
    // step 3 - pin mode
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_POT, INPUT);
    Serial.begin(9600);
}

void loop() {
    // v1 - blink led
    // digitalWrite(PIN_LED, HIGH);  // turn on LED
    // delay(2000);                  // pause for 2000 ms, or 2 sec
    // digitalWrite(PIN_LED, LOW);   // turn off LED
    // delay(2000);
    //comment multiple lines at once by selecting and hitting cmd or ctrl /

    //v2 - analog write
    /*
    analogWrite allows to simulate analog voltage outputs
    values varies from 0 (min) to 255 (max)
    --> effect is that led will get brighter or less bright   
    */
  //  loopCounter = loopCounter + 1;
  //  Serial.println("starting new loop cycle " + String(loopCounter));
  //  analogWrite(PIN_LED,0);  //off
  //  delay(500);
  //  analogWrite(PIN_LED, 127); //50%
  //  delay(1000);
  //  analogWrite(PIN_LED, 255); //on
  //  delay(500);
  //  analogWrite(PIN_LED, 127); 
  //  delay(500);


  //v3 - auto increase
  //led to be off, then slowly get brighter, then go off, and repeat

  /*how could we do this?
  1) for loop -- perfectly valid
  2) while loop -- DO NOT USE THIS!
  3) loop()


  lets try using loop()
    do analogwrite
    increase brightness
    check if we need reset brights
  */

  Serial.println("Brightness is " + String(brightness));
  analogWrite(PIN_LED, brightness);
  delay(100);
  brightness = brightness + 20;
  if (brightness > 255) {
    brightness = 0;
  }

}
