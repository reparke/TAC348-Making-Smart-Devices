const int PIN_LED = D7;
const int PIN_RED = D3;
const int PIN_GREEN = D4;
const int PIN_BLUE = D5;
const int PIN_SWITCH = D2;
enum Color { WHITE, GREEN, MAGENTA, YELLOW, RED };

enum DoorState { OPEN, CLOSED };
DoorState myDoor = OPEN;

void displayColors(Color c) {
    switch (c) {
        case WHITE:
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 255);
            break;
        case GREEN:
            analogWrite(PIN_RED, 0);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 0);
            break;
        case MAGENTA:
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 0);
            analogWrite(PIN_BLUE, 255);
            break;
        case YELLOW:
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 0);
            break;
        case RED:
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 0);
            analogWrite(PIN_BLUE, 0);
            break;
    }
}

void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);

    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);

    // subscribe to partner's event
    Particle.subscribe("TAC348/Door/RP", switchEventHandler, ALL_DEVICES);
    displayColors(MAGENTA);
    delay(1000);
}

void loop() {
    int switchRead = digitalRead(PIN_SWITCH);

    if (switchRead == HIGH) {  // just read that switch is open
        if (myDoor == CLOSED) {
            myDoor = OPEN;
            Particle.publish("TAC348/Door/RP", "doorIsOpen");
            Serial.println("Local door: doorIsOpen");
        }
    } else {  // just read that switch is closed
        if (myDoor == OPEN) {
            myDoor = CLOSED;
            Particle.publish("TAC348/Door/RP", "doorIsClosed");
            Serial.println("Local door: doorIsClosed");
        }
    }
}

void switchEventHandler(const char *event, const char *data) {
    String eventName = String(event);
    String eventData = String(data);  // convert the pointer to be string
    Serial.println("Remote:\n" + String(event) + "\n" + String(data));
    if (eventName.equalsIgnoreCase("TAC348/Door/RP")) {
        if (eventData.equalsIgnoreCase("doorIsOpen")) {
            Serial.println("Remote door: doorIsOpen");

            displayColors(RED);
        } else {  // open to close
            Serial.println("Remote door: doorIsClosed");

            displayColors(WHITE);
        }
    }
}