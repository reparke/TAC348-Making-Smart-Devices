---
marp: true
theme: itp

week: 14
category: lectures
title: Accelerometer
---


<!-- headingDivider: 2 -->

# Accelerometers

<img src="lecture_accelerometer.assets/13926-02.jpg" alt="1574364327550" style="width:600px;" />



## Accelerometer

* Measures acceleration
  * Movement
  * Gravity 

* Model: MMA8452Q 

* Measurement range:  ±2g/±4g/±8g 
  * g = 9.8 m/s<sup>2<sup> (Earth's gravity)
* Uses I2C serial protocol

## Uses

* Tilting sensing
* Orientation detection (e.g. smart phone)
* Vibration sensing
* Motion (e.g. Wiimote)
  * Free fall

## Measurement

* Measures acceleration in X, Y, Z direction
* At least one direction will be to acceleration due to gravity at any given time. This is how the sensor "knows" what orientation it is in

<img src="lecture_accelerometer.assets/1574737572993.png" alt="1574737572993" style="width:400px;" />

## Related Sensors

* It can be confusing because there are multiple types of sensors that perform similar functions
* Other types of sensors are **gyroscopes** and **inertial measuring units**

## Gyroscopes

<img src="lecture_accelerometer.assets/1574737698474.png" alt="1574737698474" style="width:600px;" />

* Measure rotation in X, Y, Z (pitch, roll, yaw)
* Useful for flight guidance and autonomous vehicles

## IMU (inertial measurement unit)

<img src="lecture_accelerometer.assets/1574737956962.png" alt="1574737956962" style="width:300px;" />

* Combine accelerometer and gyroscope
* Detailed measurement of orientation, position, and velocity
* Provides up to nine degrees of freedom
* Useful for robotics

## Sensor Wiring

| Sensor | Argon | Function                        |
| ------ | ----- | ------------------------------- |
| GND    | GND   | Ground                          |
| VCC    | 3V3   | Power (requires 3.3v)           |
| SDA    | SDA   | I2C data (no resistors needed)  |
| SCL    | SCL   | I2C clock (no resistors needed) |

## Sensor Wiring

<img src="lecture_accelerometer.assets/accelerometer_bb.png" style="width:800px;" />

## `SparkFunMMA8452Q` Library

* Initialize accelerometer object

```c++
MMA8452Q accel; 		//accelerometer object

void setup() {
  accel.begin(<<SCALE>>, <<RATE>>); //initialize object
```

* `<<SCALE>>` specifies ±2g, ±4g, ±8g
* `<<RATE>>` specific update frequences in Hz
* Ex:
  * ` accel.begin(SCALE_2G, ODR_400)` measures **±2g** and updates at **400 Hz**

## Library Operations

```c++
if (accel.available()) {	//check if available
  accel.read();				//read sensor values
  float x = accel.cx;		//get X-dir measurement (in G's)  
  float y = accel.cy;		  
  float z = accel.cz;		  
```



## Library Operations

* Recommended library for Argon
  * ```SparkFunMMA8452Q```
* Check for vibrations
  * `accel.readTap()` greater than 0 is a vibration (*doesn't work with Argon library*)
* Check orientation
  * `accel.readPL()` returns int value relating to orientation of sensor



## Exercise 1

* Download starting code: Go to [https://bit.ly/ProjectZip](https://bit.ly/ProjectZip)
  * Paste the following link into the top right
    https://github.com/reparke/ITP348-Physical-Computing/tree/master/_exercises/week14/accelerometer_start
* Connect sensor and run example code

## Exercise 2

* Connect RGB LED
* Change LED colors based on orientation
* Then change LED colors based acceleration
* Then turn on LED if there is vibration

## Credit

- [Sparkfun](https://www.sparkfun.com/products/13926)
- [Sensor Datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Accelerometers/MMA8452Q-rev8.1.pdf)
- [Accelerometers, Gyros, IMUs](https://www.sparkfun.com/pages/accel_gyro_guide)
- Diagrams created with [Frizting](https://fritzing.org)

