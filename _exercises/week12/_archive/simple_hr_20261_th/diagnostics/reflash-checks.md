**Testing the revised pulse sensor firmware**

The current acquisition experiment uses the modified local library. Its
published dependency line in `project.properties` is temporarily commented
out so cloud builds also compile this copy. No new library version has been
published for this experiment.

Compile and flash this project using the existing Photon 2 / Device OS 6.4.1
settings. The signal pin is still A1. Open Serial Monitor at the existing
9600 setting, hold the sensor steady, and collect about 20 seconds of output.
There is no startup wait for the serial connection, so the initial banner may
appear before the monitor opens.

You will see the existing `BPM` / `IBI` lines plus a diagnostic line each second:

```text
RAW:... FILTERED:... PP:... THRESH:... MIN_AMP:60 SAMPLES_PER_SEC:... MAX_GAP_MS:... STATE:...
```

- `RAW` is the latest ADC sample; `FILTERED` is its smoothed value.
- `PP` is the filtered peak-to-peak swing over the reporting window. It helps
  judge signal strength; it does not prove the waveform contains real pulses.
- `MIN_AMP` is the minimum peak-to-trough swing required by the beat detector.
  It starts at 60 ADC counts out of 4095. This is a trial sensitivity setting,
  not a calibration based on a recording from this sensor.
- `THRESH` is the adaptive center threshold; a 10-count margin on each side
  helps prevent small fluctuations from repeatedly toggling the pulse state.
- `SAMPLES_PER_SEC` should be around 500 under regular scheduling. Short bursts
  of callbacks are skipped rather than assigned invented timestamps.
- `MAX_GAP_MS` reports the longest sampling interval in that window. A gap
  above 20 ms invalidates tracking and starts reacquisition.
- `STATE:tracking` means the detector has acquired intervals. It is not a
  guarantee that every detected beat is correct. `acquiring` means it is
  waiting for three consecutive measured intervals with a range no greater
  than 25% of their mean before calculating the first new rate.

After 2.5 seconds without a qualifying beat, or after a sampling gap, expect
`Pulse Lost: ...; reacquiring`. The notification occurs once per loss episode,
including an initial failure to acquire. Once pulses return, the rate history
is seeded from the three consistent intervals rather than from the first
possibly unsettled interval. At 90 BPM, this takes about two seconds after the
first detected beat once intervals are consistent. Irregular acquisition takes
longer. This is not a general finger-presence detector or a guarantee against
missed beats once tracking has begun.

The revised code uses two gentle low-pass stages, elapsed-time interval
measurement, a minimum amplitude gate, and hysteresis. It keeps the original
250 ms beat guard, so the displayed rate is not capped to a resting range.
Raw samples are read only by the sensor library; serial output runs in the
application loop after releasing its shared-state lock.

The normal setting is diagnostics disabled. For the current no-finger capture,
this sample temporarily sets `printPulseDiagnostics = true` so Workbench's
read-only serial monitor can show diagnostics without sending input. Restore
`false` after the capture. With a two-way terminal such as PuTTY or CoolTerm,
send `d` (or `D`) to toggle diagnostics. Toggling resets the reporting window
so old samples are not included in the next line.
Keep `minimumPulseAmplitude = 60` for an initial comparison. If it stays in
`acquiring`, preserve the diagnostic output before changing sensitivity.
Very low `PP` and large sampling gaps call for different fixes. After checking
signal quality, the minimum amplitude can be tuned in that file; setting it
too high rejects useful weak pulses, while setting it too low admits noise.

**No-finger investigation**

`PulseSensorAmped_lost()` reports absence of accepted beats; it is not a direct
finger-presence measurement. In 0.0.2, every accepted crossing resets the
2.5-second timer. Strong enough interference can therefore keep BPM output
running with no finger and prevent the callback. A deterministic synthetic
experiment with a clean 100-BPM pulse followed by strong random ADC noise
produced 69 false detections over 20 seconds and no loss notification. This
demonstrates the limitation, not the physical source of this sensor's noise.

To choose a signal-quality rule without sacrificing the working pulse reading,
capture about 20 seconds with the sensor off the finger, then 10–20 seconds
with it on the finger. Include both `BPM`/`IBI` and diagnostic lines. Do not
interpret `STATE:tracking` as proof of finger contact, and do not just shorten
the timeout: recurring false detections can also reset a shorter timeout.

**Validation**

All 18 host scenarios pass, including stable 50 and 90 BPM, withholding BPM
after a single long interval, and acquisition through the unsettled intervals
from `scratch/results.txt`. That last case generates synthetic optical pulses
with the logged timing; the log does not contain a full raw waveform for replay.
Hardware validation of the acquisition change is still pending.
The sample's Photon 2 cloud build passed on Device OS 6.4.1 with the modified
local library and no published-library dependency overriding it.

The host checks compile and execute the actual modified library C++, with fake
ADC samples, a controllable clock, and a timer substitute. They cover clean
40/50/60/90/100/180/230 BPM, rejection of small 50/60 Hz noise, 100 BPM with added
60 Hz interference, fading signal, timeout recovery, 4 ms callbacks, callback
bursts and gaps, clock rollover, and diagnostic snapshots. They also access
diagnostics from user callbacks to verify callbacks run without the state lock.
They do not emulate Particle's scheduler or the physical sensor.

On a machine with a native C++17 compiler, run from the project directory:

```sh
c++ -std=c++17 -Wall -Wextra -Werror -pthread \
  -Idiagnostics/host -Ilib/pulsesensoramped_p2/src \
  diagnostics/host/detector_test.cpp \
  lib/pulsesensoramped_p2/src/PulseSensorAmped.cpp \
  -o /tmp/pulse-detector-test
/tmp/pulse-detector-test
```

`diagnostics/host/Particle.h` is exclusively a host-test substitute; do not add
that include directory to the firmware build. The older Python simulation is
retained as a reproduction of the pre-fix failure, not a test of this firmware.
