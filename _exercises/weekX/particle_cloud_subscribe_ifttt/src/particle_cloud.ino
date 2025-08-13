/*
  Publish
  -------
  - first demonstrate switch working on serial monitor
  - design logic first
  - create publish statements
  - demonstrate publish in console

  Variable
  --------
  - motivation: What if we aren't watching the event? how can we know
    what the current state is?
  - publish variable
  - check on app that status changes

  Function
  --------
  -      create function to turn on / off LED
  - register, test with cloud
  - optional: have them do blink
  - question: how do we know if light is on or not? --> add state variale
  - then create light state and register it
  - show that on the website, the state of light doesn't automatically update\\

  Subscribe
  =========
  - discuss goal: work in pairs, and have an open door on one student's device
  make your LED turn on
  - have each team create a unique event name
      TAC348/Door/<<UNIQUE_NAME>>
  - create event handler
  - register subscriber

  IFTTT
  =====
  - set If <EVENT_NAME> open, then send notification
  - create new function to override alarm based on location (describe)
*/

// 1. PUBLISH
const int PIN_SWITCH = D2;
int switchVal;  // low = closed, high = open
bool doorOpen = false;

// 3. FUNCTION
const int PIN_LED = D3;
// 3b. FUNCTION
bool lightOn = false;

// 5. IFTTT
bool isAlarmArmed = true;

void setup() {
    // 1. PUBLISH
    Serial.begin(9600);
    pinMode(PIN_SWITCH, INPUT);

    // 2. VARIABLE
    Particle.variable("doorOpen", doorOpen);

    // 3. FUNCTION
    pinMode(PIN_LED, OUTPUT);

    Particle.function("changeLED", changeLEDState);

    // 3b. FUNCTION
    Particle.variable("lightOn", lightOn);

    // 4. SUBSCRIBE
    Particle.subscribe("TAC348/Door", doorEventHandler, ALL_DEVICES);

    // 5. IFTTT
    Particle.function("setAlarmStatus", setAlarmStatus);
    Particle.variable("isAlarmArmed", isAlarmArmed);
}

void loop() {
    // 1. PUBLISH
    switchVal = digitalRead(PIN_SWITCH);
    // Serial.println("Switch val = " + String(switchVal));

    if (switchVal == HIGH) {  // just read that switch is open
        if (doorOpen ==
            false) {  // we do this so one event is fired, not endless events
            doorOpen = true;

            // 5. IFTTT only - add alarm trigger IF logic
            if (isAlarmArmed == true) {
                Particle.publish("TAC348/Door", "open");
            }
            Serial.println("\tDoor: closed -> open; doorOpen = " +
                           String(doorOpen));
        }
    } else {  // just read that switch is closed
        if (doorOpen ==
            true) {  // we do this so one event is fired, not endless events
            doorOpen = false;
            Particle.publish("TAC348/Door", "closed");
            Serial.println("\tDoor: open -> closed; doorOpen = " +
                           String(doorOpen));
        }
    }
}

// 3. FUNCTION
int changeLEDState(String command) {
    if (command.equalsIgnoreCase("on")) {
        digitalWrite(PIN_LED, HIGH);

        // 3b. FUNCTION
        lightOn = true;

        return 0;
    } else if (command.equalsIgnoreCase("off")) {
        digitalWrite(PIN_LED, LOW);

        // 3b. FUNCTION
        lightOn = false;
        return 0;
    }
    return -1;
}

// 4. SUBSCRIBE
void doorEventHandler(const char *event, const char *data) {
    String eventName = String(event);
    String eventData = String(data);

    if (eventName.equalsIgnoreCase("TAC348/Door")) {
        if (eventData.equalsIgnoreCase("closed")) {
            // call changeLEDState to make switch on another students device
            // affect light
            changeLEDState("off");
            Particle.publish("TAC348/Door-Partner", "closed door -> LED off");

        } else if (eventData.equalsIgnoreCase("open")) {
            // call changeLEDState to make switch on another students device
            // affect light
            changeLEDState("on");
            Particle.publish("TAC348/Door-Partner", "open door -> LED on");
        }
    }
}

// 5. IFTTT
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