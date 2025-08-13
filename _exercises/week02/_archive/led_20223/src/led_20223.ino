/*
 * Rob Parke
   assign 2
   TAC 348
 */

// to control LED
// Create a constant to represent the pin
const int PIN_LED = D2;  // PIN_LED can now be used to refer to our pin D2 with
                         // the Anode of the led

// in setup, we always need to specify if our pins are INPUT or OUTPUT

void setup() {
    pinMode(PIN_LED, OUTPUT);  // other option is INPUT
}

void loop() {
    // to turn ON an LED, we need send HIGH or 3.3v to the Anode side of the LED
    //  --> we need to send HIGH to PIN_LED

    // digitalWrite(PIN_LED, HIGH);
    // delay(500); //stop the program for 500 ms (1/2 sec)
    // digitalWrite(PIN_LED, LOW);   //write LOW to anode of the LED, basically
    // turning it off delay(500);

    // half bright, full bright, half bright, off
    // analogWrite(PIN_LED, 127);   //analogwrite allows us to vary output
    // voltage from 0-255 delay(500); analogWrite(PIN_LED, 255);  //OR we use
    // digitalWrite HIGH delay(500); analogWrite(PIN_LED, 127);  // analogwrite
    // allows us to vary output voltage from 0-255 delay(500);
    // analogWrite(PIN_LED, 0);
    // delay(500);

    // for loop in C++ is like a RANGE BASED python for loop
    for (int pwmValue = 0; pwmValue <= 255; pwmValue = pwmValue + 5) {
        analogWrite(PIN_LED, pwmValue);
        delay(20);
    }
    for (int pwmValue = 255; pwmValue >= 0; pwmValue = pwmValue - 5) {
        analogWrite(PIN_LED, pwmValue);
        delay(20);
    }
}