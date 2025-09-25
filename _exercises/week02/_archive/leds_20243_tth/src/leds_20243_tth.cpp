#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

/*
  Creating new project
    1) configure for device
    2) create pin labels -- globcal constant that makes it easy to refer to pins
  on Photon 2 GLOBAL variables and constants are created above setup() and
  outside of any function 3) Set the pin modes do this in setup() for every pin
  you plan to use

  PWM

  Goal: is to vary the brightness automatically from 0 to 255, then rset back to
  0 and repeat possible solutions 1) use potentiomter (come back to this) 2) for
  loop 3) while ---  DO NOT USE THIS!!!!!!! why not?  remember loop() is already
  an infinite while loop
      ** 4) use global variables and treat loop() like the infinite it really is


    use the serial monitor
    1) Serial.begin(9600) in setup
    2) SErial.println() in loop
    3) OPEN the serial monitor in workbench

    New goal is to control the LED brightness with a the pot!


*/

const int PIN_LED = A2; //define global const to refer to our LED
const int PIN_POT = A0;
int brightness = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_POT, INPUT);
}

void loop() {
    // int brightness = 0;  //wouldn't work because brightness would be reset every loop()

    // digitalWrite(PIN_LED, HIGH);    //high is 3.3v
    // delay(1000);    //1000 ms or 1 sec
    // digitalWrite(PIN_LED, LOW);     //low is 0v or ground
    // delay(2000);

    // analogWrite(PIN_LED, 85);   // 85 is 33% brightness (1/3 of 255)
    // delay(1000);
    // analogWrite(PIN_LED, 170);  // 170 is 66 %
    // delay(1000);
    // analogWrite(PIN_LED, 255);  //max
    // delay(1000);

  //   // automatic
  //   analogWrite(PIN_LED, brightness);
  //   delay(500);
  //   brightness = brightness + 20;
  //   if (brightness >= 255) {
  //       brightness = 0;
  // }

  // input range of ADC: 0-4095
  // output range of PWM: 0-255

  //read the potentiometer
  int potValue = analogRead(PIN_POT);

  // int pwmValue = potValue / 4095 * 255; // won't work
  // int pwmValue = potValue / 4095.0 * 255; // math works correctly
  int pwmValue = float(potValue) / 4095 * 255;  // math works correctly

  analogWrite(PIN_LED, pwmValue);
  Serial.println("Potentiometer value = " + String(potValue) + ", PWM value = " + String(pwmValue));

  /*
    / division is not "true division"
    int / int --> int  (throughs away any decimal)

    solution!
    make one number a float
    float / int --> float
  */
}
