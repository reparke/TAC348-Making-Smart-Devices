
/*
| Motor Controller | Argon |
| ---------------- | ----- |
| PWMA             | D5    |
| AIN2             | D4    |
| AIN1             | D3    |
| VCC              | 3v3   |
| GND              | GND   |
| VM               | 3v3   |
| STBY             | 3v3   |

Servo: D2
Pot: A0
*/

// use the potentiometer as a speed controller

// to control motor, we need three pins
const int AIN1 = D3;
const int AIN2 = D4;  // these two control direction of motor
const int PWMA = D5;  // this controls speed
const int PIN_POT = A0;
const int PIN_SERVO = D2;

unsigned long prevMillis = 0;
unsigned long INCREMENT_TIMER = 20;
int servoPosition = 15;          // servo angle
bool isServoPosIncreasing = true;  // direction

//create the servo object
Servo servo;

void setup() {
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PIN_POT, INPUT);
    pinMode(PIN_SERVO, OUTPUT);

    //connect servo to a pin
    servo.attach(PIN_SERVO);

    Serial.begin(9600);
}

void loop() {
    // //spin in one direction at full speed
    // digitalWrite(AIN1, HIGH);
    // digitalWrite(AIN2, LOW);
    // analogWrite(PWMA, 255);
    // delay(1000);
    // analogWrite(PWMA, 127);
    // delay(1000);

    // //stop motor
    // digitalWrite(AIN1, LOW);
    // digitalWrite(AIN2, LOW);
    // analogWrite(PWMA, 0);
    // delay(1000);

    // //spin in opposite direction
    // digitalWrite(AIN1, LOW);
    // digitalWrite(AIN2, HIGH);
    // analogWrite(PWMA, 255);
    // delay(1000);

    // // stop motor
    // digitalWrite(AIN1, LOW);
    // digitalWrite(AIN2, LOW);
    // analogWrite(PWMA, 0);
    // delay(1000);

    // digitalWrite(AIN1, LOW);
    // digitalWrite(AIN2, HIGH);

    // int potVal = analogRead(PIN_POT);
    // int speed = map(potVal, 0, 4095, 0, 255);
    // analogWrite(PWMA, speed);

    // servo.write(15);  //rotate 15 deg
    // delay(500);
    // servo.write(90);
    // delay(500);
    // servo.write(165);
    // delay(500);

    // int potVal = analogRead(PIN_POT);
    // int rotation = map(potVal, 0, 4095, 15, 165);
    // servo.write(rotation);

    /*
    1) pot controls DC motor speed
    2) servo rotates automatically 15-165 degrees, stop, then 165-15, etc

        what to track?
            logic: is at 15 or 165?
            variable: int current rotation, bool the rotation inreasing or decreasing
        millis: every so often you change rotation
    */

        unsigned long curMillis = millis();

        if (curMillis - prevMillis > INCREMENT_TIMER) {
            prevMillis = curMillis;
            // what direction are we going--> increment or decrement
            // check that we dont go above 165 or below 15
            if (isServoPosIncreasing == true) {
                servoPosition++;  // C++ notation to add 1  servoPos = servoPos+1
                servo.write(servoPosition);
                if (servoPosition >= 165) {
                    servoPosition = false;
                }
            } else {
                servoPosition--;  // C++ notation to subrat 1
                servo.write(servoPosition);
                if (servoPosition <= 15) {
                    servoPosition = true;
                }
            }
        }
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);

        int potVal = analogRead(PIN_POT);
        int speed = map(potVal, 0, 4095, 0, 255);
        analogWrite(PWMA, speed);  // full speed opposite
}