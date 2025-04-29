---
marp: true
theme: itp

category: reference
title: (Reference) RFID
show_in_list: true
---

<!-- headingDivider: 2 -->

# RFID - Radio Frequency ID 

<img src="rfid.assets/rfid_mfc522_sensor.jpg" style="width:600px;" />



## Wiring 

- Uses SPI communication protocol

| Sensor | Photon 2                       |
| ------ | ------------------------------ |
| 3.3v   | 3.3v                           |
| Reset  | A1 (or any digital output pin) |
| GND    | GND                            |
| IRQ    | -                              |
| MOSI   | MO                             |
| MISO   | MI                             |
| SCK    | SCK                            |
| SDA    | A0 (or any digital output pin) |

## Wiring Diagram

<img src="rfid.assets/Screenshot 2024-07-04 at 1.18.14 AM.png" alt="Screenshot 2024-07-04 at 1.18.14 AM" style="width:800px;" />



## Operation

### Library

* We need a library to handle much of the complex communication with the OLED 
* To install a library, go to the command palette and type `Install Library`
* Install the OLED library: `MFRC522`

### Examples

- There are extensive examples in the library folder under `lib/examples`

## Code

- See the in-class exercises and notes for more detailed examples

## Credit

* [Sparkfun](https://www.sparkfun.com/products/13285)























