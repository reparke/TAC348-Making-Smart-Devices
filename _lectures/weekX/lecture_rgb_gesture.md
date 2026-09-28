---
marp: true
theme: tac

week: 16
category: lectures
title: RGB and Gesture Sensor
---

<!-- headingDivider: 2 -->

# RGB and Gesture Sensor



<img src="lecture_rgb_gesture.assets/image-20200430160841732.png" alt="image-20200430160841732" style="width:500px;" />

*This content is incomplete but provides some code examples to get started using RFID*

*Class sensor may be a different color (purple)*

## RGB and Gesture Sensor 

* Uses APDS-9960 sensor 
* Measures ambient light 
* Measure color
* Supports proximity detection
* Allows for gesture recogition

## Sensor

* Sensor communicates with Argon using **I2C**

* Operates at 3.3v

## Sensor Wiring

| Sensor | Argon |
| ------ | ----- |
| VCC    | 3.3v  |
| GND    | GND   |
| SDA    | SDA   |
| SCL    | SCL   |
| INT    | -     |

## RFID Library

  * `SparkFun_APDS9960` is an Argon compatible library
  * `Wire` may also need to be included

## Sample Code

* The following code is adapted from the library example
* Supports swiping gestures by moving hand over sensor for tracking or identification

## Sample Code

```c++

#include <SparkFun_APDS9960.h>
#include <Wire.h>

SparkFun_APDS9960 apds = SparkFun_APDS9960();

void setup() {
  Serial.begin(9600);
  // Initialize APDS-9960 (configure I2C and initial values)
  if (apds.init()) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if (apds.enableGestureSensor(true)) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
}

void loop() {
	if (apds.isGestureAvailable()) {
        handleGesture();
	}
    delay(500);
}

void handleGesture() {
  if (apds.isGestureAvailable()) {
    switch (apds.readGesture()) {
      case DIR_UP:
        Serial.println("UP");
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
}
```



## Example Links to Products

* Sensor: [Amazon](https://www.amazon.com/gp/product/B01NACU412/)

## Credit

* [Sparkfun](https://www.sparkfun.com/products/12787)





























