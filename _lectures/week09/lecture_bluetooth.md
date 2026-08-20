---
marp: true
theme: itp

week: 9
order: 4
category: lectures
title: Bluetooth
---

<!-- headingDivider: 2 -->

# Bluetooth

 <img src="lecture_bluetooth.assets/5213ccb1757b7f4c568b4568.jpg" alt="https://cdn.sparkfun.com/assets/4/b/e/e/9/5213ccb1757b7f4c568b4568.jpg" style="width:500px" /> 

## What is Bluetooth?

 

## Review: Communication 

- WiFi and Cellular
- Bluetooth Low Energy (BLE)
  - Ex: Communication between smart watch and phone; wireless headphones
  - Range: ~1200+ ft
- Near-Field Communication (NFC) 
  - Ex: Contact-less payment like Apple Pay
  - Range: 4 inches

## Bluetooth

* Set of protocols / standards for communicating wirelessly on 2.4 GHz frequency (same as WiFi)
* Ubiquitous: uses include headphones, game controller, stylus, keyboard / mouse, speakers, mobile phones
* We will focus on Bluetooth Low Energy (BLE)
  * Subset of Bluetooth that is low-cost, low power
  * Also called "Bluetooth 4.0" or "Bluetooth Smart"

## Fun Fact!

<img src="lecture_bluetooth.assets/5213ccb1757b7f4c568b4568.jpg" alt="https://cdn.sparkfun.com/assets/4/b/e/e/9/5213ccb1757b7f4c568b4568.jpg" style="width:200px" /> 

* Bluetooth is named for **Harald Bluetooth**, a 10th Scandanavian king who unified parts of Denmark and Norway
* Bluetooth logo is a combination of his initials
  *   [<img src="lecture_bluetooth.assets/8px-Runic_letter_ior.svg.png" alt="Runic letter ior.svg" style="width:30px" />](https://en.wikipedia.org/wiki/File:Runic_letter_ior.svg) (Hagall) and [<img src="lecture_bluetooth.assets/8px-Runic_letter_berkanan.svg.png" alt="Runic letter berkanan.svg" style="width:30px;" />](https://en.wikipedia.org/wiki/File:Runic_letter_berkanan.svg) (Bjarkan)

## Device Roles

* Each device has a **General Access Profile** (GAP) which defines how it operates in relation to other devices
* **Central** devices typically have more computing power and battery life such as phones and computers
* **Peripheral** devices are lower cost and lower power such as a heart rate sensor or microcontroller like Photon 2

## Example: Device Roles

1. Single mobile phone triggers LEDs or motor connected to Photon 2
   * Phone is **central** and Photon 2 is **peripheral**
   * Phone can connect to multiple peripherals
   * This is how we will use BLE

<img src="lecture_bluetooth.assets/central_peripheral.png" alt="central_peripheral" style="width:1000px" />

## Example: Device Roles

2. Broadcast messages to many phones when people enter a concert
   * Many phone are **central** and Photon 2 is **peripheral**

<img src="lecture_bluetooth.assets/peripheral.png" alt="peripheral" style="width:750px" />

## Example: Device Roles

3. Using Photon 2 to read signal from Bluetooth heartrate sensor
   * Photon 2 is **central** and sensor is **peripheral** 

4. Using Photon 2 to communicate with another Photon 2 over Bluetooth

   * Photon 2 is designated **central** and the other is **peripheral**
   * This is how **mesh** networking works

## Advertising

 <img src="lecture_bluetooth.assets/8228.AdvertiseScan.PNG" alt="image description" style="width:1150px" /> 

* Peripheral devices broadcast messages announcing their presence and what services they support
* Intervals are 20 ms to 10 s

## Connecting to Peripherals

* Connection between central and peripheral devices is managed through a **General Attribute Profile** (GATT)
* Devices advertise **Services** and **Characteristics**
* **Services** are collections of related objects called characteristics that describe a device functionality
* **Characteristics** are specific values for data from the device
* Each is identified by either a 16 bit or 128 bit UUID (unique ID)

## Sample Services

* Glucose monitoring
* Health thermometer
* Heart rate
* Pulse oximter
* Weight scale

## Sample Characteristics

* Last name
* Longitude
* Rainfall
* Resting heart rate
* Glucose measurement

## Specific Example

* **Service**: Health thermometer (ID: 6153 or  0x1809)
  * Used for communication of temperature value from sensor
* **Characteristics**: Temperature measurement (ID:10870 or 0x2A1C)
  * Temperature (actual temperature)
  * Temperature type (e.g. mouth, armpit, ear, etc.)
  * Interval (time between reading)


## Making the Connection

  *  Photon 2
     *  Use as central device to connect to sensors and other Photon 2s
     *  Use as peripheral device to receive connections from mobile devices

<img src="lecture_bluetooth.assets/Screenshot 2024-06-21 at 11.24.57 PM.png" alt="Screenshot 2024-06-21 at 11.24.57 PM" style="width:700px" />

## Connecting with Mobile Apps

* There are many great resources and tools online to create iOS and Androids to communicate over BLE

* This is definitely the best option for a commercial product

## Making the Connection: Custom Mobile Apps 

<img src="lecture_bluetooth.assets/ember.png" alt="ember" style="width:300px;" /> <img src="lecture_bluetooth.assets/iosbluetooth.png" alt="iosbluetooth" style="width:300px;" />


## Connecting with Mobile Apps

* Building a mobile app is beyond the scope of this class, but we can use free testing apps to explore BLE functionality

## Adafruit Bluefruit

|                                                              |                                                              |
| ------------------------------------------------------------ | :----------------------------------------------------------- |
| <img src="lecture_bluetooth.assets/bluefruit.png" alt="Adafruit Bluefruit" style="width:450px;" /> | [Adafruit Bluefruit](https://learn.adafruit.com/bluefruit-le-connect) <br />Receive and graph sensor data <br /><br />Send pre-defined commands over UART (button press and release) <br /><br />Color picker |

## Nordic nRF Toolbox

|                                                              |                                                              |
| ------------------------------------------------------------ | :----------------------------------------------------------- |
| <img src="lecture_bluetooth.assets/nrftoolbox.png" alt="nRFToolbox" style="width:400px;" /> | [Nordic nRF Toolbox](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Toolbox)  <br />Test specific BLE services such as temperature and glucose monitor<br /><br />Send arbitrary string commands over UART (button press only; not press and release) |





<!--Diagnostic issue with nRF toolbox
Sometimes the Photon 2 doesn't properly disconnect from app. When app is then opened (iOS), it crashes. One fix is to exit nRF Toolbox, open Bluefruit app and connect / then disconnect from Photon 2. Then open nRF toolbox again
-->


## References

* [Adafruit Bluefruit Guide](https://learn.adafruit.com/bluefruit-le-connect/controller)
* [List of Official Bluetooth Services](https://www.bluetooth.com/specifications/gatt/services/)
* [List of Official Bluetooth Characteristics](https://www.bluetooth.com/specifications/gatt/characteristics/)

## Credits

* [Sparkfun](https://learn.sparkfun.com/tutorials/bluetooth-basics/all)
* [Bluetooth](https://en.wikipedia.org/wiki/Bluetooth)
* [Nordic Semiconductor](https://devzone.nordicsemi.com/nordic/nordic-blog/b/blog/posts/bluetooth-smart-and-the-nordics-softdevices-part-1)

* Images created with [Fritzing](https://fritzing.org/home/)
