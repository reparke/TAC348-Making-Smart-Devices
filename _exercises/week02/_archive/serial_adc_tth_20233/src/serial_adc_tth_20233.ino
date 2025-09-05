const int PIN_LED = A1;
const int PIN_POT = A0;

void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_POT, INPUT);
    Serial.begin(9600);  // step 1 for serial
}

void loop() {
    int potValue = analogRead(PIN_POT);

    // PWM is for analog output--take values 0 - 255
    // ADC is for measuring analog input--take values 0 - 4095

    // use the potentiometer to change the LED brightness
    // don't change the wiring

    // physically turn the pot
    // read the change of the pot
    // convert the pot value into something that control the LED
    // change the LED accordingly

    int pwmValue = float(potValue) / 4095 * 255;

    //input range: 0 - 4095 "digital units"
    //output range: 0- 255 PWM values


    // step 2 for serial
    Serial.println("The pot value = " + String(potValue) +
                   " and the pwm value = " + String(pwmValue));
    analogWrite(PIN_LED, pwmValue);
    delay(100);
}

// step 3 for serial is to open the serial monitor