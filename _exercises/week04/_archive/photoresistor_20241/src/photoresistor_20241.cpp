#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

const int PIN_PHOTO = A1;
const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15; // aka MOSI pin

/*
  how do we know what threshold ars?
    reading of 3000--what does that mean? -- meaningless

    PR is measuring relative light
    calibrate it and check for changes

    approach 1: divide 4095 into third--bottom third is dark, middle third is ambient, top third is bright

    approach 2: test and calibrate using the serial monitor
*/

const int THRESHOLD_DARK = 1500; //this specific to Rob
const int THRESHOLD_AMBIENT = 3000; 

//create a function to change led color
void changeRgb(int r, int g, int b) {
  analogWrite(PIN_RED, r);
  analogWrite(PIN_GREEN, g);
  analogWrite(PIN_BLUE, b);
}

void setup() {
  pinMode(PIN_PHOTO, INPUT);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  //part 1
  // //analog input device
  // int lightValue = analogRead(PIN_PHOTO);
  // Serial.println("Light value = " + String(lightValue));
  
  // if (lightValue >=0 && lightValue < THRESHOLD_DARK) { //dark
  //   Serial.println("\tRoom is dark");
  //   changeRgb(0,0,0);
  // }
  // else if (lightValue >= THRESHOLD_DARK && lightValue < THRESHOLD_AMBIENT) {
  //   Serial.println("\tRoom is ambient");
  //   changeRgb(0,0,255);
  // }
  // else {
  //   Serial.println("\tRoom is bright");
  //   changeRgb(255,255,255);
  // }
  
  // delay(500);



  //Part 2
  // analog input device
  int lightValue = analogRead(PIN_PHOTO);
  Serial.println("Light value = " + String(lightValue));
  // int pwmValue = map(lightValue, 0, 4095, 0, 255);   // technically correct
  int pwmValue = map(lightValue, 700, 3600, 0, 255);  

  //let's make the brightness change, but the light color should be magenta
  changeRgb(pwmValue, 0, pwmValue);


  if (lightValue >= 0 && lightValue < THRESHOLD_DARK) {  // dark
      Serial.println("\tRoom is dark");

      //send to cloud
      Particle.publish("Room Status", "dark");
      Particle.publish("Light Value", String(lightValue));    // OK because we can a burst of up to 4 message at once

      // changeRgb(0, 0, 0);
  } else if (lightValue >= THRESHOLD_DARK && lightValue < THRESHOLD_AMBIENT) {
      Serial.println("\tRoom is ambient");
      Particle.publish("Room Status", "ambient");
      Particle.publish("Light Value", String(lightValue));

      // changeRgb(0, 0, 255);
  } else {
      Serial.println("\tRoom is bright");
      Particle.publish("Room Status", "bright");
      Particle.publish("Light Value", String(lightValue));

      // changeRgb(255, 255, 255);
  }

  // delay(500);
  delay(2000);      //need longer delay for Particle.publish
}


/*
  how could use the photoresistor to vary the brightness of our LED?

  convert ADC value 0-4095  to PWM value of 0-255

  map() --> converts an input range of numbers to some output range of numbers

   outputValue =  map(INPUT_VALUE,
                      INPUT_RANGE_MIN, INPUT_RANGE_MAX,
                      OUTPUT_RANGE_MIN, OUTPUT_RANGE_MAX)

*/
