---
marp: true
theme: itp

week: 6
category: lectures
title: Creating IoT Mobile Apps with Blynk
---

<!-- headingDivider: 2 -->
<!-- new version -->
<!--NB: need to create a new template for each project; need to create datastream for each variable ahead of time; need to create device for each project-->

# Blynk Overview 

![bg opacity:.75](lecture_blynk_cloud.assets/blynk.jpg)
	 

## What is Blynk?

* Blynk is a "low code" platform for interacting with IoT products
* "No code" drag-and-drop, visual tool to build mobile apps
* Mobile apps can interact with, receive data from, and control IoT devices 
* You can develop add your own branding and package the app with your IoT device

## Blynk Functionality

- Data storage
- Display real-time sensor data and historical data
- Control IoT device from app
- Email / push notification when device is offline
- Custom webhooks

## Blynk Evaluation

| Advantages                                                   | Disadvantages                                    |
| ------------------------------------------------------------ | ------------------------------------------------ |
| Highly customizable                                          | Free version has limitations                     |
| Easier to integrate than other mobile dashboards (e.g. Losant) | Dashboard is limited (compared to Initial State) |
| Easy to design mobile app without coding                     | Requires modifying `loop()` logic                |

## Quick Blynk Definitions

- Template: store configuration settings for your project; need to create a new template for each project
- Device: represents your Photon 2
- Datastream: channels that send data between the device and Blynk; each variable you send needs separate datastream 
- Virtual Pins

## Virtual Pins

- Use **virtual pins** to send and receive data from Photon 2
- These are not real hardware pins, but just a concept used by Blynk
- Virtual pins support `ints` and `Strings` (unlike hardware pins) 
- 32-128 pins are supported (label `V0`, `V1`, etc.)
- Note: You **can not** use `const int` to define virtual pins. If you want to define pin label, use `#define VPIN_LED V2` syntax

# Blynk Integation

## Three Phases to Integrate Blynk

There are three places we need to configure to use Blynk

