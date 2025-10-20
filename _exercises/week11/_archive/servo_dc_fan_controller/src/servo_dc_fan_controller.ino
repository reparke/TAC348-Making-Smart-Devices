/*
 * Created by Ray Kim (USC)
 * modified by Rob Parke
 */
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

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int PIN_SERVO = D2;
int pos = 15;  // variable to store the servo position
const unsigned long TURN_DELAY = 100;
bool posIncreasing = true;  // are we doing pos++ or pos--

const int PIN_POT = A0;
unsigned long prevMillis = 0;
unsigned long prevMillisServo = 0;
unsigned long intervalServo = 20;

const int AIN1 = D3;
const int AIN2 = D4;
const int PWMA = D5;

void setup() {
    // Put initialization like pinMode and begin functions here.
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);

    pinMode(PIN_SERVO, OUTPUT);
    myservo.attach(
        PIN_SERVO);  // attaches the servo on pin 9 to the servo object

    pinMode(PIN_POT, INPUT);
}

void loop() {
    // initialExamples(); //first introduction to DC and servo motots
    
    // potControlDcMotor(); //no servo,

    // potControlRotate();  // pot controls servo rotation, constant DC speeed

    // potControlSpeed();    // constant servo rotation, pot controls DC speed


}

void initialExamples() {
    // set the direction one HIGH, one LOW
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 255);  // full speed one way
    delay(1000);             // run for 1 second

    analogWrite(PWMA, 0);  // stop
    delay(1000);

    // change direction
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 255);  // full speed opposite way
    delay(1000);

    analogWrite(PWMA, 0);  // stop
    delay(1000);
}
void potControlDcMotor() {  // use pot to change fan speed
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);

    int potVal = analogRead(PIN_POT);
    int speed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, speed);  // full speed opposite way
}
void potControlRotate() {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 255);  // full speed opposite way

    int potVal = analogRead(PIN_POT);
    pos = map(potVal, 0, 4095, 15, 165);
    myservo.write(pos);  // tell servo to go to position in variable 'pos'

    Serial.println("potval: " + String(potVal) + ", pos: " + String(pos));
}


void potControlSpeed() {
    unsigned long curMillis = millis();
    // if the time between turning has happened, then update prevMillis and move
    if ((curMillis - prevMillis) > TURN_DELAY) {
        prevMillis = curMillis;
        if (posIncreasing == true) {
            pos++;
            if (pos >= 165) {
                posIncreasing = false;
            }
        } else {  // decreasing
            pos--;
            if (pos <= 15) {
                posIncreasing = true;
            }
        }

        myservo.write(pos);  // tell servo to go to position in variable 'pos'
        int potVal = analogRead(PIN_POT);
        int pwmVal = map(potVal, 0, 4095, 0, 255);
        analogWrite(PWMA, pwmVal);
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);

        Serial.println("pos: " + String(pos) +
                       ", posIncreasing: " + String(posIncreasing) +
                       "pot: " + String(potVal) + ", pwm: " + String(pwmVal));
    }
}



/* Skip this version in favor of millis version */
/*
void constantRotateLoop() {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 255);  // full speed opposite way
    for (pos = 15; pos <= 165;
         pos += 1) {  // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(15);           // waits 15ms for the servo to reach the position
    }
    for (pos = 165; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
        myservo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(15);           // waits 15ms for the servo to reach the position
    }
}
*/