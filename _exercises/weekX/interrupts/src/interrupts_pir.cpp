#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

const int PIN_PIR = D3;           // Input pin for the motion sensor (Trigger)
const int PIN_BUTTON = D2;  // Input pin for the acknowledge/reset button
const int PIN_ONBOARD_LED = D7;     // Output pin for the alarm indicator

// The volatile flag that tracks the alarm state.
volatile bool alarmActive = false;

// -----------------------------------------------------------------
// ISR #1: Alarm Trigger (PIR Sensor)
// This is the CRITICAL action. Runs immediately upon motion detected.
// -----------------------------------------------------------------
void triggerAlarmISR() {
    // 1. Take the most critical action: Turn the LED ON
    digitalWrite(PIN_ONBOARD_LED, HIGH);

    // 2. Set the global flag so loop() knows the critical event occurred.
    alarmActive = true;
}

// -----------------------------------------------------------------
// ISR #2: Alarm Reset (Acknowledge Button)
// Runs immediately upon button press to silence the immediate alert.
// -----------------------------------------------------------------
void resetAlarmISR() {
    // 1. Critical action: Turn the LED OFF
    digitalWrite(PIN_ONBOARD_LED, LOW);

    // 2. Reset the flag to signal the loop() that the event is acknowledged.
    alarmActive = false;
}

void setup() {
    // Configure output pin
    pinMode(PIN_ONBOARD_LED, OUTPUT);

    // Configure PIR pin. PIR sensors typically need simple INPUT.
    pinMode(PIN_PIR, INPUT);

    // Configure Button pin. Since students use a pull-up resistor, we use
    // INPUT.
    pinMode(PIN_BUTTON, INPUT);

    // Attach Interrupt 1: PIR
    // PIR goes RISING when motion is detected
    attachInterrupt(PIN_PIR, triggerAlarmISR, RISING);

    // Attach Interrupt 2: Button Reset
    // Button with pull-up resistor goes FALLING when pressed
    attachInterrupt(PIN_BUTTON, resetAlarmISR, FALLING);

    Serial.begin(9600);
    Serial.println("System Ready. Waiting for motion...");
}

void loop() {
    // The loop's job is to handle the SLOW, complex tasks based on the flag
    if (alarmActive) {
        // Alarm is active! Log the event and send a notification.
        Serial.println("!!! ALARM: Motion Detected !!!");
        // Particle.publish("ALERT", "Motion triggered!", PRIVATE); // Example
        // slow task You may add a slight delay here to prevent spamming the
        // serial/cloud
        delay(500);
    } else {
        // Alarm is inactive or has been reset.
        // The system can now perform other tasks or sleep.
    }
}