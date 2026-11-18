#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int pulseSignalPin = A1;
// Minimum filtered pulse swing, in 12-bit ADC counts (0-4095).
// Start here; use the PP diagnostic before adjusting sensitivity.
const int minimumPulseAmplitude = 60;
// Temporarily enabled for the no-finger capture in Workbench's read-only monitor.
// Restore false after capture. Two-way terminals can also toggle with 'd'.
bool printPulseDiagnostics = true;

#include <PulseSensorAmped.h>

PulseSensor PulseSensorAmped;

void setup() {
    // bug fix for the argon
    analogRead(pulseSignalPin);  // anytime you are using the HR sensor, put
                                 // this line first in setup()

    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    Serial.println("Starting pulse sensor: local test, waiting for 3 consistent intervals");
    Serial.println(printPulseDiagnostics ? "Pulse diagnostics enabled at startup"
                                        : "Pulse diagnostics disabled at startup");
    PulseSensorAmped.attach(pulseSignalPin);
    PulseSensorAmped.setMinimumAmplitude(minimumPulseAmplitude);
    PulseSensorAmped.start();
}

void loop() {
    // Must process Pulse Sensor updates in main event loop
    PulseSensorAmped.process();

    static uint32_t lastDiagnostic = millis();
    if (Serial.available()) {
        const int command = Serial.read();
        if (command == 'd' || command == 'D') {
            printPulseDiagnostics = !printPulseDiagnostics;
            // Discard the disabled interval so the first reported sample rate
            // and peak-to-peak range describe only the new capture window.
            PulseSensorAmped.getDiagnostics();
            lastDiagnostic = millis();
            Serial.println(printPulseDiagnostics ? "Pulse diagnostics enabled"
                                                 : "Pulse diagnostics disabled");
        }
    }
    const uint32_t now = millis();
    if (printPulseDiagnostics && now - lastDiagnostic >= 1000) {
        const uint32_t elapsed = now - lastDiagnostic;
        lastDiagnostic = now;
        const auto d = PulseSensorAmped.getDiagnostics();
        Serial.printf("RAW:%d FILTERED:%d PP:%d THRESH:%d MIN_AMP:%d "
                      "SAMPLES_PER_SEC:%lu MAX_GAP_MS:%lu STATE:%s\r\n",
                      d.raw, d.filtered, d.peakToPeak, d.threshold,
                      minimumPulseAmplitude,
                      static_cast<unsigned long>(d.samples * 1000 / elapsed),
                      static_cast<unsigned long>(d.maxGapMs),
                      d.tracking ? "tracking" : "acquiring");
    }
    delay(1);
}

// An optional function to recieve the Beats Per Minute (BPM) and Interbeat
// Interval (IBI) in mS
//event handler - event driven programming
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
void PulseSensorAmped_lost(void) {
    Serial.println("Pulse Lost: signal too weak, no beat, or sampling gap; reacquiring");
}
