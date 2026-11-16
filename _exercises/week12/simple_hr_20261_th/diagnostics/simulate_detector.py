"""Reproduce failures in a Python model of the ORIGINAL, pre-fix pulse detector.

Run: python3 diagnostics/simulate_detector.py

This preserves pulseISR() and start() as they existed before the November 16
fixes to lib/pulsesensoramped_p2/src/PulseSensorAmped.cpp. It does not execute
the current C++ firmware or emulate Particle's
scheduler/ADC, or use a recording from the physical sensor. The waveforms and
callback delays are synthetic experiments, not measurements of this device.
Only short runs with positive intervals are modeled; integer rollover and
foreground/callback races are outside this experiment.
"""

from math import pi, sin


class Detector:
    def __init__(self, timeout_midpoint=512):
        self.sample_counter = self.last_beat = 0
        self.peak = self.trough = self.threshold = 2048
        self.amplitude = 410
        self.first_beat, self.second_beat = True, False
        self.bpm, self.ibi = 0, 600
        self.pulse = False
        self.rates = [0] * 10
        self.timeout_midpoint = timeout_midpoint
        self.events, self.timeouts = [], []

    def sample(self, raw, wall_ms):
        # Deliberately preserve the library's assumed 2 ms per invocation,
        # independently of the real interval supplied by the experiment.
        self.sample_counter += 2
        elapsed = self.sample_counter - self.last_beat

        if raw < self.threshold and elapsed > (self.ibi // 5) * 3:
            if raw < self.trough:
                self.trough = raw
        if raw > self.threshold and raw > self.peak:
            self.peak = raw

        if elapsed > 250:
            if (raw > self.threshold and not self.pulse
                    and elapsed > (self.ibi // 5) * 3):
                self.pulse = True
                self.ibi = self.sample_counter - self.last_beat
                self.last_beat = self.sample_counter
                if self.second_beat:
                    self.second_beat = False
                    self.rates = [self.ibi] * 10
                if self.first_beat:
                    self.first_beat, self.second_beat = False, True
                    return
                self.rates = self.rates[1:] + [self.ibi]
                # runningTotal is uint16_t in the C++ implementation.
                average = (sum(self.rates) % 65536) // 10
                self.bpm = 60000 // average
                self.events.append((wall_ms, self.bpm, self.ibi))

        if raw < self.threshold and self.pulse:
            self.pulse = False
            self.amplitude = self.peak - self.trough
            self.threshold = self.amplitude // 2 + self.trough
            self.peak = self.trough = self.threshold

        if elapsed > 2500:
            self.threshold = self.peak = self.trough = self.timeout_midpoint
            self.last_beat = self.sample_counter
            self.first_beat, self.second_beat = True, False
            # The original timeout does NOT reset Pulse, invalidate BPM,
            # or set QS to deliver a signal-lost notification.
            self.timeouts.append(wall_ms)


def sine(t, period=600, amplitude=200):
    return round(2048 + amplitude * sin(2 * pi * t / period))


def fading_pulse(t):
    if t < 6000:
        return sine(t)
    amplitude = max(0, 200 * (1 - (t - 6000) / 3000))
    return sine(t, amplitude=amplitude) + sine(t, 1000 / 60, 15) - 2048


def run(name, signal, step_ms=2, timeout_midpoint=512):
    detector = Detector(timeout_midpoint)
    for t in range(step_ms, 20001, step_ms):
        detector.sample(signal(t), t)
    print(name)
    print("  Last five BPM:", [event[1] for event in detector.events[-5:]])
    print("  Reported beats:", len(detector.events),
          "Timeouts:", len(detector.timeouts))
    return detector


def main():
    clean = run("Clean 100 BPM pulse", sine)
    noise = run("60 Hz noise only, +/-15 ADC counts",
                lambda t: sine(t, 1000 / 60, 15))
    fade = run("100 BPM pulse fades over 3 s into +/-15-count noise",
               fading_pulse)
    print("  BPM during transition:",
          [event[1] for event in fade.events if 5500 <= event[0] <= 14000])

    def recovery_signal(t):
        return 1900 if t < 4000 else sine(t)

    broken_recovery = run("Flat signal then pulse; current 512 reset",
                          recovery_signal)
    restored_recovery = run("Same input; change ONLY reset midpoint to 2048",
                            recovery_signal, timeout_midpoint=2048)
    abrupt_loss = run("100 BPM pulse abruptly replaced by small noise",
                      lambda t: sine(t) if t < 6000
                      else sine(t, 1000 / 60, 15))
    slow_timer = run("100 BPM pulse; simulated callback every 4 ms",
                     sine, step_ms=4)

    # Sanity checks on the experiment outcomes, not firmware test coverage.
    assert len(clean.events) > 5
    assert all(event[1] == 100 for event in clean.events[-5:])
    for detector in (noise, fade):
        assert len(detector.events) > 5
        assert all(230 <= event[1] <= 238 for event in detector.events[-5:])
    assert broken_recovery.timeouts and not broken_recovery.events
    assert len(restored_recovery.events) > 5
    assert all(event[1] == 100 for event in restored_recovery.events[-5:])
    assert abrupt_loss.timeouts and abrupt_loss.events[-1][0] < 7000
    assert len(slow_timer.events) > 5
    assert all(event[1] == 200 for event in slow_timer.events[-5:])
    print("All behavioral-model checks passed. Hardware cause remains unverified.")


if __name__ == "__main__":
    main()
