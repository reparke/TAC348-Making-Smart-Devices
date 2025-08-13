/*
TAC348/Door/PARTNERNAME

*/

const int PIN_SWITCH = D2;
const int PIN_LED = D3;

int switchVal;
bool doorOpen = false;
String doorStatus = "closed";
bool lightOn = false;

bool isAlarmArmed = true;

// alarm function handler
int setAlarmStatus(String update) {
    if (update.equalsIgnoreCase("arm")) {
        isAlarmArmed = true;
        return 0;
    } else if (update.equalsIgnoreCase("disarm")) {
        isAlarmArmed = false;
        return 0;
    } else {
        return -1;
    }
}

// setup() runs once, when the device is first turned on.
void setup() {
    pinMode(PIN_SWITCH, INPUT);
    pinMode(PIN_LED, OUTPUT);
    Serial.begin(9600);

    // register a cloud variable
    Particle.variable("doorOpen", doorOpen);
    Particle.variable("switchVal", switchVal);
    Particle.variable("doorStatus", doorStatus);
    Particle.variable("lightOn", lightOn);

    // register a cloud function
    Particle.function("changeLED", changeLedStatus);
    Particle.function("setAlarmStatus", setAlarmStatus);

    // 4. SUBSCRIBE
    Particle.subscribe("TAC348/Door", doorEventHandler, ALL_DEVICES);
}

void loop() {
    switchVal = digitalRead(PIN_SWITCH);
    Serial.println("SwitchVal = " + String(switchVal));

    /*
      What does a door opened mean?
        switch is low AND door open is true

      when is door closed?
        switch is high and door open is false
    */

    if (switchVal == LOW) {  // switch (door) is currently closed
        if (doorOpen ==
            true) {  // door was PREVIOSULY close   --> door JUST opend
            doorOpen = false;
            doorStatus = "closed";
            Particle.publish("TAC348/Door", "closed", PUBLIC);
            changeLedStatus("off");
        }
    } else {  // swtich is currently open
        if (doorOpen ==
            false) {          // door was previously open --> door just closed
            doorOpen = true;  // when door is open
            doorStatus = "open";
            if (isAlarmArmed == true) {
                Particle.publish("TAC348/Door", "opened", PUBLIC);
            }
            changeLedStatus("on");
        }
    }
}

// in order to trigger LED remotely, we need separate function
// in prepartion, function needs:
//     return an int
//     take exactly one String parameter
// generally, convention is return 0 if succcess, -1 if error
int changeLedStatus(String command) {
    if (command.equalsIgnoreCase("on")) {  // equivalent to command == "on"
        digitalWrite(PIN_LED, HIGH);
        lightOn = true;
        return 0;
    } else if (command.equalsIgnoreCase("off")) {
        digitalWrite(PIN_LED, LOW);
        lightOn = false;
        return 0;
    } else {
        return -1;
    }
}

// 4. SUBSCRIBE
void doorEventHandler(const char *event, const char *data) {
    String eventName = String(event);
    String eventData = String(data);

    if (eventName.equalsIgnoreCase("TAC348/Door")) {
        if (eventData.equalsIgnoreCase("closed")) {
            // call changeLEDState to make switch on another students device
            // affect light
            changeLedStatus("off");
            Particle.publish("TAC348/Door-Partner", "closed door -> LED off");

        } else if (eventData.equalsIgnoreCase("open")) {
            // call changeLEDState to make switch on another students device
            // affect light
            changeLedStatus("on");
            Particle.publish("TAC348/Door-Partner", "open door -> LED on");
        }
    }
}