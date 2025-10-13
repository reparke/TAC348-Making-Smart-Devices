/*Note: This corresponds to locally installed project "Week 6", tab "Demo"
  Features
    - Button to control onboard LED on V5 (app --> argon)
    - display for random number on V6 (argon --> app)
    - virtual LED represents random value on V6 (argon --> app)
*/

const int PIN_LED = D7;
const int PIN_RED = D3;
const int PIN_GREEN = D4;
const int PIN_BLUE = D5;
const int PIN_SWITCH = D2;

int prevDoorState = HIGH;
int currDoorState = HIGH;

void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
}

void loop() {
    currDoorState = digitalRead(PIN_SWITCH);
    // Serial.println(currDoorState);
    if (currDoorState == LOW && prevDoorState == HIGH) {
        Serial.println("Door was closed");
        Particle.publish("Door state", "Door was closed");
        analogWrite(PIN_RED, 255);
        analogWrite(PIN_GREEN, 0);
        analogWrite(PIN_BLUE, 0);
    } else if (currDoorState == HIGH && prevDoorState == LOW) {
        Serial.println("Door was opened");
        Particle.publish("Door State", "Door was opened");
        analogWrite(PIN_RED, 255);
        analogWrite(PIN_GREEN, 255);
        analogWrite(PIN_BLUE, 255);
    }
    prevDoorState = currDoorState;
}
