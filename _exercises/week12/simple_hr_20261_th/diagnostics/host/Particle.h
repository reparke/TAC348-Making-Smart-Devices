// Host-only Particle substitutes. Never include this directory in firmware.
#pragma once
#include <cstdint>
#include <functional>
#include <mutex>

constexpr int A1 = 1;
constexpr int D7 = 7;
constexpr int OUTPUT = 1;
constexpr int LOW = 0;
constexpr int HIGH = 1;

extern uint32_t testNow;
extern int testSignal;
inline uint32_t millis() { return testNow; }
inline int analogRead(int) { return testSignal; }
inline void digitalWrite(int, int) {}
inline void pinMode(int, int) {}
inline int constrain(int value, int low, int high) {
    return value < low ? low : (value > high ? high : value);
}
using Mutex = std::mutex;

class Timer {
   public:
    template <typename T>
    Timer(unsigned, void (T::*method)(), T& object)
        : callback([&object, method] { (object.*method)(); }) {
        active = this;
    }
    ~Timer() { active = nullptr; }
    void start() { running = true; }
    void stop() { running = false; }
    static void tick() {
        if (active && active->running) active->callback();
    }

   private:
    inline static Timer* active = nullptr;
    std::function<void()> callback;
    bool running = false;
};
