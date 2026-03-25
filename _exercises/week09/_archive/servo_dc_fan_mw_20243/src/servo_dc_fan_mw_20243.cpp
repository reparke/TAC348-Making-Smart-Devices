#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// motor
const int AIN1 = D3;  // control motor dir
const int AIN2 = D4;  // control motor dir
const int PWMA = A5;  // control motor speed

// pot
const int PIN_POT = A1;

// servo
const int PIN_SERVO = A2;

// step 1: create servo obj
Servo fanServo;

// fan var
unsigned long prevMillis = 0;
int fanAngle = 90;            // 90 degrees
bool isFanIncreasing = true;  // is fan incr angle or decr angle

void basicDCMotor() {
    /*
      AIN1    AIN2
      H         L     "forward"
      L         H      "reverse"
      L         L       "stop"
      H         H       bad!

      PWM 0-255 speed
    */

    // motor spins in one dir for 5 sec
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 255);
    delay(5000);
    // motor spins in opposite dir for 5 sec at half speed
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 127);
    delay(5000);
    // motor stops for 5 sec
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 0);
    delay(5000);
}

// how would use pot to control fan speed?
void potDCMotor() {
    // pick a single direction
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, motorSpeed);
}

void basicServo() {
    // servo goes from 0-180 degrees, but we use 15-165 as a safe zone
    fanServo.write(15);
    delay(1000);
    fanServo.write(90);
    delay(1000);
    fanServo.write(165);
    delay(1000);
}

void potServo() {
    int potVal = analogRead(PIN_POT);

    int fanAngle = map(potVal, 0, 4095, 15, 165);
    fanServo.write(fanAngle);
}

void autoFan() {
    /*
      input: pot
      output: servo and dc motor

      have the pot control speed
      servo angle changes automatically

      move 15 degrees every few sec (milllis timer)

      millis timer
        - read the pot and map to fan speed
        - every 1 sec, check pot value and change angle

        - switch dir of servo rotating

    */
    // potDCMotor();
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, motorSpeed, 50);

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > 1000) {
        prevMillis = currMillis;

        if (isFanIncreasing == true) {
            fanAngle += 2;
        } else {
            fanAngle -= 2;
        }
        if (fanAngle > 100) {
            isFanIncreasing = false;
        } else if (fanAngle < 80) {
            isFanIncreasing = true;
        }
        fanServo.write(fanAngle);
    }
}

void setup() {
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PIN_POT, INPUT);
    Serial.begin(9600);
    // step 2: attach the pin
    fanServo.attach(PIN_SERVO);
}

void loop() {
    // basicDCMotor();
    // potDCMotor();
    // basicServo();
    // potServo();
    // autoFan();
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        analogWrite(PWMA, 120);
    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, motorSpeed, 50);

        fanServo.write(80);
        delay(1000);
        fanServo.write(90);
        delay(1000);
        fanServo.write(100);
        delay(1000);
        fanServo.write(90);
        delay(1000);
    }
