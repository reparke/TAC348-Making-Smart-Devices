/*
 * Project myProject
 * Author: Your Name
 * Date:
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

/* when creating new project always
 1) config for device
  2) create pin lab (const int)
  3) set pinmode (output/input)
  4) serial.begin
*/

const int PIN_LED1 = D3;
const int PIN_LED2 = D4;
const int PIN_BUTTON = D2;
int count = 0;
int prevButtonVal = LOW;

// setup() runs once, when the device is first turned on
void setup() {
    // Put initialization like pinMode and begin functions here
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    // // v1
    //   int buttonVal = digitalRead(PIN_BUTTON); // what val to expect? high or
    //   low, 0 or 1 Serial.println("Button val = " + String(buttonVal));

    //   // use button to turn on LED1 (when pressed led is on, unpresed is off)
    //   if (buttonVal == LOW) {
    //     digitalWrite(PIN_LED1, HIGH);

    //   } else {
    //     digitalWrite(PIN_LED1, LOW);
    //   }
    //   delay(100);

    // // v2
    // // create an int counter var
    // // everytime you press button, increment the counter and print out
    // current value int buttonVal = digitalRead(PIN_BUTTON); // what val to
    // expect? high or low, 0 or 1

    // // Serial.println("Button val = " + String(buttonVal));
    // // use button to turn on LED1 (when pressed led is on, unpresed is off)
    //    if (buttonVal == LOW) {
    //     digitalWrite(PIN_LED1, HIGH);
    //     count = count + 1;
    //     Serial.println("Button count = " + String(count));
    //    } else {
    //      digitalWrite(PIN_LED1, LOW);
    //    }
    //    delay(100);

    // }

    // v3 - button latch
    int currButtonVal = digitalRead(PIN_BUTTON);
    // when is a button first pressed
    if (currButtonVal == LOW) {  // falling edge--button was just pressed
        count = count + 1;
        Serial.println("Counter = " + String(count));
    }
    // one last thing for a latch
    // at the end of the loop OUTSIDE your if statement, update prevbutton
    prevButtonVal = currButtonVal;
}
// #include "Particle.h"

// SYSTEM_MODE(AUTOMATIC);

// SYSTEM_THREAD(ENABLED);
// SerialLogHandler logHandler(LOG_LEVEL_INFO);

// /*
//   when creating a new project, we always do this
//   1) config for device
//   2) create pin label (const int)
//   3) set pinmode (output / input)
//   4) serial.begin
// */

// const int PIN_LED1 = D3;
// const int PIN_LED2 = D4;
// const int PIN_BUTTON = D2;

// int counter = 0;
// int prevButtonVal = HIGH;
// bool isLed1On = false;

// void setup() {
//     pinMode(PIN_LED1, OUTPUT);
//     pinMode(PIN_LED2, OUTPUT);
//     pinMode(PIN_BUTTON, INPUT);
//     Serial.begin(9600);
// }

// // use the button to turn on LED1 (when pressed, led is on, not pressed led1 is
// // off )
// void loop() {
//     // //version 1
//     // int buttonVal = digitalRead(PIN_BUTTON);  // what values to expect? 0  or
//     // 1 , HIGH or LOW Serial.println("Button val = " + String(buttonVal)); if
//     // (buttonVal == LOW) {
//     //   digitalWrite(PIN_LED1, HIGH);
//     // }
//     // else {
//     //   digitalWrite(PIN_LED1, LOW);
//     // }

//     // delay(100);

//     // version 2
//     //  create a int counter var
//     //  everytime you press the button, increment counter and print out the
//     //  current val int buttonVal = digitalRead(PIN_BUTTON); if (buttonVal ==
//     //  LOW) {
//     //    counter = counter + 1; //same as counter++
//     //    Serial.println("Counter = " + String(counter));
//     //  }

//     // //version 3 - button latch
//     // int currButtonVal = digitalRead(PIN_BUTTON);
//     // //when is a button first pressed
//     // if (currButtonVal == LOW && prevButtonVal == HIGH){ // falling
//     // edge--button was just pressed
//     //   counter = counter + 1;
//     //   Serial.println("Counter = " + String(counter));
//     // }
//     // //one last thing for a latch
//     // //at the end of the loop OUTSIDE your if statement, update prevbutton
//     // prevButtonVal = currButtonVal;

//     // version 4
//     //  use latch
//     // press button, LED1 turns on and STAYS on when you release button
//     // pres button again, LED1 turns off and stays off
//     // toggling led
//     int currButtonVal = digitalRead(PIN_BUTTON);
//     // when is a button first pressed
//     if (currButtonVal == LOW &&
//         prevButtonVal == HIGH) {  // falling edge--button was just pressed
//         if (isLed1On == true) {
//             isLed1On = false;
//             digitalWrite(PIN_LED1, LOW);
//         } else {
//             isLed1On = true;
//             digitalWrite(PIN_LED1, HIGH);
//         }
//     }
//     // one last thing for a latch
//     // at the end of the loop OUTSIDE your if statement, update prevbutton
//     prevButtonVal = currButtonVal;
// }

// /*
//   ideas
//     use counter
//     use a flag (boolean var)

// */