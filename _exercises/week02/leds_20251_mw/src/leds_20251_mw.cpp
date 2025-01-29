#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

/*
  New projects - every time
  1) configure for device
  2) create pin labels - GLOBAL CONSTANT that makes it easy to refer to our components
  3) set the pin mode - we have to say if it is INPUT or OUTPUT

  to use serial monitor
  - serial.begin(9600) in setup
  - serial.println(...)in loop
*/
//global constant - defined ABOVE setup
const int PIN_LED = A2;
const int PIN_POT = A0;

//global var
int brightness = 0;

//setup runs once when we start the device
void setup() {
  //set pin mode
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_POT, INPUT);
  Serial.begin(9600);   //config serial
}



//loop runs forever infinitely
void loop() {
  // //turn on LED for 2 sec
  // // LED is a DIGITAL OUTPUT device
  // //    ON or OFF
  // digitalWrite(PIN_LED, HIGH);    //HIGH and LOW to be ON and OFF (or 1 and 0)
  // delay(2000); //2000 millsec or 2 sec
  // //turn off for 4 sec
  // digitalWrite(PIN_LED, LOW);
  // delay(4000);

  //experiment with PWM (analog output)
  // analogWrite(PIN_LED, 0);  //off
  // delay(1000);
  // analogWrite(PIN_LED, 127); //half brightness: 255 is full (3.3) so HALF would 127
  // delay(1000);
  // analogWrite(PIN_LED, 255);
  // delay(1000);

  //how can we increase the brightness AUTOMATICALLY
  //increase brightness from 0 to 255, and reset back to 0
  //we could use loop to increase brightness alittle each time
  // void loop() is ALREADY an infinite loop

  //remember that local var disappear each time the functions ends
  //so if want to store brightness, it needs to GLOBAL

  // brightness = brightness + 10; //update
  // //reset
  // if (brightness >= 255) {
  //   brightness = 0;
  // }
  // Serial.println("The brightness is " + String(brightness));
  // analogWrite(PIN_LED, brightness);
  // delay(500);

  //read pot
  int potVal = analogRead(PIN_POT);


  // int pwmVal = potVal / 4095 * 255; 
  //in C++, int / int --> int
  // SO when we divide integers AND we want a decimal, we need to force
  // one of the integers to be a float because int / float --> float
  // int pwmVal = potVal / 4095.0 * 255;   //one way to make sure you get a float
  int pwmVal = float(potVal) / 4095 * 255;

  Serial.println("Pot val = " + String(potVal) + " and PWM val = " + String(pwmVal));
  analogWrite(PIN_LED, pwmVal);
  delay(100); //100 ms

  //use the potentiometer to control the brightness of the LED
  // pot is analog input which means it converts 0-3.3V to 0-4095
  // changing brightness is analog output which uses PWM and values vary 0-255
 

  
}
