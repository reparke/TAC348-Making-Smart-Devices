//every time we make a new project, first "configure project for device"
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
Everytime we start a new project, we need to:

1) configure for device
2) set out pin labels (global constants)
3) set up pin Modes (do this in setup)
4) do Serial.begin(9600) in setup()



how do we get print statements to appear
i) serial.begin(9600) in setup()
ii) use Serial.println() in loop() when you want to see  printing
iii) open the serial monitor from the command palette to see results
*/

// pin label is just constant to refer to a pin
const int PIN_LED = A2;

//global
int brightness = 0;

//runs ONCE when device first turns on
void setup() {
  pinMode(PIN_LED, OUTPUT); //says pin A2 will be output
  Serial.begin(9600); //starts Serial process
}

// loop runs forever like an infinite while loop
void loop() {

  //v1 - one LED on / off
  //turn on LED for 1 sec, and turn off for 2 sec
  // digitalWrite(PIN_LED, HIGH);  // send 3.3V or HIGH to anode of LED
  // delay(1000);  //1 sec or 1000 ms
  // digitalWrite(PIN_LED, LOW);   //send Ground or gnd or 0v or LOW to anode
  // delay(2000);

  // v2 - basic PWM
  //turn on LED full bright for 1 sec
  //go to 25% bright for half sec
  //go off for two sec
  //now we use analogWrite to vary the voltage
  // Serial.println("LED at full brightness");
  // analogWrite(PIN_LED, 255);  //255 is the max value, which 100% or 3.3v
  // // digitalWrite(PIN_LED, HIGH);
  // delay(1000);

  // Serial.println("LED at 25% brightness");
  // analogWrite(PIN_LED, 64);
  // delay(500);

  // Serial.println("LED off");
  // analogWrite(PIN_LED, 0);
  // delay(2000); 

  //v3 - auto brightness
  /*
    how could we make the LED change brightness automatically?
    - for loop with analog values
    - while loop  -- DONT DO THIS
    - loop() - variable for brightness

    we need a GLOBAL variable which is like the "memory" of our brightness
      so it will keep of the brightness over each time loop() runs
      bcz a local var would get rewritten each time loop runs
*/
    Serial.println("brightness = " + String(brightness));
    analogWrite(PIN_LED, brightness);
    brightness = brightness + 10; //increase brightness by 10
    if (brightness > 255) {
      brightness = 0;
    }
    delay(500);

}
