const int AIN1 = D3;
const int AIN2 = D4;
const int PWMA = D5;
const int POT = A0;

// servo
const int SERVO = D2;
Servo servo;  // no libraries to include

unsigned long prevMillis = 0;
unsigned long INCREMENT_TIMER = 20;
int position = 15;       // servo angle
bool posIncreasing = true;  // direction

void setup() {
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(POT, INPUT);

    pinMode(SERVO, OUTPUT);
    servo.attach(SERVO);
}
void loop() {
    // initialExample();
    // potControlDcMotor();
    // potControlServo();
    fullFan();
}

// have the servo rotate 15 deg to 165 deg, and then back the other direction
// the pot will control fan speed
//  DON'T USE DELAY OR FOR LOOP -- use millis
//  Idea: global var to track angle
//        var to track direction (boolean, State enum);
//        miilis()

void fullFan() {
    unsigned long curMillis = millis();

    if (curMillis - prevMillis > INCREMENT_TIMER) {
        prevMillis = curMillis;
        // what direction are we going--> increment or decrement
        // check that we dont go above 165 or below 15
        if (posIncreasing == true) {
            position++;  // C++ notation to add 1
            servo.write(position);
            if (position >= 165) {
                posIncreasing = false;
            }
        } else {
            position--;  // C++ notation to subrat 1
            servo.write(position);
            if (position <= 15) {
                posIncreasing = true;
            }
        }
    }
    potControlDcMotor();
}

void potControlServo() {
    // servo.write(15);
    // delay(500);
    // servo.write(95);
    // delay(500);
    // servo.write(150);
    // delay(500);

    int potVal = analogRead(POT);
    int rotation = map(potVal, 0, 4095, 15, 165);
    servo.write(rotation);
}

void potControlDcMotor() {  // use pot to change fan speed
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);

    int potVal = analogRead(POT);
    int speed = map(potVal, 0, 4095, 0, 255);
    analogWrite(PWMA, speed);  // full speed opposite way
}

// basics of how to a motor
void initialExample() {
    // spin at full speed in one direction
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 255);
    delay(1000);

    // stop
    analogWrite(PWMA, 0);
    delay(1000);

    // spin in other direction
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 255);
    delay(1000);

    // stop
    analogWrite(PWMA, 0);
    delay(1000);
}