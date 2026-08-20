/*
 * Created by Ray Kim (USC)
 * modified by Rob Parke
 */
/*
| Motor Controller | Argon |
| ---------------- | ----- |
| PWMA             | D5    |
| AIN2             | D3    |
| AIN1             | D4    |
| VCC              | 3v3   |
| GND              | GND   |
| VM               | 3v3   |
| STBY             | 3v3   |
*/

const int AIN1 = D4;
const int AIN2 = D3;
const int PWMA = D5;
const int PIN_POT = A0;
const int PIN_SERVO = D2;

int pos = 0;  // servo position (0-180)

// servo obj
Servo servoObj;

// Particle.subscribe("TAC348-ENVIRO", enviroHandler, ALL_DEVICES);
void enviroHandler(const char *event, const char *data) {
    double eventData = atof(data);  // atof converts string into double
    String eventName = String(event);
    Serial.println("event name: " + String(eventName));
    // if (eventName.equals("TAC348-ENVIRO")) {     //if the eventName starts
    // with TAC 348
    //     temperatures[currentIndex] = eventData;  //fill data in the
    //     currentIndex currentIndex = currentIndex + 1;         //increase
    //     current index by 1 counter = counter + 1; //increase the counter (use
    //     for average) if (currentIndex == 20) {                //if current
    //     index is equal to 20
    //         currentIndex = 0;                    //restarts the array,
    //         rewrites starting from beginning
    //     }
    //     if (counter == 20) {         //if the counter is equal to 20
    //         counter == counter + 0;  //increase counter by 0, stays at 20
    //         because there will always be 20 values
    //     }
    // }
}

void setup() {
    pinMode(AIN1, OUTPUT);  // input to motor
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PIN_SERVO, OUTPUT);
    pinMode(PIN_POT, INPUT);

    // init servo
    servoObj.attach(PIN_SERVO);
    Particle.subscribe("TAC348-ENVIRO", enviroHandler, ALL_DEVICES);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    // //control servo
    // for (pos = 15; pos < 165; pos++) { //since servo are delicate we use 15
    // and 165
    //   servoObj.write(pos);
    //   delay(50);
    // }

    // fan blows constantly, pot controls servo position -- do now
    // servo rotates constantly, pot control fan speed

    // control dc motor
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    // control speed
    analogWrite(PWMA, 255);  // full speed

    // use map to MAP 0-4095 from pot to 15-165 for servo
    int potVal = analogRead(PIN_POT);

    pos = map(potVal, 0, 4095, 15, 165);
    servoObj.write(pos);
}