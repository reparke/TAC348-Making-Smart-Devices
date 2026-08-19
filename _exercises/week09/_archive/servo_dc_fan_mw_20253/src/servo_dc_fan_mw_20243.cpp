
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// motor pins
const int AIN1 = D3;  // motor dir
const int AIN2 = D4;  // motor dir
const int PWMA = A5;  // speed

// pot
const int PIN_POT = A1;

// photon --> motor driver --> motor

// servo step 1: create servo obj
Servo servoObj;
const int PIN_SERVO = A2;

// fan
int servoAngle = 15;
boolean isIncreasing = true;
unsigned long prevMillis = 0;
const unsigned long INTERVAL_FAN = 1000;

void basicDCMotor() {
    /*
        AIN1        AIN2
         H           L          -- "forward"
         L           H          -- "backward" (opposite)
         L           L          --  off
         H           H          -- BAD! (sadness :( ) avoid this

         PWM control speeds
    */

    // spin motor at full in one dir for 5 sec
    Serial.println("full speed forward");
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 255);
    delay(5000);

    // spin motors at half speed in oppo direction for 5 sec
    Serial.println("half speed forward");

    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 127);  // half speed
    delay(5000);

    // stop motor for 5 sec
    Serial.println("stop");

    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 0);
    delay(5000);
}

void potDCMotor() {
    // how can we use pot to control the motor?
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, motorSpeed);
    Serial.println(potVal);
}

void basicServo() {
    // servo step 3: servo.write()
    //  what is the servo range (angle)?
    //  0-180. but we use 15-165 for safety
    // rotate to 15 deg
    servoObj.write(15);
    delay(1000);
    servoObj.write(90);
    delay(1000);
    servoObj.write(165);
    delay(1000);
    servoObj.write(90);
    delay(1000);
}

void potServo() {
    int potVal = analogRead(PIN_POT);
    int angle = map(potVal, 0, 4095, 15, 165);
    servoObj.write(angle);
}

void simpleFan() {
    /*
        input: pot
        output: servo and dc motor

        goal:
        make servo rotate automatically
        make pot control DC motor speed

        how do we make servo rotate automatically?
        idea 1: for loop (would use delay)
        idea 2: use to map delay
        idea 3: millis
            servo stars at 15, increase by a fixed amount each time the timer
       goes off when servo gets to 165, start decreases now until 15, and flip
       and repeat

        then just pot to control motor speed
    */
    unsigned long curMillis = millis();
    int potVal = analogRead(PIN_POT);
    int speed = map(potVal, 0, 4095, 0, 255);

    // control DC motor
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    // analogWrite(PWMA, speed);   //this won't work because a photon 2 bug
    analogWrite(PWMA, speed, 50);
    /*
        DC motors and servos both use PWM, but at diff freq and they are not
       compatible SO! if we are combining DC motors and servo, we need to
       specify the PWM freq explicitly for the DC motor
    */

    if (curMillis - prevMillis > INTERVAL_FAN) {
        prevMillis = curMillis;

        // increase angle
        if (isIncreasing == true) {
            servoAngle = servoAngle + 15;
        } else {
            servoAngle = servoAngle - 15;
        }

        // stay in bounds
        if (servoAngle >= 165) {
            servoAngle = 165;
            isIncreasing = false;
        } else if (servoAngle <= 15) {
            servoAngle = 15;
            isIncreasing = true;
        }
        servoObj.write(servoAngle);
    }
}

void setup() {
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PIN_POT, INPUT);
    Serial.begin(9600);

    // servo step 2: attach pin
    servoObj.attach(PIN_SERVO);
}
void loop() {
    basicDCMotor();
    // potDCMotor();
    // basicServo();
    // potServo();
    // simpleFan();
}