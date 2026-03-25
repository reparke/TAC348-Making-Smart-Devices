
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// motor pin
const int AIN1 = D3;  // motor dir
const int AIN2 = D4;  // motor dir
const int PWMA = A5;  // speed

// pot
const int PIN_POT = A1;

// photon --> motor driver --> motor

// servo part 1
Servo fanServo;  // declare the Servo obj
const int PIN_SERVO = A2;

// fan variables
unsigned long prevMillis = 0;
const unsigned long INTERVAL = 1000;
// what other two var?
int servoAngle = 15;
const int MAX_ANGLE = 165;
const int MIN_ANGLE = 15;
bool isIncreasing = true;

void basicDCMotor() {
    /*
        PWMA will control the speed (0-255)

        AIN1    AIN2       What does motor do?
        L       H       -- spin!
        H       L       -- spin the other way
        L       L       -- no spin
        H       H       -- BAD!
    */

    // spin motor at full speed
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 255);
    delay(5000);

    // reverse at half speed
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 127);
    delay(5000);

    // motor off
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 0);
    delay(5000);
}

void potDCMotor() {
    // how can we use pot to control the DC motor?
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, motorSpeed);
}

void basicServo() {
    // servo step 3: fanServo.write(..)
    //  servo angle range: 0-180
    //           safe range: 15-165
    fanServo.write(15);
    delay(1000);
    fanServo.write(90);
    delay(1000);
    fanServo.write(165);
    delay(1000);
    fanServo.write(90);
    delay(90);
}

void potServo() {
    // skip
    // map pot to 15-165 and writing
}

void simpleFan() {
    /*
        input: pot
        output: servo, dc motor

        goal:
        -make servo rotate automatically back and forth
        -make pot control fan blade speed

        solution:
        -use pot to control motor speed

        how do we make the servo rotate automatically?
        idea 1: increase / decrease servo position each loops cycle
        idea 2: millis timer to increase / decreaese
        idea 3: for loop <-- problem is that we would to use delay() -- AVOID

        servo starts at 15, increase by fixed amount each time timer goes off
        when servo get to 165, start to decrease until 15, then repeat
    */
    // control fan blade
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    // analogWrite(PWMA, motorSpeed);  // we will come back
    analogWrite(PWMA, motorSpeed, 50);  

    /*
    DC motors and servos both use PWM at DIFFERENT FREQUENCIES
        --> these diff freq are NOT COMPATIBLE
    if in the same project we use both servo and DC motor
        --> we need to specify the PWM frequency for the DC motor

        analogWrite(PIN, PWM_VALUE, 50); <----
    */

    
    unsigned long currMillis = millis();

    if (currMillis - prevMillis > INTERVAL) {
        prevMillis = currMillis;

        // if increasing, increase angle to 165
        // if decreasing, decrease angle to 15
        // if > 165, switch direction to decr
        // if < 15, switch direct to incr
        if (isIncreasing == true) {
            servoAngle = servoAngle + 10;

        } else {  // decrease
            servoAngle = servoAngle - 10;
        }

        if (servoAngle > MAX_ANGLE) {
            servoAngle = MAX_ANGLE;
            isIncreasing = false;
        } else if (servoAngle < MIN_ANGLE) {
            servoAngle = MIN_ANGLE;
            isIncreasing = true;
        }
        fanServo.write(servoAngle);
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(PIN_POT, INPUT);
    pinMode(AIN1, OUTPUT);  // output or input?
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    // servo part 2
    fanServo.attach(PIN_SERVO);  // no pinMode
}
void loop() {
    // basicDCMotor();
    // potDCMotor();
    // basicServo();
    simpleFan();
}