1. **Blynk Cloud website ([https://blynk.cloud](https://blynk.cloud))**
   This is where we configure the data that will be sent
2. **Workbench**
   This is where we write the Photon 2 code to send data
3. **Blynk mobile app** 
   This is where we will design the interface

## Integration Phase 1: Blynk Cloud

Blynk Cloud website ([https://blynk.cloud](https://blynk.cloud))

- Create template (new template for every new project)
- Create datastreams (one for each piece of data to be sent to cloud)
- Create device (this represents your Photon 2)
- Copy config info / key into Workbench Sketch

## Integration Phase 1: Create template

![image-20240212172351680](lecture_blynk_cloud.assets/image-20240212172351680.png)

![image-20210905203331216](lecture_blynk_cloud.assets/image-20210905203331216.png)



## Integration Phase 1: Create datastreams

<img src="lecture_blynk_cloud.assets/image-20210905212827674.png" alt="image-20210905212827674" style="width:500px" />



<img src="lecture_blynk_cloud.assets/image-20210905213011243.png" alt="image-20210905213011243" style="width:500px" />

Click **Save**

 

## Integration Phase 1: Create new device

<img src="lecture_blynk_cloud.assets/image-20240212172503798.png" alt="image-20240212172503798" width=200/>



<img src="lecture_blynk_cloud.assets/image-20210905214659317.png" alt="image-20210905214659317" style="width:400px;" />

<img src="lecture_blynk_cloud.assets/image-20210905214734120.png" alt="image-20210905214734120" style="width:400px;" />

## Integration Phase 1: Configuration Info / Key

Copy this info to include in sketch below (**Note: this is just an example--use the unique values for your template)**
<img src="lecture_blynk_cloud.assets/image-20210905215009623.png" alt="image-20210905215009623" style="width:400px" />

## Integration Phase 2: Workbench

- Create new sketch
- Install `blynk` library
- Modify sketch with Blynk configuration
- Add your unique custom info / keys from Blynk Cloud

## Integration Phase 2: Modify sketch with Blynk configuration

1. Copy the lines from the template to the top of your sketch:

```c++
#define BLYNK_TEMPLATE_ID "ADD_YOUR_OWN"
#define BLYNK_DEVICE_NAME "ADD_YOUR_OWN"
#define BLYNK_AUTH_TOKEN "ADD_YOUR_OWN"
```



2. Also add these lines beneath the template lines:

```c++
#include <blynk.h>
```


3. Add these line to the end of `setup()`

```c++
delay(5000);
Blynk.begin(BLYNK_AUTH_TOKEN);
```


4. Add this line to the top of `loop()`

```c++
Blynk.run();
```

After integration, your code should look something like the following

```c++
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#define BLYNK_TEMPLATE_ID "ADD_YOUR_OWN"
#define BLYNK_DEVICE_NAME "ADD_YOUR_OWN"
#define BLYNK_AUTH_TOKEN "ADD_YOUR_OWN"

#include <blynk.h>

void setup() {
  delay(5000);
  Blynk.begin(BLYNK_AUTH_TOKEN);
}

void loop() {
  Blynk.run();
}
```




## Integration Phase 3: Blynk App

- Install Blynk app on your phone
- Build interface in Blynk app

# Building Blynk Projects

## Important notes about `loop()`

- Do **not** use `delay()` in `loop()` or it will interfere with cloud connection

- Instead, use a `millis()` or a timer to send data to app (limit to 10 values per second)

## App: Send data from Blynk App to Photon 2

![width:500px](lecture_blynk_cloud.assets/blynk_8.png)![blynk lecture_blynk_cloud.assets/blynk_2.png) width:400px](lecture_blynk_cloud.assets/blynk_2.png)


## Syntax: Send data from Blynk App to Photon 2

- To send data FROM **app** TO **Photon 2**, create a `BLYNK_WRITE(vPin)` function 
- This event handler will be called automatically when the app changes

```c++
BLYNK_WRITE(<<VIRTUAL_PIN>>){
    //code
}
```

## Example: Send data from Blynk App to Photon 2

```c++
BLYNK_WRITE(V0){
  //assign incoming value from pin V0 to a variable
  int pinValue = param.asInt(); //or param.asStr() or .asDouble()
  Serial.println("V0 Slider value is: " + String(pinValue));
}
```

## Syntax: Send data from Photon 2 to Blynk App

- To send data from Photon 2 to Blynk App, use 

```c++
Blynk.virtualWrite(<<PIN>>, <<VALUE>>);
```

## Example: Send data from Photon 2 to Blynk App

```c++
unsigned long blynkDelay = 10000; //change this as needed

void loop() {
  unsigned long curMillis = millis();
  if (curMillis - prevMillis > blynkDelay) {
    double tempF = ...; //read a sensor
    Blynk.virtualWrite(V1, tempFermF);
    prevMillis = curMillis;
  }
 
  Blynk.run();
}
```

## App: Send data from Photon 2 to Blynk App

![blynk_4](lecture_blynk_cloud.assets/blynk_4.png)

## Wiring for Exercise and Lab

<img src="lecture_magnetic_switch.assets/Screenshot 2024-06-19 at 11.23.18 AM.png" alt="Screenshot 2024-06-19 at 11.23.18 AM" style="width:500px;"/>

## Exercise

* Connect RGB led and magnetic switch 
* Install Blynk app on your phone
* Create Blynk template
* Create Blynk datastream

    | Datastream Name     | Virtual Pin |
    | ------------------- | ----------- |
    | `Button Show Light` | `V5`        |
    | `Random Number`     | `V6`        |
    | `Door State`        | `V3`        |


- Build Blynk with the following features

  1. Use a display to show if magnetic switch is `open` or `closed` on pin `V3` *(Photon 2 --> app)*
  2. Send random number (0-255) to app and display on pin `V6` (Photon 2 --> app)
  3. Use virtual LED to show random number on pin `V6` (Photon 2 --> app)
  4. Use a gauge to show random number on pin `V6`  (Photon 2 --> app)
  5. Use button to control turn the RGB led to white via pin `V5` (app --> Photon 2)

## Exercise App Layout

<img src="lecture_blynk_cloud.assets/image-20210927175246789.png" alt="image-20210927175246789" style="width:300px" />

## Lab

* Work in teams and create the following functionality in Blynk app

* Create a new template and device in Blynk Cloud

  | Datastream                    | Virtual Pin |
  | ----------------------------- | ----------- |
  | `RGB Red`                     | `V0`        |
  | `RGB Green`                   | `V1`        |
  | `RGB Blue`                    | `V2`        |
  | `Button Display Random Color` | `V4`        |
  | `Displayed Color String`      | `V7`        |

  1. Use three sliders to control RGB LED on pins `V0 V1 V2` *(app --> Photon 2)*
  1. Use a button on `V4` to trigger the RGB LED to display a color randomly chosen from **white**, **yellow**, **magenta**, or **red** *(app --> Photon 2)*
  1. When one of the four random colors is displayed on the RGB LED, send a string representing that color to the app on pin `V7` *(Photon 2 --> app)*
  
* What happens if you put `Blynk.syncAll();` at the end of `setup()`? 

## Lab App Layout

<img src="lecture_blynk_cloud.assets/Screenshot 2024-02-12 at 5.42.52 PM.jpeg" alt="Screenshot 2024-02-12 at 5.42.52 PM" style="zoom: 33%;" />





## Resources

- [Blynk Documentation](https://docs.blynk.io/en/)

## Credit

* Image from [Blynk](https://blynk.io/)

