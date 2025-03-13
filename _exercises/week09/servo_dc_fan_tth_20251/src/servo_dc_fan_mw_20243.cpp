#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// motor pins
const int AIN1 = D3;  // motor pin - dir
const int AIN2 = D4;  // motor pin - dir
const int PWMA = A5;  // speed

// pot
const int PIN_POT = A1;
/*
    photon ---> motor driver ---> dc motor

*/

// servo step 1: declare pin and Servo object
const int PIN_SERVO = A2;
Servo servoObj;

// fan variables
const int INTERVAL_FAN = 1000;
unsigned long prevMillis = 0;

int servoAngle = 15;
boolean isIncreasing = true;

void basicDCMotor() {
    /*
    Direction
        AIN1        AIN2
         H           L      -- "forward"
         L           H      -- "opposite direction"
         L           L      -- stops
         H           H      -- BAD!

    PWM controls the speed
    */
    // spin the motor one direction at full speed for 5 seconds
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 255);  // pwm ranges from 0-255
    delay(5000);

    // reverse motor at half speed for 5 seconds
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 127);
    delay(5000);

    // stop motor for 5 sec
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 0);
    delay(5000);
}

void potDCMotor() {
    // use pot to control DC motor
    // how? read pot value and convert to PWM
    // pick a motor direction
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, motorSpeed);
}

void basicServo() {
    // servo step 3:  servo.write()
    servoObj.write(15);  // rotate to 15 deg
    delay(1000);
    servoObj.write(90);
    delay(1000);
    servoObj.write(165);
    delay(1000);
}

void potServo() {
    // use pot to control servo angle
    int potVal = analogRead(PIN_POT);
    int angle = map(potVal, 0, 4095, 15, 165);
    servoObj.write(angle);
}

void simpleFan() {
    /*
        input: pot
        output: servo and dc motor

        fan speed: low, medium
        base rotates back and forth

        goal:
        make servo rotate automatically
        make pot control Dc motor speed

        how do we make the servo rotate automatically?
        idea 1: for loop (would work but requires delay)

        idea 2: millis
            millis timer
            angle starts at 15, goes up by a little every time the timer goes
       off up to 165, then back to down to 15, and on and on
    */
    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    // DC speeds and Servo both use PWM but they update at different freq
    // so! when we want to servo and DC motors in the same, our analogWrite
    // for the DC motors need to have an extra parameter 50 at the end
    analogWrite(PWMA, motorSpeed, 50);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

    // servo rotation
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > INTERVAL_FAN) {
        prevMillis = curMillis;

        // increase the angle
        // idea is use prevAngle
        if (isIncreasing == true) {
            servoAngle += 15;

            // servoAngle = servoAngle + 15; //same as servoAngle += 15;

        } else {
            servoAngle -= 15;
        }

        // stay in bounds
        if (servoAngle >= 165) {
            isIncreasing = false;
        } else if (servoAngle <= 15) {
            isIncreasing = true;
        }

        servoObj.write(servoAngle);
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PIN_POT, INPUT);

    // servo step 2: attach the pin to the servo object
    servoObj.attach(PIN_SERVO);
}

void loop() {
    // basicDCMotor();
    // potDCMotor();
    // basicServo();
    // potServo();
    simpleFan();
}