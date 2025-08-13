const int PIN_LED = D7;

const int PIN_SWITCH = D2;
int switchRead;  // magnetic switch

bool isDoorOpen = false;
const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;  // aka MOSI

void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);

    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);

    Particle.variable("isDoorOpen",
                      isDoorOpen);  // particle variables need to be GLOBAL
    Particle.function("blinkLed", blinkLed);

    // subscribe to partner's event
    Particle.subscribe("TAC348/Door/NH", switchEventHandler, ALL_DEVICES);
    blinkLed("twice");
}

void loop() {
    switchRead = digitalRead(PIN_SWITCH);

    if (switchRead == HIGH) {  // just read that switch is open
        if (isDoorOpen == false) {
            isDoorOpen = true;
            Particle.publish("TAC348/Door/REP", "closed --> open");
        }
    } else {  // just read that switch is closed
        if (isDoorOpen == true) {
            isDoorOpen = false;
            Particle.publish("TAC348/Door/REP", "open --> closed");
        }
    }
}

void switchEventHandler(const char *event, const char *data) {
    String eventName = String(event);
    String eventData = String(data);  // convert the pointer to be string

    if (eventName.equalsIgnoreCase("TAC348/Door/NH")) {
        if (eventData.equalsIgnoreCase("closed --> open")) {
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 0);
            analogWrite(PIN_BLUE, 0);
        }  // open to close
        else {
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 255);
        }
    }
}
// this is a particle function
int blinkLed(String cmd) {
    Serial.println(cmd);
    if (cmd.equals("twice")) {
        analogWrite(PIN_RED, 255);
        analogWrite(PIN_GREEN, 255);
        analogWrite(PIN_BLUE, 255);
        delay(500);
        analogWrite(PIN_RED, 0);
        analogWrite(PIN_GREEN, 0);
        analogWrite(PIN_BLUE, 0);
        delay(500);
        analogWrite(PIN_RED, 255);
        analogWrite(PIN_GREEN, 255);
        analogWrite(PIN_BLUE, 255);
        delay(500);
        analogWrite(PIN_RED, 0);
        analogWrite(PIN_GREEN, 0);
        analogWrite(PIN_BLUE, 0);
        delay(500);
    } else if (cmd.equals("once")) {
        analogWrite(PIN_RED, 255);
        analogWrite(PIN_GREEN, 255);
        analogWrite(PIN_BLUE, 255);
        delay(500);
        analogWrite(PIN_RED, 0);
        analogWrite(PIN_GREEN, 0);
        analogWrite(PIN_BLUE, 0);
        delay(500);
    }
    return 0;
}

// int blinkLed(String cmd) {
//     Serial.println("IFTTT function input: " + cmd);
//     if (cmd.equalsIgnoreCase("twice")) {
//         digitalWrite(PIN_LED, HIGH);
//         delay(1000);
//         digitalWrite(PIN_LED, LOW);
//         delay(1000);
//     }
//     digitalWrite(PIN_LED, HIGH);
//     delay(1000);
//     digitalWrite(PIN_LED, LOW);
//     delay(1000);
// }