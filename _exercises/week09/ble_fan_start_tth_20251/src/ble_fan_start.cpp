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

int motorSpeed = 0;
int fanAngle = 90;

// servo step 1
Servo fanServo;

/* onDataReceived() is event handler for incoming data via RX characteristic
   When the RXCharacteristic receives data, the event handler is called
   Note: uint8_t is a byte ("unsigned integer of length 8 bits")

    The command scheme is from the Adafruit Bluefruit app
    https://learn.adafruit.com/bluefruit-le-connect/controller

    ex: [‘!’] [‘B’] [‘4’] [‘1’] [CRC]

quick notes about C++
    -characters and strings
    character: is ONE SINGLE symbol and uses ' '
    string: can be MANY symbols togeher and uses " "

ex: release button 2
        0     1    2    3
data = ['!', 'B', '2', '0']
*/
void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer,
                    void* context) {
    // bluetoothSerialDebug(data, len); /* uncomment for serial monitor debug */

    if (len > 4) {
        // blink LED when button 1 is pressed
        // code: ! B 1 1
        if (data[0] == '!' && data[1] == 'B' && data[2] == '1' &&
            data[3] == '1') {
            digitalWrite(PIN_LED, HIGH);
            delay(500);
            digitalWrite(PIN_LED, LOW);
            delay(500);

        }
        // turn on LED when button 2 is pressed, turn OFF led when button 2 is
        // released
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '2' &&
                 data[3] == '1') {  // button 2 is pressed
            digitalWrite(PIN_LED, HIGH);
        } else if (data[0] == '!' && data[1] == 'B' && data[2] == '2' &&
                   data[3] == '0') {  // button 2 released
            digitalWrite(PIN_LED, LOW);
        }
        // up button is pressed
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '5' &&
                 data[3] == '1') {
            motorSpeed += 10;
            if (motorSpeed >= 255) {
                motorSpeed = 255;
            }
            digitalWrite(AIN1, HIGH);
            digitalWrite(AIN2, LOW);
            // analogWrite(PWMA, motorSpeed);
            // when using servo and DC motor in the same project,
            // the dc motor analogwrite needs a third param of 50
            analogWrite(PWMA, motorSpeed, 50);
        }
        // down button is pressed
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '6' &&
                 data[3] == '1') {
            motorSpeed -= 10;
            if (motorSpeed <= 0) {
                motorSpeed = 0;
            }
            digitalWrite(AIN1, HIGH);
            digitalWrite(AIN2, LOW);
            // analogWrite(PWMA, motorSpeed);
            // when using servo and DC motor in the same project,
            // the dc motor analogwrite needs a third param of 50
            analogWrite(PWMA, motorSpeed, 50);
        }
        // right arrow button is '8'
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '8' &&
                 data[3] == '1') {
            fanAngle += 5;
            // what is actual range of servo angle? 0-180
            // what is the safe range of servo?     15-165
            if (fanAngle >= 165) {
                fanAngle = 165;
            }
            fanServo.write(fanAngle);
        }

        // left arrow button is '7'
        else if (data[0] == '!' && data[1] == 'B' && data[2] == '7' &&
                 data[3] == '1') {
            fanAngle -= 5;
            // what is actual range of servo angle? 0-180
            // what is the safe range of servo?     15-165
            if (fanAngle <= 15) {
                fanAngle = 15;
            }
            fanServo.write(fanAngle);
        }
    }
}
/********************************************************************************/

/*
 * When "RIGHT" is pressed down, rotate servo (by fixed amount)
 * clockwise When "LEFT" is pressed down, rotate servo (by fixed amount)
 * counter clockwise When "UP" is pressed down, speed up motor (by fixed
 * amount) When "DOWN" is pressed down, slow motor(by fixed amount)
 * Optional
 */

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
