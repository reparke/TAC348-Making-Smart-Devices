#include "Particle.h"

// DC motor
const int AIN1 = D3;  // motor direction
const int AIN2 = D4;  // motor dir
const int PWMA = A5;  // speed

// pot
const int PIN_POT = A1;  // IMPORTANT

/* connecting servo
    create servo obj
    attach pin
    write
*/
const int PIN_SERVO = A2;
Servo servo;  // servo obj

unsigned long prevMillis = 0;
const unsigned long INTERVAL = 1000;
int servoAngle = 15;
bool isIncreasing = true;

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

void basicDCMotor() {
    // what controls the motor?
    /*
        PWMA for speed

        AIN1        AIN2        What does motor do?
        H           L               goes one dir
        L           H               goes other dir
        L           L               stops
        H           H               BAD! could damage
    */
    // spin motor at full speed
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 255);
    delay(5000);

    // reverse motor at half speed for 5s
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

// make the potentiometer control the motor speed
void potDCMotor() {
    // pick dir
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

    // use pot to control speed
    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, motorSpeed);
    Serial.println("pot: " + String(potVal) + "; PWM: " + String(motorSpeed));
}

void basicServo() {
    // servo step 3: write(angle)
    //  servo range: 0-180
    //  safe range: 15-165

    servo.write(15);
    delay(1000);
    servo.write(90);
    delay(1000);
    servo.write(165);
    delay(1000);
    servo.write(90);
    delay(1000);
}

void simpleFan() {
/*
    green: work independently in break out room
    red: design together in class

    input: pot
    output: dc motor, servo 

    fan to rotate automatically and be able to control speed

    solution:
        use pot to control
        use millis to control servo automatically
            we do not want to use delay or for loop

    how do we use millis to control servo position?

    start at 15, increment by XX each time in millis block
        eg. 15 30 45 60 75 ...


DC motors and servo both use PWM
    BUT at DIFFERENT FREQUENCIES

if we need to control DC and servos IN THE SAME PROJECT
    --> we need to specify the PWM frequency for the DC Motor
    for DC motor
    analogWrite(PIN, VALUE, 50);  <--- 50 is the correct freq

*/
    //control fan speed
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    int potVal = analogRead(PIN_POT);
    int motorspeed = map(potVal, 0, 4094, 0, 255);
    // analogWrite(PWMA, motorspeed);
    analogWrite(PWMA, motorspeed, 50);
    Serial.println("pot: " + String(potVal) + "; PWM: " + String(motorspeed));

    //let rotate the servos 
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL){
        prevMillis = currMillis;

        if (isIncreasing == true) {
            servoAngle = servoAngle + 20;
        }
        else {
            servoAngle = servoAngle - 20;
        }

        if (servoAngle > 165) {
            servoAngle = 165;
            isIncreasing = false;
        }
        else if (servoAngle < 15) {
            servoAngle = 15;
            isIncreasing = true;
        }
        servo.write(servoAngle);
    }

}

void setup() {
    Serial.begin(9600);
    pinMode(PIN_POT, INPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    // to use servo, instead of PINMODE, we ATTACH the PIN
    servo.attach(PIN_SERVO);
}
void loop() {
    basicDCMotor();
    // potDCMotor();
    // basicServo();
    // simpleFan(); 
}