const int PIN_RGB_RED = A2;
const int PIN_RGB_GREEN = A5;
const int PIN_RGB_BLUE = D15; // aka MOSI pin


void changeLedColor(int r, int g, int b) {
    // theoretical "recipe" or algorithm using these input
    analogWrite(PIN_RGB_RED, r);
    analogWrite(PIN_RGB_GREEN, g);
    analogWrite(PIN_RGB_BLUE, b);
}

void setup() {
    Serial.begin(9600);
    pinMode(PIN_RGB_RED, OUTPUT);
    pinMode(PIN_RGB_GREEN, OUTPUT);
    pinMode(PIN_RGB_BLUE, OUTPUT);
}

void loop() {
  
}