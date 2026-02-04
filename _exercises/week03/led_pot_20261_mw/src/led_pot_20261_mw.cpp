#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
  Four things we when create ANY new project
  1) configure project
  2) create pin labels
  3) pin modes
  4) setup project

  What is PWM and why do we use it?
  -
  makes leds dimmer/brighter
  simulate an analog signal

  analogWrite --> what is the range of values we give this function?
    0 - 255

  Last wed, we use the loop() and we made the LED get brighter and brighter and
  turn off, and repeat

  today
  -
  have LED get brighter until max brightness, then get dimmer until off, then
  repeat use loop() and NOT for/while hint: we can use global variables


  what is a potentiometer?
  -
  analog input device
  technically, this varies RESISTANCE
    but it allows to measure change in VOLTAGE
    3v3 one leg, 0v on other, and we measure the voltage change in middle (wiper)
*/

// pin labels
const int PIN_LED = A2;
const int PIN_POT = A0;

int brightness = 0;
bool isIncreasing = true; // are we getting brighter, or not

void setup() {
    // pin mode
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_POT, INPUT);

    Serial.begin(9600);
}
void loop() {
//   Serial.println("Brightness = " +  String (brightness));
//   if (isIncreasing == true) {
//     brightness = brightness + 20;
//   }
//   else  { //we are now getting dimmer
//     brightness = brightness - 20;
//   }

//   if (brightness >= 255) {
//     isIncreasing = false;   //flip
//   }
//   else if(brightness <= 0) {
//     isIncreasing = true;
//   }
//   analogWrite(PIN_LED, brightness);
//   delay(100);

// lets just read the potentiometer
//  pot range is 0 - 3.3V ---> converted   0 - 4095

int potVal = analogRead(PIN_POT);

// int pwmVal = potVal / 4095 * 255;  // incorrect math due to INTEGER DIVISION
// solutions
// int pwmVal = potVal / 4095.0 * 255
int pwmVal = float(potVal) / 4095 * 255;

Serial.println("Pot val = " + String(potVal) + ", PWM val = " + String(pwmVal));

analogWrite(PIN_LED, pwmVal);



/*
  in C++, division of two ints / is always INTEGER DIVISION
    int / int ---> int (NOT A FLOAT)    so 99/100 --> 0

    solution: force one of the numbers to be float
    
      float / int ---> float
*/

/*
  now make the potentiometer control the LED brightness
  --> so as we turn the knob, the LED will get brighter or dimmer
  pot range: 0 - 4095 (ACD values)
  LED PWM range: 0-255

*/
delay(200);
}



/*
  PWM ADC

  ADC 
    converting analog input to a digital val
    range: 0-4095
    analogread

  PWM
    varying OUTPUT volt by simulating analog output
    range: 0-255
    analogwrite

*/