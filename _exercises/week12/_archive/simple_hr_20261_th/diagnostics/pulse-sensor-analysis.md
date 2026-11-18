**Pulse sensor investigation — November 16, 2026**

This report describes the original code before the fixes. Its line numbers and
Python simulation refer to that original version. The revised firmware now uses
elapsed-time beat timing, filtering, amplitude rejection, hysteresis, working
loss notifications, and consistent timeout reset. See [reflash checks](reflash-checks.md)
for the current diagnostic output and C++ test instructions.

The leading explanation for the climb toward 230 BPM is false beat detection
as the useful pulse becomes weak relative to noise. A synthetic model reproduces
that behavior. This is evidence of a detector failure mode, not confirmation of
the signal or noise source on the physical sensor. A timing error is a second
possibility that needs a measurement.

The application reads **A1**, uses `pulsesensoramped_p2` 0.0.1, and targets **p2 /
Device OS 6.4.1** in `.vscode/settings.json`. The physical board and its installed
firmware have not been independently verified. Application and library files
were left unchanged; existing library differences from Git are line endings.

**Why this can produce 230 BPM**

In `lib/pulsesensoramped_p2/src/PulseSensorAmped.cpp`, lines 42–44 allow another
beat after more than 250 ms and roughly 60% of the previous interbeat interval.
A false short interval shortens that second guard for the following beat.
Once noise repeatedly crosses the threshold, it can be accepted as soon as
the guard expires.

At the assumed 2 ms sampling interval, the shortest accepted interval is
252 ms: `60000 / 252` gives about 238 BPM. A 260 ms interval gives about 231 BPM.
The detector can therefore report near 230 even when the interference itself
is much faster. [The sensor manufacturer's algorithm explanation](https://pulsesensor.com/pages/pulse-sensor-amped-arduino-v1dot1)
also describes the approximately 240-BPM ceiling.

Lines 72–89 average the last ten intervals. As false short intervals replace
the older intervals, the displayed BPM rises gradually. The latest printed
`IBI` and `60000 / BPM` need not match during that transition, because the former
is one interval and the latter reflects the average.

Lines 95–107 continually move the threshold to the midpoint of the observed
peak and trough. There is **no minimum signal amplitude or separate high/low
threshold pair** to reject small fluctuations. `amp = 410` in `start()` merely
initializes a variable; it does not impose a minimum amplitude. Changing the
initial `thresh = 2048` alone will not establish a lasting threshold, because
the algorithm overwrites it after detected pulses.

**Reproducible experiments**

Run `python3 diagnostics/simulate_detector.py`. This is a Python behavioral
model of the local algorithm, not a compiled C++ test or a hardware capture.
All inputs are synthetic; 60 Hz is an example interference frequency, not a
measurement of the user's setup.

| Synthetic input | Model result |
| --- | --- |
| Clean pulse every 600 ms | Stable 100 BPM |
| Only 60 Hz noise, +/-15 ADC counts around 2048 | 236–237 BPM |
| 100-BPM pulse fades over 3 seconds into that small noise | Gradual climb to 236–237 BPM |
| Flat signal for 4 seconds, then clean 100-BPM pulse | Current timeout logic fails to recover |
| Same recovery experiment, changing only reset midpoint to 2048 | Recovers to 100 BPM |
| Abrupt replacement of a strong pulse with small noise | Stops producing readings and repeatedly times out |
| Clean 100-BPM pulse, callbacks artificially delivered every 4 ms | Reports 200 BPM |

The fading experiment includes this sequence:
`100, 104, 110, 118, 123, 132, 143, 156, 171, 190, 212, 220, ... 236`.
The abrupt-loss experiment shows that different waveform transitions can also
produce silence; noise does not invariably cause a high reading.

**Definite library defects and timing concern**

- **Inconsistent timeout reset:** lines 110–117 reset `thresh`, `P`, and `T` to
  **512**, while startup uses **2048**. Particle's ADC returns 0–4095; 2048 is
  the midpoint of that range. A waveform remaining above 512 may never cross
  downward to clear `Pulse`, preventing recovery. Use a shared 12-bit midpoint
  for startup and reset, and reset the pulse state when reacquiring. This defect
  is established, but it does not by itself explain the persistent high BPM.
  [Particle ADC reference](https://docs.particle.io/reference/device-os/api/input-output/analogread-adc/)
- **Unreachable loss notification:** `process()` calls `PulseSensorAmped_lost()`
  only when `QS` is true and `BPM < 0`. Nothing assigns a negative BPM, and the
  timeout sets neither a loss event nor an invalid result. Absence of the
  `Pulse Lost` message therefore says nothing about signal quality. Moreover,
  false noise beats prevent the no-beat timeout from expiring at all.
- **Assumed clock:** lines 17–18 add exactly 2 ms per callback, but line 123
  creates a Particle software `Timer`, despite the hardware-ISR comments.
  Particle documents that callbacks share timer service execution and can be
  delayed. Sustained under-sampling could inflate BPM; ordinary jitter alone
  does not establish a twofold error. The installed 6.4.1 sources specify a
  1 kHz OS tick and pass the requested timer period through, so there is no
  evidence here of a fixed 4 ms platform minimum. Measure actual callback
  intervals before blaming the timer. A correction should timestamp actual
  samples and handle gaps without fabricating catch-up samples.
  [Particle software timers](https://docs.particle.io/reference/device-os/api/software-timers/software-timers/)

`delay(100)` in the application's loop delays delivery of the printed result;
the separate timer performs sampling. Reducing that delay alone does not repair
the detector. The header's A0/A1 warning describes an older hardware-timer
implementation; this code uses a software timer, and A1 is an ADC input on
Photon 2. Verify the signal wire is actually on A1 rather than changing pins
because of that old comment.

**Fastest next checks when the hardware is available**

1. Save 10–20 seconds of the existing `BPM` and `IBI` output, including the
   transition. Persistent intervals near 252–280 ms support the short-interval
   failure mode. Compare several seconds of output timing against the sum of
   those intervals; large disagreement warrants checking timer timing. Individual
   print times include up to about 100 ms of loop delay plus other scheduling
   delays, so they are not precise sample timestamps.
2. Capture the raw A1 waveform, detector threshold, and sample timestamps.
   Prefer exposing the samples already taken by the timer through a bounded
   buffer, then printing from `loop()`. Avoid printing from the timer callback
   or adding a second concurrent ADC reader. About 500 samples per second
   captures the intended sampling rate; record gaps and buffer overruns.
   A separate raw-only sketch is also useful for checking the optical signal,
   but does not test the current timer path.
3. Check whether the trace has clear recurring pulse peaks, small noise around
   a nearly flat baseline, extra peaks, or clipping near 0/4095. Verify signal
   to A1 and common ground. For a PulseSensor rated to run at 3.3 V, use the
   board's 3V3 supply; Photon 2's analog inputs are limited to 0–3.3 V. Sensor
   model and wiring remain unverified. [Particle ADC limits](https://docs.particle.io/reference/device-os/api/input-output/analogread-adc/)
4. Fix reset consistency and loss reporting, then use the trace to choose
   amplitude/noise rejection, hysteresis, or filtering. Simply capping BPM or
   extending the lockout until the number looks plausible can conceal false
   detection. [The manufacturer's getting-started guide](https://pulsesensor.com/pages/code-and-guide)
   recommends inspecting the raw pulse and tuning sensitivity.

No USB serial device was visible in this environment, and no compatible native
C++ compiler or Particle CLI was on PATH. Windows ARM toolchain files and
Device OS sources were readable, but no firmware build or flash was performed.
The remaining decisive evidence is a live waveform and measured sample timing.
