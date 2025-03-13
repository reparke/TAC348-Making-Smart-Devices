#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// wiring for DC motor
const int AIN1 = D3;  // motor dir
const int AIN2 = D4;  // motor dir
const int PWMA = A5;  // motor speed

// pot
const int PIN_POT = A1;

// servo step 1 - create servo object
const int PIN_SERVO = A2;
Servo fanServo;

unsigned long prevMillis = 0;
const unsigned long INTERVAL_ROTATE = 1000;
int servoAngle = 90;  // track rotation
bool isAngleIncreasing = true;

void basicDcMotor() {
    /*
    Direction
        AIN1        AIN2
         H            L      "forward"
         L            H      "reverse"
         L            L          stop
         H            H        BAD!

         PWMA   0-255 is speed
    */
    // spin motor at full speed in one dir for 5 sec
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 255);
    delay(5000);

    // reverse motor at half speed for 5 sec
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 127);
    delay(5000);

    // stop for 5 sec
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 0);
    delay(5000);
}

void potDcMotor() {
    // pot controls motor speed
    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, motorSpeed);

    // pick a direction
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
}

void basicServo() {
    // servo control step 3
    fanServo.write(15);  // rotate to 15 deg
    delay(1000);
    fanServo.write(90);
    delay(1000);
    fanServo.write(165);
    delay(1000);

    // notice the servo angle is 0-180, but we use 15-165 to prevent damage
}

void potServo() {
    // pot control servo direction
    int potVal = analogRead(PIN_POT);
    int angle = map(potVal, 0, 4095, 15, 165);
    fanServo.write(angle);
}

void simpleFan() {
    /*
        input: pot
        output: servo and DC motor

        fan speed: low med high
        rotates back and forth on its own

        goal:
            make servo rotate back / forth automatically
            make pot control dc motor (fan) speed

        how do we implement this?
        how to make servo rotate automatically?
            use millis instead of delay so device is responsive all the time
            track prevMillis
            conditional / if statement for time length
                increase the angle
                BUT we will need to REVERSE direction at some point
            need global var for angle

        one important hint!
            both servo and DC motor use PWM
            BUT they update at a different frequency
            SO...if we want to use a DC motor and SERVO in same device
                then when we change the DC Motor speed with analogWrite
                we have to say analogWrite(PWMA, speed, 50)   <--- 50 has to be
       here
    */

    // dc motor
    int potVal = analogRead(PIN_POT);
    int motorspeed = map(potVal, 0, 4095, 0, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, motorspeed,
                50);  // 50 is needed because will ALSO use the servo
                      // without, the DC motor stops working

    unsigned long curMillis = millis();
    if (curMillis - prevMillis > INTERVAL_ROTATE) {
        prevMillis = curMillis;

        // changing angle
        if (isAngleIncreasing == true) {
            servoAngle += 5;
        } else {
            servoAngle -= 5;
        }

        // reset direction
        if (servoAngle >= 165) {
            isAngleIncreasing = false;
        } else if (servoAngle <= 15) {
            isAngleIncreasing = true;
        }

        // write the angle
        fanServo.write(servoAngle);
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PIN_POT, INPUT);

    // servo connect step 2
    fanServo.attach(PIN_SERVO);
}

void loop() {
    // basicDcMotor();
    // potDcMotor();
    // basicServo();
    // potServo();
    simpleFan();
}