/*NOTE: This sensor is different in behavior from documentation
  Time the signal is active (low) is about 3 sec, not 15 sec in documentation

  Also there are no jumpers regarding retrigger or potentiometers for
  sensitivity

  Pay careful attention that WHITE is GROUND, and BLACK is ALARM
*/

/******************************************************************************
PIR_Motion_Detector_Example.ino
Example sketch for SparkFun's PIR Motion Detector
  (https://www.sparkfun.com/products/13285)
Jim Lindblom @ SparkFun Electronics
May 2, 2016

The PIR motion sensor has a three-pin JST connector terminating it. Connect
the wire colors like this:
- Black: D2 - signal output (pulled up with 10K)
- White: GND
- Red: 5V

Connect an LED to pin D2

Whenever the PIR sensor detects movement, it'll write the alarm pin LOW.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/

// 10k pull up resistor
const int MOTION_PIN = D4;  // Pin connected to motion detector
const int LED_PIN = D7;     // LED pin - active-high

void setup() {
    Serial.begin(9600);
    // The PIR sensor's output signal is an open-collector,
    // so a pull-up resistor is required:
    pinMode(MOTION_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("PIR Sensor is stabilizing. Please wait...");
    delay(3000);  // Wait 30 seconds for the sensor to stabilize
    Serial.println("Sensor ready.");
}
int count = 0;
void loop() {
    int proximity = digitalRead(MOTION_PIN);
    // Serial.println("Motion pin: " + String(proximity));
    if (proximity ==
        LOW)  // If the sensor's output goes low, motion is detected
    {
        digitalWrite(LED_PIN, HIGH);
        Serial.println(String(count++) + " Motion detected!");
    } else {
        digitalWrite(LED_PIN, LOW);
        // Serial.println(String(count++) + " Motion stopped!");
    }
    // delay(1000);
}
