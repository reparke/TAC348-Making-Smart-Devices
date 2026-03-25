#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);


// motor pins
const int AIN1 = D3;  // controls motor dir
const int AIN2 = D4;  // controls motor dir
const int PWMA = MISO;  // controls motor speed

// pot
const int PIN_POT = A1;

// servo
const int PIN_SERVO = A5;

// create servo object
Servo fanServo;

/*
 how could we make a working desk fan?
    1) pot controls the speed, and fan rotates back and forth continuously
    2) map out from high low of the pot ranges
*/

int fanAngle = 0;              // servo rotation
unsigned long prevMillis = 0;  // last rotation time
bool isFanIncreasing = true;   // is the fan angle increasing or decreasing?

void basicServo() {
    // range of values for servos?
    // 0-180 is technically the full range
    // however, 15-165 is a safe zone
    fanServo.write(15);  // rotate servo to 15 degrees
    delay(1000);
    fanServo.write(90);  // rotate servo to 90 degrees
    delay(1000);
    fanServo.write(165);
    delay(1000);
}
void potControlServo() {
    int potVal = analogRead(PIN_POT);
    int servoAngle = map(potVal, 0, 4095, 15, 165);
    fanServo.write(servoAngle);
}
void basicMotor() {
    /*
        AIN1            AIN2
        H               L           motor will spin in a direction
        L               H           motor will spin in opposite direction
        L               L           motor will stop
        H               H           DAMAGE!

        PWMA  0-255
    */
    // motor to spin one direction at full speed
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 255);
    delay(5000);
    // motor spins opposite direction at half speed
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 127);
    delay(5000);
    // turn off the motor
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 0);
    delay(5000);
}

// use the potentiometer to control motor speed
void potControlDcMotor() {
    // set one direction
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 100);

    // write the code in the next 3-5 min
    // int potVal = analogRead(PIN_POT);
    // int pwm = map(potVal, 0, 4095, 0, 255);
    // analogWrite(PWMA, pwm);
}

void simpleFan() {
    // delay is not desireable
    /*
        millis timer for fan
        - read pot and map to fan speed
        - every 1 sec, check pot value and change fan speed accoringly

        - set rotating interval with millis
        - every sec change the angle
    */

    // when should we change the speed of the fan?
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > 1000) {
        prevMillis = curMillis;

        if (isFanIncreasing == true) {
            fanAngle = fanAngle + 15;
        } else {
            fanAngle = fanAngle - 15;
        }
        fanServo.write(fanAngle);
        // switch rotation direction
        if (fanAngle > 165) {
            isFanIncreasing = false;  // start decreasing
        } else if (fanAngle < 15) {
            isFanIncreasing = true;  // start increasing
        }
    }
    // outside millis
    potControlDcMotor();
}
void simpleFanWithDelay() {
    // have the fan rotate automatically, and the pot controls the speed of the
    // fan blade rotation two ways! for loop, OR millis timer
    for (int servoPos = 15; servoPos <= 165; servoPos = servoPos + 5) {
        fanServo.write(servoPos);
        Serial.println("Servo pos = " + String(servoPos));
        potControlDcMotor();
        delay(1000);
    }
    for (int servoPos = 165; servoPos >= 15; servoPos = servoPos - 5) {
        fanServo.write(servoPos);
        Serial.println("Servo pos = " + String(servoPos));

        potControlDcMotor();
        delay(1000);
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(PIN_POT, INPUT);
    pinMode(AIN1, OUTPUT);  // input TO THE CONTROLLER from the ARGON
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);

    // attach the servo object to our pin
    fanServo.attach(PIN_SERVO);  // we don't use PINMODE with servo
}

void loop() {
    // simpleFan();
    simpleFanWithDelay();
    // potControlServo();
    // basicServo();
    // potControlDcMotor();
    // basicMotor();
}
