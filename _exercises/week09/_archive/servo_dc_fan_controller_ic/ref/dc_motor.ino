/*
 * Created by Ray Kim (USC)
 * modified by Rob Parke
 */
/*
| Motor Controller | Argon |
| ---------------- | ----- |
| PWMA             | D8    |
| AIN2             | D7    |
| AIN1             | D6    |
| VCC              | 3v3   |
| GND              | GND   |
| VM               | 3v3   |
| STBY             | 3v3   |
*/

const int AIN1 = D3;
const int AIN2 = D4;
const int PWMA = D5;
// const int STBY = D2;

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
pinMode(AIN1, OUTPUT);
pinMode(AIN2, OUTPUT);
pinMode(PWMA, OUTPUT);
// pinMode(STBY, INPUT_PULLUP);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

//set the direction one HIGH, one LOW
digitalWrite(AIN1, HIGH);
digitalWrite(AIN2, LOW);
analogWrite(PWMA, 255); //full speed one way
delay(1000); //run for 1 second

analogWrite(PWMA,0); // stop
delay(1000);

//change direction
digitalWrite(AIN1, LOW);
digitalWrite(AIN2, HIGH);
analogWrite(PWMA, 255); //full speed opposite way
delay(1000);

analogWrite(PWMA,0); //stop
delay(1000);

}