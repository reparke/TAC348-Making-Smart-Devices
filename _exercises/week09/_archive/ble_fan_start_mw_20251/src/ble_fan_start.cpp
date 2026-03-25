#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// bluetooth setup code
#include "particle_ble_setup.h"

// on board LED
const int PIN_LED = D7;

// Servo
const int PIN_SERVO = A2;

// pot
const int PIN_POT = A1;

// motor pins
const int AIN1 = D3;
const int AIN2 = D4;
const int PWMA = A5;

// create Servo - step 1
Servo servoObj;
int fanAngle = 90;

int motorSpeed = 0;

/* onDataReceived() is event handler for incoming data via RX characteristic
   When the RXCharacteristic receives data, the event handler is called
   Note: uint8_t is a byte ("unsigned integer of length 8 bits")

    The command scheme is from the Adafruit Bluefruit app
    https://learn.adafruit.com/bluefruit-le-connect/controller

    ex: [‘!’] [‘B’] [‘4’] [‘1’] [CRC]

    in C++, a character is a SINGLE LETTER and uses ' '
    a string can be many characters and uses " "
*/
void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer,
                    void* context) {
    // bluetoothSerialDebug(data, len); /* uncomment for serial monitor debug */

    // data is just an array of characters (single letter strings)
    if (len > 4) {  // our command is 4 bytes (e.g ! B 1 1)

        // turn on LED when button 1 is pressed
        //  ! B 0 1
        if (data[0] == '!' && data[1] == 'B' && data[2] == '1' &&
            data[3] == '1') {
            digitalWrite(PIN_LED, HIGH);
            delay(100);
            digitalWrite(PIN_LED, LOW);
            delay(100);
        }
        // keep led on while button 2 is pressed
        // turn off led when button 2 is released
        //  ! B 2 1 -> button 2 pressed
        //  ! B 2 0 -> button 2 is released
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '2' &&
                 data[3] == '1') {  // button 2 press
            digitalWrite(PIN_LED, HIGH);

        } else if (data[0] == '!' && data[1] == 'B' && data[2] == '2' &&
                   data[3] == '0') {  // button 2 release
            digitalWrite(PIN_LED, LOW);
        }
        // When "RIGHT" is pressed down, rotate servo (by fixed amount)
        // clockwise
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '8' &&
                 data[3] == '1') {
            fanAngle += 10;
            // true range of servo:  0-180
            // safe range for servo: 15-165
            if (fanAngle >= 165) {
                fanAngle = 165;
            }
            servoObj.write(fanAngle);

        }
        // left
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '7' &&
                 data[3] == '1') {
            fanAngle -= 10;
            // true range of servo:  0-180
            // safe range for servo: 15-165
            if (fanAngle <= 15) {
                fanAngle = 15;
            }
            servoObj.write(fanAngle);
        }
        // up
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '5' &&
                 data[3] == '1') {
            motorSpeed += 10;
            if (motorSpeed >= 255) {
                motorSpeed = 255;
            }
            digitalWrite(AIN1, HIGH);
            digitalWrite(AIN2, LOW);
            //NOTE! when we have DC MOTOR and SERVO in the same device,
            //we need to use a different version of analogWrite
            // analogWrite(PWMA, motorSpeed);
            analogWrite(PWMA, motorSpeed, 50);
        }
        // down
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '6' &&
                 data[3] == '1') {
            motorSpeed -= 10;
            if (motorSpeed <= 0) {
                motorSpeed = 0;
            }
            digitalWrite(AIN1, HIGH);
            digitalWrite(AIN2, LOW);
            // analogWrite(PWMA, motorSpeed);
            analogWrite(PWMA, motorSpeed, 50);
        }
    }
}
/********************************************************************************/

/*
 * When "RIGHT" is pressed down, rotate servo (by fixed amount) clockwise
 * When "LEFT" is pressed down, rotate servo (by fixed amount)  counter
 * clockwise When "UP" is pressed down, speed up motor (by fixed amount)
 * When "DOWN" is pressed down, slow motor(by fixed amount) Optional
 * challenge: When "3" is pressed down, change direction of DC motor
 */

void setup() {
    argon_ble_setup();  // BLE setup

    pinMode(PIN_LED, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);

    Serial.begin(9600);

    servoObj.attach(PIN_SERVO);
}

void loop() {}
