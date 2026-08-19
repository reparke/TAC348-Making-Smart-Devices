/*
A) Connect physiscal to EN pin
    -use switch to enable / disable (turn on / off) device

b) connect button any GPIO pin
    -use button to sleep /wake device

what is the difference between A and B?
    A TURNS OFF the device fully
        pro: uses NO power at all
        con: erases any variable you had in memory
    B SLEEPS device
        pro: preservers all variables in memory
        con: use some power


*/









#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_PIR = D2;
const int PIN_BUTTON = D10;
int count = 0;
int prevAlarm = LOW;

unsigned long WAKE_DURATION = 60000; //how long device is awake for
unsigned long SLEEP_DURATION = 20000; //sleeping
unsigned long prevMillis = 0;

int prevButton = HIGH;

void setup() {
    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}

//example 1 - timer
void wakeOnTimer() {
    // set a millis timer for long the device should AWAKE
    //when the timer expires, put the device to sleep for a certain time
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > WAKE_DURATION) {
        prevMillis = curMillis; //go to sleep
        Serial.println("About to go sleep...");

        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER).duration(SLEEP_DURATION);
        System.sleep(config);

        Serial.println("...just woke up");
    }
}

//example 2 - button
void wakeOnButton() {
    //press a button to make device to go to sleep
    // and configure so that another button press wakes it up
    int currButton = digitalRead(PIN_BUTTON);
    if(currButton == LOW && prevButton == HIGH) {
        Serial.println("about to sleep on button press");

        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER).gpio(PIN_BUTTON, FALLING).gpio(PIN_PIR,RISING);
        //now it will WAKE if we press button OR it detects movement
        System.sleep(config);
    }
    prevButton = currButton;
}

void loop() {
    // wakeOnTimer();
    wakeOnButton();

    // int currentAlarm = digitalRead(PIN_PIR);
    // HIGH movement detected
    // LOW no movement detected

    // if(currentAlarm == HIGH) {
    //     Serial.println(String(count++) + ": Movement detected");
    // }

    // what if instead we wanted ONE message that says Movement Detected, and
    // then stopped?

    // mvmt detected
    // if (currentAlarm == HIGH && prevAlarm == LOW) {
    //     Serial.println("Movement has started");
    // } else if (currentAlarm == LOW && prevAlarm == HIGH) {
    //     Serial.println("Movement has stopped");
    // }
    // prevAlarm = currentAlarm;
}