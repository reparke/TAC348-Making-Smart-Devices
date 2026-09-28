---
marp: true
theme: tac

category: reference
title:  (Reference) MAX30101 Heart Rate Sensor
show_in_list: true

---
<!-- headingDivider: 2 -->



# Heart Rate Sensor

<img src="heart_rate_sensor.assets/MAX30101.jpg" alt="image-20200416155711370" style="width:500px" />

## Wiring

<img src="heart_rate_sensor.assets/oled_i2c_bb.png" style="width:900px;" />

## Wiring - Qwiic Cable

<img src="heart_rate_sensor.assets/qwiic_cable.jpg" style="width:300px;" />

## 
<span style="font-size:75%">



| OLED         | Argon | Purpose | Notes                 |
| ------------ | ----- | ------- | --------------------- |
| GND          | GND   | Ground  | Ground                |
| 3V3          | 3V3   | Power   | 3.3v                  |
| SDA (Blue)   | SDA   | Data    | Serial data           |
| SCL (Yellow) | SCL   | Clock   | Synchronization clock |

</span>

## Operation

### Library

* We need a library to handle much of the complex communication with the heart rate sensor
* To install a library, go to the command palette and type `Install Library`
* Install the heart rate sensorlibrary: `SparkFun-MAX3010x`

### Examples

- There are extensive examples in the library folder under `lib/examples`

  



## Credits

- [Sparkfun](https://www.sparkfun.com/products/16474)