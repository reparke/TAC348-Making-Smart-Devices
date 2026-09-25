#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
  four things we do when starting every new project?
  1) configure project for device
  2) create pin labelws
  3) set up pin mode
  4) set up Serial

  setup() runs once
  loop() runs forever, and very fast
*/

// pin labels are global constants
const int PIN_LED = A2;
const int PIN_POT = A0;

// pin mode and serial are in setup()
void setup() {
    Serial.begin(9600);
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_POT, INPUT);
}

void loop() {

  /*
    what is does potVal actually represent?
      ex: potVal = 4.....4 what?

      ideas:
        volts
        bits
        --> "digital value" or it has no unit

        it is the conversion of 
          volt range input: 0V to 3.3V
          ADC range output: 0 to 4095

        
      ADC
        converts analog INPUT to digital value
        ADC range: 0 - 4095

      PWM
        analog OUTPUT
        pwm values: 0 - 255

    lab:
      make the pot control the LED brightness
  */
  // lets read from the potentiometer
  int potVal = analogRead(PIN_POT);


  // int pwmVal = potVal * 255 / 4095;
  // int pwmVal = potVal / 4095 * 255;   // why did this break?


  /* 
    C++ discussion
    / is division but when we have  
        int / int  ----> int  (integer division)

      if potVal is 3000, then 3000/4095 = 0
      --> we need to make sure the division gives us a float result
  */
  // int pwmVal = potVal / 4095.0 *255;
    // works because   int / float --> float

    int pwmVal = float(potVal) / 4095 * 255;  
    //works because we have   float /  int ---> float


  //ADC converts a voltage (0-3.3v) to ADC val (0-4095)
  //convert ADC to PWM  -->  0-4095 to 0-255

  analogWrite(PIN_LED, pwmVal);

  Serial.println("potVal = " + String(potVal) + ", pwmVal = " + String(pwmVal));
  Particle.publish("pot", String(potVal));
  Particle.publish("pwm", String(pwmVal));

  //for now only, we want to slow loop() down a little
  // delay(200);
  delay(1000);  //only publish to cloud once per sec

  //serial monitor shows serial messages, NOT publish cloud events

}
