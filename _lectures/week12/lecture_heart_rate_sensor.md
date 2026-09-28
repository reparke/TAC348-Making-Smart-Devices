---
marp: true
theme: tac

week: 12
category: lectures
title: Heart Rate Sensor (Pulse Sensor Amped)
---

<!-- headingDivider: 2 -->



# Heart Rate Sensor

<img src="lecture_smart_watch.assets/smart_watch.gif" alt="smart_watch" style="width:500px;" />

## Detecting Heart Rate

<img src="lecture_heart_rate_sensor.assets/image-20221101172350013.png" alt="image-20221101172350013" width="400px;" />

## Pulse Sensor Amped

* Measure heart rate on finger
* Green light useful (like Apple Watch)

## Pulse Sensor Amped Wiring

| Sensor | Photon 2   | Function              |
| ------ | ---------- | --------------------- |
| GND    | GND        | Ground                |
| VCC    | 3V3        | Power (requires 3.3v) |
| Data   | Analog Pin | Data                  |


## Library

- From Workbench, install the library `PulseSensorAmped_P2`

## Configuration

```c++
#include <PulseSensorAmped.h>	//sensor library
const int PIN_PULSE = A0; // any analog pin
PulseSensor PulseSensorAmped; //create pulse sensor object

```

## Initialization

```c++
void setup() {
   analogRead(PIN_PULSE); // this is a workaround for a problem in the PulseSensorAmped library
    
   PulseSensorAmped.attach(PIN_PULSE);
   PulseSensorAmped.start();
  
```

### Note

- `analogRead` needs to be before the pulse sensor is initialized. This is a workaround to fix a problem in the library. For more information, see this [post](https://community.particle.io/t/pulse-sensor-amped-incompatible-with-os-5-3-0/64313/4)

## Sensor Readings

- The beats per minute can be read by adding the following function

```c++
void PulseSensorAmped_data(int BPM, int IBI) {
 // BPM will be the parameter that is the current Beats Per Minute
 // IBI will be the parameter that is the current Interbeat Interval
}

```



## Other Useful Methods

- The following function will be called when the signal is lost

```c++
void PulseSensorAmped_lost(void) {

}
```

## Credits

- [Sparkfun](https://www.sparkfun.com/products/16474)