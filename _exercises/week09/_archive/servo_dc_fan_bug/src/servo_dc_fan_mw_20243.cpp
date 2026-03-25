#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int AIN1 = D3;  // control motor dir
const int AIN2 = D4;  // control Motor dir
const int PWMA = A5;  // control motor speed
const int PIN_POT = A1;
const int PIN_SERVO = A2;

Servo fanServo;
int servoAngle = 90;
unsigned long prevMillis = 0;
bool isAngleIncreasing = true;

void setup() {
    pinMode(AIN1, OUTPUT);  
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PIN_POT, INPUT);
    Serial.begin(9600);
    fanServo.attach(PIN_SERVO);
}


void loop() {
    // analogWrite(PWMA, 255);
    // digitalWrite(AIN1, HIGH);
    // digitalWrite(AIN2, LOW);

    // if (isAngleIncreasing == true) {
    //     servoAngle += 5;
    // } else {
    //     servoAngle -= 5;
    // }
    // if (servoAngle >= 165) {
    //     isAngleIncreasing = false;
    // } else if (servoAngle <= 15) {
    //     isAngleIncreasing = true;
    // }
    // fanServo.write(servoAngle);
    // delay(200);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, motorSpeed, 50);

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