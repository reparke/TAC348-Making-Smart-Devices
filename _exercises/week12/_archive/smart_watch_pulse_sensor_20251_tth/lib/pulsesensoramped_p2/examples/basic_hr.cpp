#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int pulseSignalPin = A0;

#include <PulseSensorAmped.h>

PulseSensor PulseSensorAmped;

void setup() {
    // bug fix for the argon
    analogRead(pulseSignalPin);  // anytime you are using the HR sensor, put
                                 // this line first in setup()

    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    Serial.println("Starting");
    PulseSensorAmped.attach(pulseSignalPin);
    PulseSensorAmped.start();
}

void loop() {
    delay(100);
    // Must process Pulse Sensor updates in main event loop
    PulseSensorAmped.process();
}

// An optional function to recieve the Beats Per Minute (BPM) and Interbeat
// Interval (IBI) in mS
void PulseSensorAmped_data(int BPM, int IBI) {
    Serial.print("BPM:");
    Serial.print(BPM);
    Serial.print(" IBI: ");
    Serial.println(IBI);
}

// An optional function to indicate that the pulse signal has been lost
// (Due to the nature of pulse detection via reflected light, spurios signals
// are possible.
//  i.e. received data may not be valid)
void PulseSensorAmped_lost(void) { Serial.println("Pulse Lost"); }
