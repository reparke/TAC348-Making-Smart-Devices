#include "Particle.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
  what do we everytime we make a new project
  1) configure project for device
  2) create pin labels
  3) set pin modes
  4) set up serial

  what's different between setup() and loop()?
  -
  setup() runs ONCE when devices starts
  loop() runs FOREVER

  What is PWM and why do we care?
    pulse width modulation
    simulates analog output
    make the led brighter / less bright

    fn: analogWrite 
    range: 0 - 255
    NOT EVERY PIN SUPPORTS THIS!

    last week, we used loop() and made the LED get brighter then turn off, repeat

    today
    have the led get brighter to MAX, then get dimmmer to MIN, etc
    use loop() (don't use FOR or WHILE)
    hint: its ok to use global var


    potentiometer
    -
    3 pins: 3v3, gnd, wiper (read this)
    technically, pot varies resistance
      but it does allows to measure voltage change
      3v3 and gnd--> wiper can sweep the range of voltages from 0 - 3.3v
*/

const int PIN_LED = A2;
const int PIN_POT = A0;

int brightness = 0;
bool isIncreasing = true;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_POT, INPUT);
  Serial.begin(9600);
}
void loop() {
  // if (isIncreasing == true) {
  //   brightness = brightness + 20;
  // }
  // else {
  //   brightness = brightness - 20;
  // }

  // //check bounds
  // if (brightness >= 255) {
  //   isIncreasing = false;
  //   brightness = 255;
  // }
  // else if (brightness <= 0) {
  //   isIncreasing = true;
  //   brightness = 0;
  // }


  // analogWrite(PIN_LED, brightness);
  // Serial.println("Brightness = " + String(brightness));
  // delay(200);

  //read pot
  int potVal = analogRead(PIN_POT);
  
  // int pwmVal = potVal / 4095 * 255; //incorrect math
  // int pwmVal = potVal / 4095.0 * 255; 
  int pwmVal = float(potVal) / 4095 * 255;


  Serial.println("potVal = " + String(potVal) + " pwmVal = " + String(pwmVal));
  analogWrite(PIN_LED, pwmVal);
  //as a general rule, if we are going to constantly print inside, we should some of kind of delay
  delay(200);

  //use the pot to control the LED brightness
  //hint: consider the ranges of pot and LED PWM


}

/*
    int pwmVal = potVal / 4095 * 255;  ---> 
      pwm = 0

    in c++, dividion of two ints is ALWAYS INTEGER DIVISION   / 
      int / int --> int
    
      solution: we force one of the numbers to be afloat

*/