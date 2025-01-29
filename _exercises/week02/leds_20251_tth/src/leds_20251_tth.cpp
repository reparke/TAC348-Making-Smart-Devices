#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);

SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

/*
  New projects
  1) configure project for device
  2) create pin labels for any pins we are using
      --> create GLOBAL CONSTANTS to identify the pins we are using
  3) set the pin mode --> in setup(), we say if a pin is INPUT or OUTPUT
*/

/*
  global variables exist everywhere -- use these when we need a variable
      to keep its value after the loop() ends
  local variables exist ONLY in a function and are erase at the end of the function
*/

/*
  Often, we want to see debug mesages about code
  equivalent of print statements is Serial.println()

  To use Serial.print, these are the steps
  1) in setup(), add
    Serial.begin(9600);
  2) to display a message from Photon in Workbench, use the function Serial.println()
  3) Open the SERIAL MONITOR from command palette
*/

const int PIN_LED = A2;
const int PIN_POT = A0;

int brightness = 0; //global var

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_POT, INPUT);
  Serial.begin(9600);
}

void loop() {
  //lets make the LED on for 2 sec, and off for 4 sec
  // digitalWrite(PIN_LED, HIGH);  //send 3.3v (HIGH) to PIN_LED
  // delay(2000);    //2000 millsec = 2 sec
  // digitalWrite(PIN_LED, LOW); // LOW means 0v or ground
  // delay(4000);
   
   //experiment with analog write
   // values from 0 - 255 (0 is off or 0V, and 255 is on or HIGH 3.3v)
  //  analogWrite(PIN_LED, 128); //half bright
  //  delay(2000);
  //  analogWrite(PIN_LED, 255); //full voltage
  //  delay(2000);
  //  analogWrite(PIN_LED, 0);
  //  delay(2000);

  //how can we get the brightness to go from 0 to 255 over time and then reset back to 0
  // one approach is a for loop or a while loop
  //      however, in this class we rarely use for loops
          // and we NEVER use while loops

    // brightness = brightness + 10;
    // if (brightness >= 255) {
    //   brightness = 0;
    // }
    // delay(500);
    // analogWrite(PIN_LED, brightness);
    // Serial.println("The brightness is " + String(brightness));
    // // we can not concatenate (use +) a string and int

  // lets use the potentiometer to control the brightness of the LED
  // reading pot converts 0-3.3V to a digital value 0-4095
  // writing an LED brightness uses PWM 0-255

  int potVal = analogRead(PIN_POT); // 0-4095

  // int pwmVal = potVal / 4095 * 255;  //incorrect!
// int pwmVal = potVal / 4095.0 * 255;
int pwmVal = float(potVal) / 4095 * 255;

  // in C++,  int / int --> int
  //       float / int --> float

  analogWrite(PIN_LED, pwmVal);

  Serial.println("potVal = " + String(potVal) + ", pwmVal = " + String(pwmVal));


}
