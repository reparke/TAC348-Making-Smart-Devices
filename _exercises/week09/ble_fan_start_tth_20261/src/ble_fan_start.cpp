#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#include "particle_ble_setup.h"
/*
Use Adafruit Bluefruit app
(https://learn.adafruit.com/bluefruit-le-connect/controller)
Connect to Argon -> controller

- control fan motor and servo
- use controller flash on-board LED
- use color picker to change LED

RGB LED (common cathode)
R - A2
G - A1
B - A0

Servo: D2
On-board LED - D7

Specifications

* When "1" is pressed down, on-board LED D7 will blink twice
* When "2" is pressed down, on-board LED D7 will turn on
* When "2" is released, on-board LED D7 will turn off

* When "RIGHT" is pressed down, rotate servo (by fixed amount) clockwise
* When "LEFT" is pressed down, rotate servo (by fixed amount)  counter clockwise
* When "UP" is pressed down, speed up motor (by fixed amount)
* When "DOWN" is pressed down, slow motor(by fixed amount)
* Optional challenge:
  * When "3" is pressed down, change direction of DC motor
  * When "4" is pressed, turn on fan auto mode

*/

const int PIN_RED = D15;    // aka MOSI
const int PIN_GREEN = D16;  // aka MISO
const int PIN_BLUE = D1;    // aka SCL

const int PIN_LED = D7;

const int PIN_SERVO = A2;

const int AIN1 = D3;
const int AIN2 = D4;
const int PWMA = A5;

const int MOTOR_DELTA = 15;
const int SERVO_DELTA = 15;

Servo servo;
int servoPosition = 90;  // range of 15-165

int motorSpeed = 0;

bool isFanSpinningForward = true;

// fan auto mode variables
bool isFanAutomaticMode = false;
unsigned long prevMillis = 0;
unsigned long INCREMENT_TIMER = 20;
bool isServoPosIncreasing = true;  // direction

void spinFanForward() {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
}
void spinFanBackward() {
    digitalWrite(AIN2, HIGH);
    digitalWrite(AIN1, LOW);
}

void fanAuto() {
    unsigned long curMillis = millis();

    if (curMillis - prevMillis > INCREMENT_TIMER) {
        Serial.println("in fan auto millis");

        prevMillis = curMillis;
        // what direction are we going--> increment or decrement
        // check that we dont go above 165 or below 15
        if (isServoPosIncreasing == true) {
            servoPosition++;  // C++ notation to add 1
            servo.write(servoPosition);
            if (servoPosition >= 165) {
                isServoPosIncreasing = false;
            }
        } else {
            servoPosition--;  // C++ notation to subrat 1
            servo.write(servoPosition);
            if (servoPosition <= 15) {
                isServoPosIncreasing = true;
            }
        }
    }
}

/*  Sample Code to communicate from Argon to Adafruit Bluefruit app
    https://learn.adafruit.com/bluefruit-le-connect/controller

    The command scheme is from the Adafruit Bluefruit app
    ex: [‘!’] [‘B’] [‘4’] [‘1’] [CRC]
*/

// onDataReceived() is event handler for incoming data via RX characteristic
// When the RXCharacteristic receives data, the event handler is called
// Note: uint8_t is a byte ("unsigned integer of length 8 bits")
void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer,
                    void* context) {
    bluetoothSerialDebug(data, len); /* uncomment for serial monitor debug */
                                     // String: String msg = "hello"
    // char:   char letter = 'h';  '%'   'Y'    '5'
    // this function gets called WHEN YOU PRESS a button on the bluefruit app
    // data is an array of chars
    // our gooal is to write if statements to identify which button was pressed
    // and take approprioate action

    if (len > 4) {
        // when 1 button is pressed, lets blink the onboard LED
        // ! B 1 1
        if (data[0] == '!' && data[1] == 'B' && data[2] == '1' &&
            data[3] == '1') {
            digitalWrite(PIN_LED, HIGH);
            delay(100);
            digitalWrite(PIN_LED, LOW);
            delay(100);
        }
        // when button two is pressed (and held down), LED should stay on,
        // otherwise its off
        //  ! B 2 1 --> pressing button 2 --> turn on LED
        //  ! B 2 0 --> releasing button 2 --> turn off LED
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '2' &&
                 data[3] == '1') {
            digitalWrite(PIN_LED, HIGH);
        } else if (data[0] == '!' && data[1] == 'B' && data[2] == '2' &&
                   data[3] == '0') {
            digitalWrite(PIN_LED, LOW);
        }

        else if (data[0] == '!' && data[1] == 'B' && data[2] == '5' &&
                 data[3] == '1') {
            // press up arrow to increase speed
            motorSpeed = motorSpeed + MOTOR_DELTA;
            if (motorSpeed > 255) {
                motorSpeed = 255;
            }
            digitalWrite(AIN1, HIGH);
            digitalWrite(AIN2, LOW);
            analogWrite(PWMA, motorSpeed, 50);  // added for Photon 2 single PWM timer
        } else if (data[0] == '!' && data[1] == 'B' && data[2] == '6' &&
                   data[3] == '1') {
            // press down arrow to decrease speed
            motorSpeed = motorSpeed - MOTOR_DELTA;
            if (motorSpeed < 0) {
                motorSpeed = 0;
            }
            digitalWrite(AIN1, HIGH);
            digitalWrite(AIN2, LOW);
            analogWrite(PWMA, motorSpeed,
                        50);  // added for Photon 2 single PWM timer
        } else if (data[0] == '!' && data[1] == 'B' && data[2] == '7' &&
                   data[3] == '1') {
            isFanAutomaticMode = false;  // only if implementing full auto
            // 7 is left arrow so servo
            servoPosition = servoPosition + 15;
            if (servoPosition > 165) {
                servoPosition = 165;
            }
            servo.write(servoPosition);
        } else if (data[0] == '!' && data[1] == 'B' && data[2] == '8' &&
                   data[3] == '1') {
            isFanAutomaticMode = false;  // only if implementing full auto

            // 8 is right arrow so servo
            servoPosition = servoPosition - 15;
            if (servoPosition < 15) {
                servoPosition = 15;
            }
            servo.write(servoPosition);
        }

        // optional
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '3' &&
                 data[3] == '0') {
            isFanSpinningForward = !isFanSpinningForward;
            if (isFanSpinningForward == true) {
                spinFanForward();
            } else {
                spinFanBackward();
            }
        } else if (data[0] == '!' && data[1] == 'B' && data[2] == '4' &&
                   data[3] == '0') {
            isFanAutomaticMode = !isFanAutomaticMode;
        }
    }
}

void setup() {
    /* === START BLE SETUP === */
    argon_ble_setup();
    /* === END BLE SETUP === */
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);

    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    Serial.begin(9600);

    servo.attach(PIN_SERVO);
    servo.write(servoPosition);

    analogWrite(PWMA, motorSpeed, 50);
    spinFanForward();
}

void loop() {
    if (isFanAutomaticMode == true) {
        fanAuto();
    }
}