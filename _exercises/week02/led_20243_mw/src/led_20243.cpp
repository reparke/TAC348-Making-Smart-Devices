#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// use 5.8
/*
  When we make a new project
    1) Configure for device
    2) Create our constants for the pins we are using
    3) Set the pin modes
      do this in the setup function

    in MCU, we have no main
    instead, setup() and loop()
    setup() is called ONCE when you plug in or flash your photon
    loop() then runs FOREVER in a loop


    WE DO NOT WANT TO USE WHILE LOOPS IN THIS CLASS

    loop() ALREADY is basically an infinite while loop

    USING SERIAL MONITOR
    1) in setup: Serial.begin
    2) in loop(): SErial.println when you need it
    3) workbench: open the serial monitor
*/

// pin label global constants
//  const int PIN_LED = D1;
const int PIN_POT = A0;
const int PIN_LED = A2;

// global variable (not constant)
//  try use loop() and this variable to vary brightness automatically
int brightness = 0;

void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_POT, INPUT);
    Serial.begin(9600);
}

void loop() {
    // digitalWrite will send a 3.3V signal to a pin
    //     this causes the LED to turn on
    //  HIGH is 3.3V
    //  LOW is ground

    // digitalWrite(PIN_LED, HIGH);
    // delay(200); //200 ms
    // digitalWrite(PIN_LED, LOW);
    // delay(200);

    // use PWM to vary the brightness
    //  analogWrite(PIN_LED, 127);   // specify PWM values as 0-255
    //  delay(500);
    //  analogWrite(PIN_LED, 255);// full brightness
    //  delay(1000);

    // analogWrite(PIN_LED, brightness);  // range of PWM is 0-255
    // delay(50);
    // brightness = brightness + 25;
    // // we are in a loop
    // if (brightness >= 255) {
    //     brightness = 0;
    // }

  // read the voltage on the pot
  //what is the range of ADC values? 0-4095
  int potValue = analogRead(PIN_POT);
  Serial.println("Potentiometer value " + String(potValue));
  delay(100);

  // input is 0-4095
  // output is PWM 0-255

  int pwmValue = map()
}
