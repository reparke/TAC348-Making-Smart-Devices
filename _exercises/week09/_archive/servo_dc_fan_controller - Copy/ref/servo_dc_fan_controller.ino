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
int pos = 15;  // variable to store the servo position
const unsigned long TURN_DELAY = 100;
bool posIncreasing = true;  // are we doing pos++ or pos--
unsigned long prevMillis = 0;

// motor pins
const int AIN1 = D3;
const int AIN2 = D4;
const int PWMA = D5;
const int PIN_POT = A0;
const int PIN_SERVO = D2;

// to work with servo, three steps
// step 1 create servo object
Servo servoObj;

void setup() {
    Serial.begin(9600);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PIN_POT, INPUT);
    // no need to configure servo pin mode
    // step 2: attach pin
    servoObj.attach(PIN_SERVO);
}
void loop() {
    // how would we get motor to go full speed forward for 3 sec, stop for 2
    // sec, then half speed the opposite direction for 5 sec?
    // //full speed for 3 sec
    // digitalWrite(AIN1, HIGH);
    // digitalWrite(AIN2, LOW);
    // analogWrite(PWMA, 255);
    // delay(3000);

    // // stop speed for 2 sec
    // digitalWrite(AIN1, LOW);
    // digitalWrite(AIN2, LOW);
    // analogWrite(PWMA, 0);
    // delay(2000);

    // // half  speed for 5 sec opposite direction
    // digitalWrite(AIN1, LOW);
    // digitalWrite(AIN2, HIGH);
    // analogWrite(PWMA, 127);
    // delay(5000);

    // use the potentiometer to control the motor speed
    int speed = map(analogRead(PIN_POT), 0, 4095, 0, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, speed);
    Serial.println(speed);
    // step 3: write your value
    // what is the range of servo?
    // full range is 0 deg to 180 deg; 15-165 is a safe range
    for (int i = 15; i < 165; i = i + 10) {
        servoObj.write(i);
        int speed = map(analogRead(PIN_POT), 0, 4095, 0, 255);
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        analogWrite(PWMA, speed);
        delay(500);
    }
    for (int i = 165; i > 15; i = i - 10) {
        servoObj.write(i);
        int speed = map(analogRead(PIN_POT), 0, 4095, 0, 255);
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        analogWrite(PWMA, speed);
        delay(500);
    }
    delay(1000);
    // potControlSpeed();
}
void potControlSpeed() {
    unsigned long curMillis = millis();
    // if the time between turning has happened, then update prevMillis and move
    if ((curMillis - TURN_DELAY) > prevMillis) {
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

        servoObj.write(pos);  // tell servo to go to position in variable 'pos'
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
// option1: the pot controls the fan speed while the servo continuosly THUMBS UP
// option2: the pot controls servo position while the fan speeds up and down on
// its own THUMBS DOWN