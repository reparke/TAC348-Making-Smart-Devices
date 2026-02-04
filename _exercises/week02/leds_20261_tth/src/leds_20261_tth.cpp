#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
  EVERYTIME we make a ne project, we have to do FOUR THINGS
  1) configure for device
    (cmd palette)
  2) create PIN labels
    --> GLOBAL CONSTANTS that refer to ANY pin we plan to use in our code
    --> global means defined OUTSIDE a func at the TOP of our code, and
accessible EVERYWHERE in our code (in contrast, local var mean defined INSIDE a
func and only exist in that function) 3) set pin modes
    -->tell photon whether each pin we are using in INPUT or OUTPUT
        do this in setup()
  4) setup up serial
    a) Serial.begin(9600) in setup()
    b) use serial.println in loop() whenever you want to print
    c) open "serial monitor" via the cmd palette


  LED is an output device --> lets treat it as digital
    send 3.3V to the anode (pin) --> leds turn on
    send 0v to anode -->            leds turn off

    3.3v  --> HIGH
    0V    --> LOW


program structure
  setup() run ONCE when you start device

  loop() runs FOREVER AND EVER



*/

// step 2: pin labels
const int PIN_LED = A2;
const int PIN_POT = A0;

int brightness = 0;

void setup() {
    // step 3 pin mode
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_POT, INPUT);

    // setup serial step A
    Serial.begin(9600);
}

void loop() {
    // v1 - led blink
    //  Serial.println("LED on");
    //  digitalWrite(PIN_LED, HIGH);      //turn led ON
    //  delay(1000);        //pause for 1000ms or 1 s

    // Serial.println("LED off");
    // digitalWrite(PIN_LED, LOW);       //turn led off
    // delay(2000);        //pause for 2000ms or 2 s

    // v2 - analog write
    // analogWrite(PIN_LED, 127);  // led on half brightnesss (0-255)
    // delay(1000);
    // analogWrite(PIN_LED, 255);  // led on full brightness
    // delay(1000);
    // analogWrite(PIN_LED, 90);
    // delay(1000);
    // analogWrite(PIN_LED, 0);
    // delay(1000);

  /*
    digitalWrite of HIGH is the same and analogwrite of 255
  */


  //v3 - auto brightness
  // led to be off then slowly increase in brightness until full bright, then off again
  // everytime the brightness changes, print out the brightness to serial monitor
  /*
    how could we approach this?
    1) for loop         -- this is valid
    2) while loop        -- DONT USE THIS!
    3) loop()           --


  */

  // any local var will be erased when the function end
  // if we need "memory" for var beyond just the time this fn is running right now
  //      we need a global var

  Serial.println("Brightness is " + String(brightness));
  analogWrite(PIN_LED, brightness);
  brightness = brightness + 5;
  if (brightness > 255) {
    brightness = 0;
  }
  delay(500);

}
