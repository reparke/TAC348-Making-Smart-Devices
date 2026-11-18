#ifndef PULSE_INTERRUPT_H
#define PULSE_INTERRUPT_H

#include "Particle.h"

// Callbacks run in process(), on the application thread.
extern void PulseSensorAmped_data(int BPM, int IBI) __attribute__((weak));
extern void PulseSensorAmped_lost(void) __attribute__((weak));

class PulseSensor {
   public:
    struct Diagnostics {
        int raw;
        int filtered;
        int threshold;
        int peakToPeak;  // Filtered signal range since the previous snapshot.
        uint32_t samples;
        uint32_t maxGapMs;
        bool tracking;
    };

    PulseSensor();
    void attach(int pin);
    void process();
    void start();
    void setMinimumAmplitude(int adcCounts);
    Diagnostics getDiagnostics();

   private:
    static constexpr int ADC_MIDPOINT = 2048;
    static constexpr uint32_t SAMPLE_MS = 2;
    static constexpr uint32_t MAX_SAMPLE_GAP_MS = 20;
    static constexpr uint32_t LOST_MS = 2500;
    static constexpr int FILTER_TIME_MS = 12;
    static constexpr int HYSTERESIS = 10;
    static constexpr int ACQUISITION_INTERVALS = 3;
    static constexpr int ACQUISITION_SPREAD_PERCENT = 25;

    // Timer callbacks are a separate thread, not hardware interrupts.
    // Declare the mutex first so it outlives the timer during destruction.
    Mutex stateMutex;
    Timer pulseTimer;
    int pulsePin = A1;
    int blinkPin = D7;
    int minimumAmplitude = 60;

    int rate[10] = {};
    int acquisitionIntervals[ACQUISITION_INTERVALS] = {};
    int acquisitionCount = 0;
    uint32_t lastSampleTime = 0;
    uint32_t lastBeatTime = 0;
    int P = ADC_MIDPOINT;
    int T = ADC_MIDPOINT;
    int thresh = ADC_MIDPOINT;
    bool firstBeat = true;
    bool Pulse = false;
    bool tracking = false;
    bool lossReported = false;
    bool beatPending = false;
    bool lossPending = false;
    int BPM = -1;
    int IBI = 600;
    int rawSignal = 0;
    int filteredSignal = 0;
    int32_t firstStageScaled = 0;
    int32_t filteredScaled = 0;

    int windowMin = 4095;
    int windowMax = 0;
    uint32_t sampleCount = 0;
    uint32_t maxGapMs = 0;

    void sample();
    // Caller holds stateMutex for the following helpers.
    void resetDetector(uint32_t now);
    void loseSignal(uint32_t now);
};

#endif
