// const int PIN_POT = A0;
// const int PIN_LED = D2;
const int PIN_BUTTON = D2;

int counter = 0;

// step 1:
//serial.begin
void setup() {
  Serial.begin(9600);
  // pinMode(PIN_LED, OUTPUT); //LED
  pinMode(PIN_BUTTON, INPUT);
  // pinMode(PIN_POT, INPUT);  //potentiometer is an analog input device

}

void loop() {
  int buttonVal = digitalRead(PIN_BUTTON);
  Serial.println("The button value is " + String(buttonVal));
  delay(100);

  

  // counter = counter + 1;

  // //Step 2 for serial is to print
  // // Serial.println("The current count is " + String(counter));

  // // delay(100);

  // int potValue = analogRead(PIN_POT);   //range? 


  // // input range is 0-4095 (what we measure with ADC for the pot)
  // // output range is 0-255 (what we need to send to the LED for PWM)

  // int pwmValue = float(potValue) / 4095 * 255;

  // Serial.println("The pot value is " + String(potValue) + " and the pwm value is " + String(pwmValue));
  // analogWrite(PIN_LED, pwmValue);

  // delay(100);

  //use the potentiometer to control the LED brightness

  /*
    in C++, division / does NOT always give you a float
      10 / 3 --> 3 (int)
      99 / 100 --> 0 (int)

      we need to convert one of the operand to be a float
  */

}

//step 3 for serial is to open the Serial monitor