#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);

SYSTEM_THREAD(ENABLED);
// SerialLogHandler logHandler(LOG_LEVEL_INFO);
SerialLogHandler logHandler(LOG_LEVEL_WARN);
//if you want to limit the debug messages in the serial monitor
// use LOG_LEVEL_WARN instead of LOG_LEVEL_INFo

/*
open new project
  - declare pin as const
  - set pinmode
  - configure device
  - serial.begin
*/

const int PIN_LED1 = D3;
const int PIN_LED2 = D4;
const int PIN_BUTTON = D2;

int counter = 0;
int prevButtonVal = HIGH;   //do this to start tracking button presses

void setup() {
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  Serial.begin(9600);       //"turns on" the Serial object, which allows the Photon
                            // to send text data to Workbench ALWAYS over USB which will show in the serisl mon
                            //9600 is the speed (bits per second)

}
// use the button to turn on the LED --> button press and led on, button off and led off
// create a counter (int) and everytime you press the button, add one to the counter
//  and print out the counter value

void loop() {
  //version 1: no latch
  //read button-- which function?
  // int buttonVal = digitalRead(PIN_BUTTON);

  // Serial.println("Button value = " + String(buttonVal));


  // //button == LOW --> pressed
  // //button == HIGH --> not pressed
  // if (buttonVal == LOW) {         
  //   digitalWrite(PIN_LED1, HIGH);
  //   counter = counter + 1; //or counter++;
  //   Serial.println("Counter value = " + String(counter));
  // }
  // else { //buttonVal == HIGH
  //   digitalWrite(PIN_LED1, LOW);

  // }
  // delay(100);


  ///version 2: button latch
  int currButtonVal = digitalRead(PIN_BUTTON);
  // button press means curbuttonval is LOW and prevbuttonval is HIGH
  if (currButtonVal == LOW && prevButtonVal == HIGH) {
    //Hooray! we know the button was just pressed
    counter = counter + 1;
    Serial.println(counter);
  }
  //make sure to update prevbutton
  prevButtonVal = currButtonVal;
  delay(100);
}

/*
  Button Latch
    latch allows ONE PHYSICAL PRESS to register in our code as a SINGLE PRESS 
*/