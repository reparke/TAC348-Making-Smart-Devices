#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// motors pin
const int AIN1 = D3;  // motor dir
const int AIN2 = D4;  // motor dir
const int PWMA = A5;  // speed

// pot
const int PIN_POT = A1;  // correction from pre-class wiriing

// photon   -->   motor driver ---> motor

/*
3 steps to using a servo
1) create servo obj
2) attach pin
3) write the angle
*/
const int PIN_SERVO = A2;
Servo servo;  // step 1

int servoAngle = 15;
unsigned long prevMillis = 0;
const unsigned long INTERVAL = 1000;  // timer interval
bool isIncreasing = true;

void simpleFan() {
    // green -- we build the fan together
    // red   -- you take 10 min to build individual

    /*
        input: pot
        output: servo and dc motor

        goals:
        - make servo rotate automatically back and forth
        - make pot control motor speed

        how do we make the servo rotate automatically?
        idea: loop the servo angle
        idea: for loop (problem--we have to delay :( )
        idea: use milis timer

        //use pot to control speed

        last note:
            DC motors and servos both use PWM 
                BUT AT DIFFERENT FREQUENCIES
            
            if you're only using DC motors, this code works fine
            if you're only using servo, this code is fine

            if you are using BOTH servos and DC motors, 
                we need to specify the frequency for the Dc

            instead of
                analogWrite (PIN, VALUE)
            we say
                analogWrite (PIN, VALUE, 50)

    */
    potDCMotor();

    // increase servo angle a little each time we run this
    // switch direction at some point
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL) {
        prevMillis = currMillis;

        if (isIncreasing == true) {
            servoAngle = servoAngle + 10;
        } else {  /// we should be decr
            servoAngle = servoAngle - 10;
        }

        if (servoAngle > 165) {
            isIncreasing = false;
            servoAngle = 165;
        } else if (servoAngle < 15) {
            isIncreasing = true;
            servoAngle = 15;
        }
        servo.write(servoAngle);
    }
}

void potServo() {
    // skip
    // map pot to 15-165 and writing

  
    int potVal = analogRead(PIN_POT);
    int angle = map(potVal, 0, 4095, 15, 165);

    servo.write(angle);
}
void basicServo() {
    // servo.write(ANGLE)       //step 3
    // what is the angle range of our servos?
    // actual: 0-180
    // usable: 15-165
    servo.write(15);  // 15 deg
    delay(1000);
    servo.write(90);
    delay(1000);
    servo.write(165);
    delay(1000);
    servo.write(90);
    delay(100
}

void basicDCMotor() {
    /*
        PWMA will control the speed (0-255)

        AIN1        AIN2      Result
        L           H           spin in a direction
        H           L           spin in opposite dir
        L           L           STOP / off
        H           H           BAD!  could damage
    */
    // spin motor at half speed for 5 s
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 127);
    delay(5000);

    // spin motor in reverse at full speed
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 255);
    delay(5000);

    // stop motor
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 0);
    delay(5000);
}

void potDCMotor() {
    // use pot to control DC motor speed
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);  // pick an arbitrary dir

    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);

    // analogWrite(PWMA, motorSpeed);
    analogWrite(PWMA, motorSpeed, 50);
}
void setup() {
    Serial.begin(9600);
    pinMode(AIN1, OUTPUT);  // input or output?
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PIN_POT, INPUT);

    servo.attach(PIN_SERVO);  // step 2 - no pinMode
}
void loop() {
    //  basicDCMotor();
    // potDCMotor();
    // basicServo();
    simpleFan();
}