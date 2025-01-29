#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);

SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

/*
 new projects
 1) configure for device
 2) set pin labels
 3) pin modes
 4) Serial.begin */

const int PIN_LED = A2;
const int PIN_BUTTON = D2;

int counter = 0;  // global
int prevButtonVal = HIGH;
bool isLedOn = false;

void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}

void loop() {
    // v1
    // read button
    // int buttonVal = digitalRead(PIN_BUTTON);
    // Serial.println("Button val = " + String(buttonVal));
    // if (buttonVal == LOW) {  //button pressed
    //   digitalWrite(PIN_LED, HIGH);
    // }
    // else { // button released
    //   digitalWrite(PIN_LED, LOW);
    // }

    // v2
    // create a counter
    // increment the counter everytime the button is pressed and also display
    // the counter value
//     int buttonVal = digitalRead(PIN_BUTTON);
//     if (buttonVal == LOW) {  // pressed
//         counter = counter + 1;
//         digitalWrite(PIN_LED, HIGH);
//         Serial.println("Counter = " + String(counter));
//     } else {
//         digitalWrite(PIN_LED, LOW);
//     }
  
  //v3
  int currButtonVal = digitalRead(PIN_BUTTON);
  //need to know what the button val was LAST TIME in the loop--> global
  //what counts as press?  cur is LOW and prev is HIGH
  //in C++, "and" is &&
  if (currButtonVal == LOW && prevButtonVal == HIGH) {
    if (isLedOn == true) {
      isLedOn = false; //change state
      digitalWrite(PIN_LED, LOW);
    }
    else {
      isLedOn = true;
      digitalWrite(PIN_LED, HIGH);
    }
    //button was pressed ONE time
    counter = counter + 1;
    Serial.println("Counter = " + String (counter));
  }

  //VERY IMPORTANT!
  // when building latch code, make sure that we update prevButtonVal at the very end of the loop
  prevButtonVal = currButtonVal;

  //v4 
  // what we wanted one button press/release to turn LED On
  // and the next button press/release to turn off
  //this is a TOGGLE
  // one way is to read the LED state and adjust accordingly
  //--> we create var to track the STATE of the LED (is on or off)
}
