#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;  // photon say "MO"
const int PIN_PHOTORESISTOR = A1;


/*
  Photoresistor
    purpose is that change resistance when exposed to light
      analog
    analogRead --> ADC range 0 - 4095  

  using the PR, what does a value of 3000 mean?
    NOTHING
    RELATIVE measuring device

    need to calibrate to have any meaning


*/
const int THRESHOLD_DARK = 1000;
const int THRESHOLD_AMBIENT = 2600; //yours will be different

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_PHOTORESISTOR, INPUT);
    Serial.begin(9600);
}

void loop() {
  int lightValue = analogRead(PIN_PHOTORESISTOR);

  //how do we know what is dark, bright, ambient?
  //0-4095
  //ambient
  //dark - cover sensor
  //bright - phone flash light

  //change the fixed resistor val, you can shift ranges
  //    replace the 4.7K resistor to something else

  // lets say we want the brightness of the sensor to control the brightness of
  // the LED
  /*
    two ways do this
    1) with a simply calculation
    2) MAP function!

    outVal = map(inVal, inMin, inMax, outMin, outMax)

  */
 int pwmVal = map(lightValue, 0, 4095, 0, 255);   //full version
 changeRgbLed(255, pwmVal,pwmVal);
 String lightLabel = "";  

  if (lightValue >= 0 && lightValue < THRESHOLD_DARK) {
    Serial.println("Dark:  PR val = " +String(lightValue));
    // changeRgbLed(0,0,0);
    lightLabel = "dark";
  }

  else if(lightValue >= THRESHOLD_DARK && lightValue < THRESHOLD_AMBIENT) {
    Serial.println("Ambient: PR Val = " + String(lightValue));
    // changeRgbLed(255, 120, 0);
    lightLabel = "ambient";
  }
  else {
    Serial.println("Bright: PR val = " + String(lightValue));
    // changeRgbLed(255,255,255);
    lightLabel = "bright";
  }

  Particle.publish("Label", lightLabel);
  Particle.publish("Reading", String(lightValue));
  //we don't want this publishing more than once per second

  delay(5000); 


}