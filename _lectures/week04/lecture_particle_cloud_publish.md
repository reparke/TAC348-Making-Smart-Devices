---
marp: true
theme: tac

week: 4
category: lectures
title: Cloud Communication - Publish
---

<!-- headingDivider: 2 -->

# Cloud Communication
<img src="lecture_particle_cloud_publish.assets/iot_cloud.jpg" alt="iot_cloud" style="width:800px;" />



## Events Part 1: Publishing Events

* Events are messages sent from a Photon 2 to the cloud **as often as you choose**
* Events are private (viewable by only by you and devices in your account) 
* Events can be accessed in [Particle console]([https://console.particle.io/](https://console.particle.io/)), app, or by other devices (subscribing)

## Events in Particle Console

<img src="lecture_particle_cloud_publish.assets/1569446342143.png" alt="1569446342143" style="width:800px;" />



## Publish Syntax

```c++
Particle.publish(<<EVENT_NAME>>, <<EVENT_VALUE>>); 
```

Example

```c++
Particle.publish("lightValue", "bright"); 
Particle.publish("tempFahr", String(85.9));
```

* Names and values must always be strings
* Should only publish 1 event / sec (or burst of 4 events in 1 sec)

<!-- public event were removed Aug 2020 -->

## Publishing on Device Startup

* With threading enabled,
  ```c++
  SYSTEM_THREAD(ENABLED);
  ```

  `setup()` will run before cloud connectivity is enabled, meaning `Particle.publish()` will fail

* If you need to execute code only once when the device starts, create a boolean flag and check to make sure the Photon 2 has connected to the cloud (`Particle.connected()`) before running the code once. 

* For example

  ```c++
  bool runOnce = true;
  
  void loop() {
    if (runOnce == true && Particle.connected() == true) {
      runOnce = false;
      // put Particle.publish(...) statement here
    }
  ```

  

* In order to get the weather initially when the Photon 2 turns on, we need to set a boolean flag and do a check in `loop()`

  * [Particle community post](https://community.particle.io/t/cant-particle-publish-in-setup-with-cpp-file/66688/3?u=rob7)



## Documentation

* [Particle Cloud API](https://docs.particle.io/reference/device-os/firmware/#cloud-functions)
* [Publishing Events](https://docs.particle.io/reference/device-os/firmware/#particle-publish-)
* [Cloud Variables](https://docs.particle.io/reference/device-os/firmware/#particle-variable-)
* [Cloud Functions](https://docs.particle.io/reference/device-os/firmware/#particle-function-)
* [Subscribing to Events](https://docs.particle.io/reference/device-os/firmware/#particle-subscribe-)
