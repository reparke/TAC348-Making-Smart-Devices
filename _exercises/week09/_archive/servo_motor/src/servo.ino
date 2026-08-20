/* based on http://www.arduino.cc/en/Tutorial/Tone
 */

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int PIN_SERVO = A3;

int pos = 0;  // variable to store the servo position

void setup() {
  pinMode(PIN_SERVO, OUTPUT);

  myservo.attach(PIN_SERVO);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 15; pos <= 165; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(15);           // waits 15ms for the servo to reach the position
    Serial.println("pos: "+ String(pos));
  }
  for (pos = 165; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(15);           // waits 15ms for the servo to reach the position
    Serial.println("pos: " + String(pos));
  }
}
