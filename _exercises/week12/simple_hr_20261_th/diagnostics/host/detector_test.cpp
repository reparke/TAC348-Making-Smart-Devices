// Exercise the actual library C++ using synthetic ADC input and a fake clock.
#include "PulseSensorAmped.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

uint32_t testNow = 0;
int testSignal = 2048;
struct Beat { uint32_t time; int bpm; int ibi; };
std::vector<Beat> beats;
int lostCount = 0;
PulseSensor* currentSensor = nullptr;

void PulseSensorAmped_data(int bpm, int ibi) {
    beats.push_back({testNow, bpm, ibi});
    // This would deadlock if process() invoked callbacks holding stateMutex.
    assert(currentSensor->getDiagnostics().tracking);
}

void PulseSensorAmped_lost() {
    ++lostCount;
    currentSensor->getDiagnostics();
}

int wave(uint32_t t, double bpm = 100, double amplitude = 200) {
    return static_cast<int>(std::lround(2048 + amplitude *
        std::sin(2 * 3.141592653589793 * t * bpm / 60000)));
}

struct Fixture {
    PulseSensor sensor;
    uint32_t origin;

    explicit Fixture(uint32_t start = 0, int initial = 2048) : origin(start) {
        testNow = start;
        testSignal = initial;
        beats.clear();
        lostCount = 0;
        currentSensor = &sensor;
        sensor.attach(A1);
        sensor.setMinimumAmplitude(60);
        sensor.start();
    }

    void sample(uint32_t t, int raw) {
        testNow = origin + t;
        testSignal = raw;
        Timer::tick();
        sensor.process();
    }

    void expectRate(int expected) {
        assert(beats.size() >= 5);
        for (auto it = beats.end() - 5; it != beats.end(); ++it) {
            if (std::abs(it->bpm - expected) > 2 ||
                std::abs(it->ibi - 60000 / expected) > 8) {
                std::cerr << "Expected " << expected << " BPM; got "
                          << it->bpm << ", IBI " << it->ibi << '\n';
            }
            assert(std::abs(it->bpm - expected) <= 2);
            assert(std::abs(it->ibi - 60000 / expected) <= 8);
        }
    }
};

int main() {
    for (int bpm : {40, 60, 100, 180, 230}) {
        Fixture f;
        for (uint32_t t = 2; t <= 20000; t += 2) f.sample(t, wave(t, bpm));
        f.expectRate(bpm);
        assert(lostCount == 0);
        std::cout << "PASS clean " << bpm << " BPM\n";
    }
    for (int hz : {50, 60}) {
        Fixture f;
        for (uint32_t t = 2; t <= 20000; t += 2)
            f.sample(t, wave(t, hz * 60, 15));
        assert(beats.empty());
        assert(lostCount == 1);
        std::cout << "PASS reject " << hz << " Hz low-amplitude noise\n";
    }
    {
        Fixture f;
        for (uint32_t t = 2; t <= 20000; t += 2)
            f.sample(t, wave(t) + wave(t, 3600, 100) - 2048);
        f.expectRate(100);
        std::cout << "PASS 100 BPM with superimposed 60 Hz noise\n";
    }
    {
        Fixture f;
        for (uint32_t t = 2; t <= 20000; t += 2) {
            const double amplitude = t < 6000 ? 200 :
                std::max(0.0, 200.0 * (1 - (t - 6000) / 3000.0));
            f.sample(t, wave(t, 100, amplitude) +
                (t < 6000 ? 0 : wave(t, 3600, 15) - 2048));
        }
        assert(!beats.empty() && beats.back().time < 12000);
        assert(lostCount == 1);
        assert(!f.sensor.getDiagnostics().tracking);
        std::cout << "PASS fading pulse reports loss instead of sustained 230 BPM\n";
    }
    {
        Fixture f(0, 1900);
        for (uint32_t t = 2; t <= 20000; t += 2)
            f.sample(t, t < 4000 ? 1900 : wave(t));
        f.expectRate(100);
        assert(lostCount == 1);
        std::cout << "PASS recover after flat signal timeout\n";
    }
    {
        Fixture f;
        for (uint32_t t = 4; t <= 20000; t += 4) f.sample(t, wave(t));
        f.expectRate(100);
        std::cout << "PASS 4 ms callbacks still measure 100 BPM\n";
    }
    {
        Fixture f;
        for (uint32_t t = 2; t <= 6000; t += 2) f.sample(t, wave(t));
        const auto before = beats.size();
        for (int i = 0; i < 100; ++i) f.sample(6000, wave(6000));
        assert(beats.size() == before);
        f.sample(6200, wave(6200));
        assert(lostCount == 1);
        assert(!f.sensor.getDiagnostics().tracking);
        for (uint32_t t = 6202; t <= 20000; t += 2) f.sample(t, wave(t));
        f.expectRate(100);
        std::cout << "PASS skip callback bursts and reacquire after sampling gap\n";
    }
    {
        Fixture f(UINT32_MAX - 3000);
        for (uint32_t t = 2; t <= 20000; t += 2) f.sample(t, wave(t));
        f.expectRate(100);
        assert(lostCount == 0);
        std::cout << "PASS millis rollover\n";
    }
    {
        Fixture f;
        for (uint32_t t = 2; t <= 1000; t += 2) f.sample(t, 2048);
        auto d = f.sensor.getDiagnostics();
        assert(d.samples == 500 && d.maxGapMs == 2 && d.peakToPeak == 0);
        d = f.sensor.getDiagnostics();
        assert(d.samples == 0 && d.maxGapMs == 0 && d.peakToPeak == 0);
        std::cout << "PASS diagnostic counters reset on snapshot\n";
    }
}
