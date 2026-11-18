#include "PulseSensorAmped.h"
#include <mutex>

PulseSensor::PulseSensor() : pulseTimer(SAMPLE_MS, &PulseSensor::sample, *this) {}

void PulseSensor::attach(int pin) {
    std::lock_guard<Mutex> lock(stateMutex);
    pulsePin = pin;
}

void PulseSensor::setMinimumAmplitude(int adcCounts) {
    std::lock_guard<Mutex> lock(stateMutex);
    // Keep the amplitude gate wider than the hysteresis band.
    minimumAmplitude = constrain(adcCounts, 2 * HYSTERESIS + 1, 4095);
}

void PulseSensor::resetDetector(uint32_t now) {
    P = T = thresh = ADC_MIDPOINT;
    lastBeatTime = now;
    firstBeat = true;
    acquisitionCount = 0;
    Pulse = false;
    tracking = false;
    BPM = -1;
    IBI = 600;
    beatPending = false;
    for (int& interval : rate) {
        interval = 0;
    }
    digitalWrite(blinkPin, LOW);
}

void PulseSensor::loseSignal(uint32_t now) {
    resetDetector(now);
    if (!lossReported) {
        lossPending = true;
        lossReported = true;
    }
}

void PulseSensor::start() {
    // Do not hold stateMutex while sending commands to the timer thread.
    pulseTimer.stop();
    {
        std::lock_guard<Mutex> lock(stateMutex);
        pinMode(blinkPin, OUTPUT);
        rawSignal = analogRead(pulsePin);
        filteredSignal = rawSignal;
        firstStageScaled = filteredScaled = rawSignal * 256;
        lastSampleTime = millis();
        resetDetector(lastSampleTime);
        lossReported = lossPending = false;
        windowMin = 4095;
        windowMax = 0;
        sampleCount = maxGapMs = 0;
    }
    pulseTimer.start();
}

void PulseSensor::sample() {
    std::lock_guard<Mutex> lock(stateMutex);
    // A delayed software timer may invoke callbacks in a burst. Do not treat
    // those invocations as additional samples spaced 2 ms apart.
    if (static_cast<uint32_t>(millis() - lastSampleTime) < SAMPLE_MS) {
        return;
    }
    rawSignal = analogRead(pulsePin);
    const uint32_t now = millis();
    const uint32_t elapsed = now - lastSampleTime;
    lastSampleTime = now;
    ++sampleCount;
    if (elapsed > maxGapMs) {
        maxGapMs = elapsed;
    }

    if (elapsed > MAX_SAMPLE_GAP_MS) {
        // The missing waveform cannot be reconstructed. Reacquire instead of
        // calculating an interval across a gap or inventing catch-up samples.
        firstStageScaled = filteredScaled = rawSignal * 256;
        filteredSignal = rawSignal;
        loseSignal(now);
        return;
    }

    // Two low-pass stages suppress fast ripple that could end a pulse before
    // its peak. Use actual elapsed time and retain fractional ADC counts.
    const int32_t dt = static_cast<int32_t>(elapsed);
    firstStageScaled += (rawSignal * 256 - firstStageScaled) * dt /
                        (FILTER_TIME_MS + dt);
    filteredScaled += (firstStageScaled - filteredScaled) * dt /
                      (FILTER_TIME_MS + dt);
    filteredSignal = filteredScaled / 256;
    if (filteredSignal < windowMin) windowMin = filteredSignal;
    if (filteredSignal > windowMax) windowMax = filteredSignal;

    const uint32_t N = now - lastBeatTime;
    if (N > LOST_MS) {
        loseSignal(now);
        return;
    }

    const uint32_t refractory = (IBI / 5) * 3;
    if (filteredSignal < thresh && N > refractory && filteredSignal < T) {
        T = filteredSignal;
    }
    if (filteredSignal > thresh && filteredSignal > P) {
        P = filteredSignal;
    }

    // Keep the original 250 ms guard. Reject weak fluctuations using amplitude
    // and hysteresis rather than forcing the displayed BPM into a normal range.
    if (N > 250 && N > refractory && !Pulse &&
        filteredSignal > thresh + HYSTERESIS && P - T >= minimumAmplitude) {
        Pulse = true;
        digitalWrite(blinkPin, HIGH);
        IBI = static_cast<int>(N);
        lastBeatTime = now;

        if (firstBeat) {
            firstBeat = false;
            return;
        }

        if (!tracking) {
            // One long interval while placing the sensor must not seed all
            // ten entries and make the first BPM reading look artificially low.
            // Wait for three consistent measured intervals, at any rate.
            if (acquisitionCount == ACQUISITION_INTERVALS) {
                for (int i = 1; i < ACQUISITION_INTERVALS; ++i) {
                    acquisitionIntervals[i - 1] = acquisitionIntervals[i];
                }
                --acquisitionCount;
            }
            acquisitionIntervals[acquisitionCount++] = IBI;
            if (acquisitionCount < ACQUISITION_INTERVALS) return;

            int shortest = acquisitionIntervals[0];
            int longest = shortest;
            int sum = 0;
            for (int interval : acquisitionIntervals) {
                if (interval < shortest) shortest = interval;
                if (interval > longest) longest = interval;
                sum += interval;
            }
            const int mean = sum / ACQUISITION_INTERVALS;
            if ((longest - shortest) * 100 > mean * ACQUISITION_SPREAD_PERCENT) {
                return;
            }
            for (int& interval : rate) interval = mean;
            BPM = 60000 / mean;
        } else {
            uint32_t total = 0;
            for (int i = 0; i < 9; ++i) {
                rate[i] = rate[i + 1];
                total += rate[i];
            }
            rate[9] = IBI;
            total += IBI;
            BPM = 60000 / (total / 10);
        }
        tracking = true;
        lossReported = false;
        beatPending = true;
    }

    if (Pulse && filteredSignal < thresh - HYSTERESIS) {
        digitalWrite(blinkPin, LOW);
        Pulse = false;
        thresh = T + (P - T) / 2;
        P = T = thresh;
    }
}

void PulseSensor::process() {
    int bpm;
    int ibi;
    bool beat;
    bool lost;
    {
        std::lock_guard<Mutex> lock(stateMutex);
        bpm = BPM;
        ibi = IBI;
        beat = beatPending;
        lost = lossPending;
        beatPending = lossPending = false;
    }
    // Serial output and user callbacks must run without the state lock.
    if (lost && PulseSensorAmped_lost) PulseSensorAmped_lost();
    if (beat && PulseSensorAmped_data) PulseSensorAmped_data(bpm, ibi);
}

PulseSensor::Diagnostics PulseSensor::getDiagnostics() {
    std::lock_guard<Mutex> lock(stateMutex);
    Diagnostics result = {rawSignal, filteredSignal, thresh,
                          windowMax >= windowMin ? windowMax - windowMin : 0,
                          sampleCount, maxGapMs, tracking};
    windowMin = 4095;
    windowMax = 0;
    sampleCount = maxGapMs = 0;
    return result;
}
