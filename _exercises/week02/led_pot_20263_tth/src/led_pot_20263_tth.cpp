#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
  Four things we have to do EVERYTIME we have new project
  1) configure project for device
  2) Create pin labels (global constants)
  3) Set pinModes (in setup())
  4) Initialize Serial (in setup())


  sign-in is important! but we should only have to do that every ~2 months
*/

// pin labels
const int PIN_LED = A2;
const int PIN_POT = A0;

void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_POT, INPUT);
    Serial.begin(9600);
}

// make the potentiometer control the brightness of the LED
void loop() {
    // read from pot
    int potVal = analogRead(PIN_POT);
    // ADC: 0 - 4095
    // PWM: 0 - 255

    // int pwmVal = potVal / 4095 * 255; //incorrect math bcz of int div
    /*
      in C++
        int / int ====> int (integer division)
        3039 / 4095 ===> 0

        int / float ===> float
        3039 / 4049 == 0.75..

      solution: make one of the operands a float

      int pwmVal = potVal / 4095.0 * 255;
    */
   int pwmVal = float(potVal) / 4095 * 255; 

   analogWrite(PIN_LED, pwmVal);


  Serial.println("potVal = " + String(potVal) + ", pwmVal = " + String(pwmVal));

  // let's now publish the pot and pwm values to Particle cloud
  Particle.publish("pwm", String(pwmVal));
  Particle.publish("pot", String(potVal));

  // delay(200); //200 ms
  //change publishing rate
  delay(1000);
}


/*
  We open the Serial monitor to see Serial.println() messages

  We open the Particle console in a web browser to see Particle.publish() msgs
*/
