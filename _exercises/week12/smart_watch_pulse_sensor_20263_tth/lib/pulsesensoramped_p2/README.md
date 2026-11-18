# pulsesensoramped_p2

PulseSensor Amped support for Particle Photon 2 / P2, by Rob Parke, based on
Bill Siever's PulseSensorAmped port.

## Usage

See `examples/basic_hr.cpp`. Attach the signal pin, call `start()` in `setup()`,
and call `process()` regularly from `loop()` to deliver callbacks.

```cpp
#include <PulseSensorAmped.h>
PulseSensor PulseSensorAmped;

// In setup():
// PulseSensorAmped.attach(A1);
// PulseSensorAmped.start();

// In loop():
// PulseSensorAmped.process();
```

Define either optional callback as needed:

```cpp
void PulseSensorAmped_data(int BPM, int IBI) {
    // BPM averages ten intervals; IBI is the latest interval in milliseconds.
}
void PulseSensorAmped_lost() {
    // No qualifying beat for 2.5 seconds, or a sampling gap over 20 ms.
}
```

## Signal quality and diagnostics

Version 0.0.2 filters the raw ADC signal, applies hysteresis, and requires a
minimum filtered amplitude of 60 ADC counts (on the 0-4095 scale). Adjust with
`setMinimumAmplitude(counts)` only after checking the waveform. The algorithm
retains its original 250 ms beat guard; it does not clamp BPM to a resting range.

`getDiagnostics()` returns the latest raw and filtered samples, threshold,
filtered peak-to-peak swing, sample count, maximum sampling gap, and tracking
state. Reading diagnostics resets the reporting-window counters. Tracking is
a detector state, not a guarantee that each detected beat is correct.

The library prints no debug output. User callbacks run on the application
thread when `process()` is called. Do not add serial output inside the timer
callback. A sustained weak or noisy signal may require sensor or wiring changes.

## Release

See `CHANGELOG.md`. From this library directory, use:

```sh
particle library upload
particle library publish pulsesensoramped_p2
```

For cloud builds, pin the published version in the application project:

```properties
dependencies.pulsesensoramped_p2=0.0.2
```

Local vendored copies must contain the same version. Preserve the included
MIT license when redistributing the library.
