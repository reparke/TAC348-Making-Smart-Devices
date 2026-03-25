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

Servo fanServo;
int servoAngle = 90;

int motorSpeed = 0;

/* onDataReceived() is event handler for incoming data via RX characteristic
   When the RXCharacteristic receives data, the event handler is called
   Note: uint8_t is a byte ("unsigned integer of length 8 bits")

    The command scheme is from the Adafruit Bluefruit app
    https://learn.adafruit.com/bluefruit-le-connect/controller

    ex: [‘!’] [‘B’] [‘4’] [‘1’] [CRC]
*/
// EVENT DRIVEN PROGRAMMING -- EVENT HANDLER
void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer,
                    void* context) {
    // bluetoothSerialDebug(data, len); /* uncomment for serial monitor debug */

    // make sure that enough bytes have been sent
    if (len > 4) {
        // turn on LED when button 1 is pressed in app
        //  ! B 1 1
        if (data[0] == '!' && data[1] == 'B' && data[2] == '1' &&
            data[3] == '1') {
            digitalWrite(PIN_LED, HIGH);
            delay(100);
            digitalWrite(PIN_LED, LOW);
            delay(100);
        }
        // keep the LED on while 2 is pressed, turn off LED when 2 button is
        // released
        // ! B 2 1 turn on led
        // ! B 2 0 turn off led
        if (data[0] == '!' && data[1] == 'B' && data[2] == '2' &&
            data[3] == '1') {
            digitalWrite(PIN_LED, HIGH);
        }
        if (data[0] == '!' && data[1] == 'B' && data[2] == '2' &&
            data[3] == '0') {
            digitalWrite(PIN_LED, LOW);
        }
        //servo
        if (data[0] == '!' && data[1] == 'B' && data[2] == '7' &&
            data[3] == '1') {
            servoAngle += 10;
            if (servoAngle >= 165) {
                servoAngle = 165;
            }
            fanServo.write(servoAngle);
        }
        // servo
        if (data[0] == '!' && data[1] == 'B' && data[2] == '8' &&
            data[3] == '1') {
            servoAngle -= 10;
            if (servoAngle <= 15) {
                servoAngle = 15;
            }
            fanServo.write(servoAngle);
        }
        //dc motor
        if (data[0] == '!' && data[1] == 'B' && data[2] == '5' &&
            data[3] == '1') {
                motorSpeed += 10;
                if (motorSpeed >= 255) {
                    motorSpeed = 255;
                }
                digitalWrite(AIN1, HIGH);
                digitalWrite(AIN2, LOW);
                analogWrite(PWMA, motorSpeed, 50);  //don't forget to set freq to make servo work
        }
        // dc motor
        if (data[0] == '!' && data[1] == 'B' && data[2] == '6' &&
            data[3] == '1') {
            motorSpeed -= 10;
            if (motorSpeed <= 0) {
                motorSpeed = 0;
            }
            digitalWrite(AIN1, HIGH);
            digitalWrite(AIN2, LOW);
            analogWrite(PWMA, motorSpeed,
                        50);  // don't forget to set freq to make servo work
        }
    }
}

/*
* When "RIGHT" is pressed down, rotate servo (by fixed amount) clockwise
* When "LEFT" is pressed down, rotate servo (by fixed amount)  counter clockwise
* When "UP" is pressed down, speed up motor (by fixed amount)
* When "DOWN" is pressed down, slow motor(by fixed amount)
* Optional challenge:
  * When "3" is pressed down, change direction of DC motor
  * When "4" is pressed, turn on fan auto mode

*/
/********************************************************************************/

// we don't need to put any code in loop (today)

void setup() {
    argon_ble_setup();  // BLE setup

    pinMode(PIN_LED, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);

    Serial.begin(9600);
    fanServo.attach(PIN_SERVO);
}

void loop() {}
