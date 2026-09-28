---
marp: true
theme: tac

week: 2
category: lectures
title: Serial Monitor

---

<!-- headingDivider: 2 -->

# Serial Monitor

## Goal

* Be able to use receive status messages and program state information from Photon 2
* Use Serial Monitor to debug programs
    - This will be similar to `print` statements in other languages

## Serial

![photon2-rendering](lecture_serial_monitor.assets/photon2-rendering.png)

## Serial (UART)

* When the Photon 2 is connected via USB to your computer, it is sending and receiving data
* UART (Universal Asynchronous Receiver/Transmitter) is a chip on the Photon 2 that allows for serial communication
* The **RX** and **TX** are the same as (connected to) the USB pins

## Starting Serial Monitor

```c++
void setup() {
    Serial.begin(9600);
}
```

* Initialize the `Serial` object within`setup()`
* **9600** is the speed that the communication happens
  - 9600 bits per second (or "baud" rate)
* We will always use **9600** 
  - Some devices like GPS will need to communicate at a faster rate

## Using Serial Monitor

```c++
void loop() {
    Serial.println("Hello World!");
    Serial.println("Everything is awesome!");
```

##### Output

`Hello World!`

`Everything is awesome!`

## Using Serial Monitor

```c++
void loop() {
    Serial.print("Hello World!");
    Serial.println("Everything is awesome!");
```

##### Output

`Hello World!Everything is awesome!`

## Using Serial Monitor with Variables

```c++
void loop() {
    int x = 4;
    Serial.println(x);
    Serial.println("The value is " + x);
```

##### Output

`4`

`ERROR`  **println()** can only take one type of input at a time

## Question

- How do we get the following output?

`The value is 4 and it is an integer`

## Using Serial Monitor with Variables

```c++
//Solution 1
void loop() {
    int x = 4;
    Serial.print("The value is ");
    Serial.print(x);
    Serial.println(" and it is an integer");
```

##### Output

`The value is 4 and it is an integer`

* This combines `print()` and `println()`

## Using Serial Monitor with Variables

```c++
//Solution 2
void loop() {
    int x = 4;
    Serial.println("The value is " + String(x) + "and it is an integer");
```

##### Output

`The value is 4 and it is an integer`

* This the `String` object constructor to convert an int to a String
    - There is a `String` object in C++ just like other languages

## Opening Serial Monitor in Workbench

- Open Serial Monitor in Workbench
  - View > Command Palette > 'Serial Monitor'

<img src="lecture_serial_monitor.assets/1565664078373.png" alt="width:300px" style="width:300px" />

## How we will use Serial Monitor

* Serial Monitor allows us to debug our programs (just like print statements in other languages)
* We can see the state of variables, what functions are being called, etc.

## Special Notes about Serial Monitor

* Serial Monitor is **only** available while the Photon 2 is connected to your computer via USB

* Technically the Photon 2 also supports **sending** data to the Photon 2 via Serial Monitor (e.g. sending integer values)
  - This isn't supported in Workbench so we won't use it
  <!-- - For more information, see https://docs.particle.io/reference/device-os/firmware/argon/#read- -->