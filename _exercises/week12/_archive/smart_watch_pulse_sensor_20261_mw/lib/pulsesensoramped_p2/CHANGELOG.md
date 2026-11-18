# Changelog

## 0.0.2 — 2026-11-16

- Filter the ADC signal and reject small fluctuations with a configurable
  minimum amplitude and hysteresis.
- Measure beat intervals using actual elapsed time; skip timer callback bursts
  and reacquire after sampling gaps.
- Reset detector state consistently for the 12-bit ADC and deliver the
  signal-lost callback once per loss episode.
- Synchronize timer and application access; invoke user callbacks outside the
  state lock and tolerate omitted optional callbacks.
- Add opt-in diagnostics. The library itself does not print debug output.

The existing `attach()`, `start()`, `process()`, and callback interface is
preserved. The minimum filtered pulse amplitude defaults to 60 ADC counts.

## 0.0.1

Initial Photon 2 port.
