const int PIN_SWITCH = D2;
const int PIN_LED = D3;

// state
bool isDoorOpen = false;
bool isLedOn = false;
int switchRead;

void setup() {
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);

    // register
    Particle.variable("isDoorOpen", isDoorOpen);
    Particle.variable("isLedOn", isLedOn);

    // register function
    Particle.function("ledStatus", ledStatus);
}

void loop() {
    switchRead = digitalRead(PIN_SWITCH);

    if (switchRead == HIGH) {  // just read that switch is open
        if (isDoorOpen == false) {
            isDoorOpen = true;
            Particle.publish("TAC348/Door", "closed --> open");
        }
    } else {  // just read that switch is closed
        if (isDoorOpen == true) {
            isDoorOpen = false;
            Particle.publish("TAC348/Door", "open --> closed");
        }
    }
}

// define the function that will be called by the cloud
// ALWAYS return an int, and takes one String parameter
int ledStatus(String cmd) {
    if (cmd.equalsIgnoreCase("on")) {  // turn LED on

        digitalWrite(PIN_LED, HIGH);
        isLedOn = true;

        return 0;                              // 0 represents OK
    } else if (cmd.equalsIgnoreCase("off")) {  // turn LED on

        digitalWrite(PIN_LED, LOW);
        isLedOn = false;

        return 0;
    }

    return -1;  // this means error
}
