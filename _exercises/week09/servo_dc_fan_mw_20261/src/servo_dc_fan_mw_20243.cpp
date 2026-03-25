
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// motor pins
const int AIN1 = D3;  // motor dir
const int AIN2 = D4;  // motor dir
const int PWMA = A5;  // motor speed

// pot
const int PIN_POT = A1;

// photon <--> motor driver <--> motor

// servo step 1: create servo Obj
Servo fanServo;
const int PIN_SERVO = A2;

// fan
unsigned long prevMillis = 0;
const unsigned long INTERVAL = 1000;
boolean isIncreasing = true;
int servoAngle = 15;

void basicDcMotor() {
    /*
        AIN1        AIN2
        H           L           -- spinning
        L           H           -- spinning opposite dir
        L           L           -- stop
        H           H           -- BAD! (Jad: "Death")
        PWMA controls speed
    */

    // spin motor at at full speed one direction
    // to use motor, we need 3 pins / signals
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 255);
    delay(5000);

    // spin motor oppositve dir at half speed
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 127);
    delay(5000);

    // stop motor
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 0);
    delay(5000);
}
void potDcMotor() {
    // how can we use the pot to control motor?

    // pick a dir
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, motorSpeed);
}
void basicServo() {
    // servo step 3: write
    // 15-165 is our SAFE range of angles

    fanServo.write(15);
    delay(1000);
    fanServo.write(90);
    delay(1000);
    fanServo.write(165);
    delay(1000);
    fanServo.write(90);
    delay(1000);
}

void simpleFan() {
    /*
        input: pot
        output: servo, dc motor

        goal:
            make servo rotate automatically back and forth
            make pot control the dc motor speed

        how do we make the servo rotate automatically?
            servo range is 15-165
        idea 1: use millis (a little harder design,  but not blocking)
        idea 2: for loop (easier to think about, but requires delay() )

        miilis approach
            servo starts at 15, increasing by a fixed amount at each timer
       interval when it hits 165, then servo decrease until 15, and so on

        pot just controls motor speed

        for the next 3-4 min, try to design this approach

    */
    unsigned long currMillis = millis();
    int potVal = analogRead(PIN_POT);
    int motorSpeed = map(potVal, 0, 4095, 0, 255);

    // control dc motor speed
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    // analogWrite(PWMA, motorSpeed); // photon 2 bug with DC + servo
    analogWrite(PWMA, motorSpeed, 50); //adding 50 specifies the PWM freq
    /* for photon 2
        both DC motors and servos use PWM but at diff FREQUENCIES
        BUT those freq are not compatible with each other

        SO! if we use DC motor and servo TOGETHER, then we need to 
        specify the PWM frequency EXPLICITLY when we update DC motor
    */

    // consider automatic servo rotatio
    //  if we are increasing, then at each timer interval, increase servo angle
    // if we we decreasing, then at each timer, decrease angle
    //  if we go above 165, then start decreasing
    //  if we go below 15, then start increasing

    if (currMillis - prevMillis > INTERVAL) {
        prevMillis = currMillis;

        Serial.println(servoAngle);

        // adjust angle
        if (isIncreasing == true) {
            servoAngle = servoAngle + 10;
        } else {
            servoAngle = servoAngle - 10;
        }
        // make sure we stay in bounds
        if (servoAngle > 165) {
            servoAngle = 165;
            isIncreasing = false;
        } else if (servoAngle < 15) {
            servoAngle = 15;
            isIncreasing = true;
        }
        fanServo.write(servoAngle);
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(PIN_POT, INPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);

    // servo step 2:
    fanServo.attach(PIN_SERVO);  // no need to use pinMode with servo

    // servo step 3: write to the servo in loop()
}
void loop() {
    // basicDcMotor();
    // potDcMotor();
    // basicServo();
    // potServo(); //skipped
    simpleFan();
}
