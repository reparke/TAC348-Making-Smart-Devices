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

const int PIN_SERVO = D2;
const int PIN_POT = A0;

unsigned long prevMillis = 0;

const int AIN1 = D3;
const int AIN2 = D4;
const int PWMA = D5;

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(PIN_SERVO, OUTPUT);
  pinMode(PIN_POT, INPUT);
  Serial.begin(9600);
}

void loop() {
}