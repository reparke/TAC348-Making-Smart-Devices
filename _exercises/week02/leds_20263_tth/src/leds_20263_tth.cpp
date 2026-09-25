#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/* Steps each time we make a new proj
0) Login - only do this every two months
1) configure our proj for device
2) create pin labels
    --global constants that refer to pin on the photon
3) set our pin Modes --input or output in setup()
4) Serial.begin(9600) in setup()


how to use print statements?
i) setup(): serial.begin(9600)
ii) loop(); use Serial.println() to print out text
iii) open up serial monitor from command paletter

*/

// pin labels
const int PIN_LED = A2;

// global var
int brightness = 0;

void setup() {
    pinMode(PIN_LED, OUTPUT);
    Serial.begin(9600); //sets up serial object to receive data
}
void loop() {
    // //v1 - basic led
    // //have led on for 1 sec, and off for 2 sec
    // digitalWrite(PIN_LED, HIGH);  //send 3.3V or HIGH to led anode
    // delay(1000);    //pause for 1 sec or 1000 ms
    // digitalWrite(PIN_LED, LOW);   //send 0v or LOW to led anode
    // delay(2000);

    // //v2 - PWM
    // // led on full bright for 1 sec
    // // led on 25% bright for 0.5 sec
    // // led off for 2 sec
    // analogWrite(PIN_LED, 255);    //same as digitalWrite(PIN_LED, HIGH)
    // delay(1000);
    // analogWrite(PIN_LED, 64);
    // delay(500);
    // analogWrite(PIN_LED, 0);    //same as digitalWrite(PIN_LED, LOW)
    // delay(2000);

    // v3 - auto brightness
    /*
      lets say we want the LED to automatically get brighter? how can we do
    this? 1) for loop 2) while loop 3) void loop() because it runs forever <----


    lets use void loop() to make the LED brighter
    - if / else
    - define a variable that is brightness and can be updated
        ---> local or global var?



    quick aside: what is a local vs global var?
    - local: exists ONLY in the func where it was defined
             its value resets everytime the func runs
    - global: declared OUTSIDE of any func, and retains is value throughout the
    program like "memory"

    */
    Serial.println("brightness = " + String(brightness)); //print out brightness
    analogWrite(PIN_LED, brightness);
    brightness = brightness + 10;  // increase brightness
    if (brightness >= 255) {
        brightness = 0;
    }

    delay(200);
}
