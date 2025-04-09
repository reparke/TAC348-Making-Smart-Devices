
#ifndef PULSE_INTERRUPT_H
#define PULSE_INTERRUPT_H

#include "Particle.h"

// The "beats updated" callback; Called when valid pulse data is available.
// Passed Estimated Beats Per Minute and Interbeat Interval
// extern void PulseSensorAmped_data(int BPM, int IBI, int counter) __attribute__((weak));
// // The "signal lost" callback; Called when no more valid pulse data is
// // avaialble.
// extern void PulseSensorAmped_lost(void) __attribute__((weak));

class PulseSensor {
   public:
    PulseSensor();
    void attach(int pin);
    void process();
    void start();
    int getBPM();
    int getIBI();
    boolean beatDetected();
    volatile int counter; //for texting

   private:

    volatile int rate[10];                 // array to hold last ten IBI values
    volatile unsigned long sampleCounter;  // used to determine pulse timing
    volatile unsigned long lastBeatTime;   // used to find IBI
    volatile int P;       // used to find peak in pulse wave, seeded
    volatile int T;       // used to find trough in pulse wave, seeded
    volatile int thresh;  // used to find instant moment of heart beat, seeded
    volatile int amp;     // used to hold amplitude of pulse waveform, seeded
    volatile boolean
        firstBeat;  // used to seed rate array so we startup with reasonable BPM
    volatile boolean secondBeat;  // used to seed rate array so we startup with
                                  // reasonable BPM

    // these variables are volatile because they are used during the thread function
    volatile int BPM;        // used to hold the pulse rate
    volatile int rawSignal;  // holds the incoming raw data
    volatile int IBI;        // holds the time between beats, must be seeded!
    volatile boolean
        Pulse;            // true when pulse wave is high, false when it's low
    volatile boolean QS;  // becomes true when Arduoino finds a beat.

    //  VARIABLES
    int pulsePin;       // Pulse Sensor purple wire connected to analog pin 0
    int blinkPin = D7;  // pin to blink led at each beat
    int fadePin = D6;   // pin to do fancy classy fading blink at each beat
    int fadeRate = 0;   // used to fade LED on with PWM on fadePin

    friend void pulseISR(void);
    friend void threadFunction(void);
};

extern PulseSensor pulseSensor;

#endif