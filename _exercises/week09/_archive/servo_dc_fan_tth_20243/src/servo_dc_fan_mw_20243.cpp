#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// motor pins
const int AIN1 = D3;  // control motor dir
const int AIN2 = D4;  // control Motor dir
const int PWMA = A5;  // control motor speed

// pot
const int PIN_POT = A1;

// Servo
const int PIN_SERVO = A2;

// step1
Servo fanServo;
int servoAngle = 90;
unsigned long prevMillis = 0;
bool isAngleIncreasing = true;

void basicDCMotor() {
    /* Direction
        AIN1    AIN2
        H       L       "forward"
        L       H       "reverse"
        L       L       stop
        H       H       BAD!
    PWMA is for speed 0-255
    */
    // spin motor at full speed in one direction for 5 seconds
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 255);
    delay(5000);

    // reverse at half speed for 5 sec
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

void potDCMotor() {
    // how we use pot to control the DC motor?
    // pick a direction
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, motorSpeed);
}

void basicServo() {
    fanServo.write(15);  // write to a particular angle
    delay(1000);
    fanServo.write(90);
    delay(1000);
    fanServo.write(165);
    delay(1000);
}

void potServo() {
    int potVal = analogRead(PIN_POT);

    int angle = map(potVal, 0, 4095, 15, 165);
    fanServo.write(angle);
}

void simpleFan() {
    /*
        input: pot
        output: servo and dc motor

        fan speed low, med, high
        rotate base or be stationary

        make servo rotate automatically
        make pot control DC motor speed

        how do we make the servo rotate automatically?
            millis timer
            angle starts at 15, goes up by a little up to 165, then down to 15,
       etc. global var for angle
    */
    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, motorSpeed, 50);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > 1000) {
        prevMillis = currMillis;
        if (isAngleIncreasing == true) {
            servoAngle += 5;
        } else {
            servoAngle -= 5;
        }
        if (servoAngle >= 165) {
            isAngleIncreasing = false;
        } else if (servoAngle <= 15) {
            isAngleIncreasing = true;
        }
        fanServo.write(servoAngle);
    }
}

void setup() {
    pinMode(AIN1, OUTPUT);  // sending a signal FROM PHOTON to MOTOR DRIVEr
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PIN_POT, INPUT);
    Serial.begin(9600);
    // step 2
    fanServo.attach(PIN_SERVO);
}

void loop() {
    // basicDCMotor();
    // potDCMotor();
    // basicServo();
    // potServo();
    // simpleFan();
}