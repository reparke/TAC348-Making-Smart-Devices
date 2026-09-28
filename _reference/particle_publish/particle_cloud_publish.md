---
marp: true
theme: tac

category: reference
title: (Reference) Particle Publish
show_in_list: true

---

<!-- headingDivider: 2 -->

# `Particle.publish`
## Operation

* Events are messages sent from an Photon 2 to the cloud **as often as you choose**
* Events can be accessed in [Particle console]([https://console.particle.io/](https://console.particle.io/)), app, or by other devices (subscribing)

### Viewing Events in Particle Console

<img src="particle_cloud_publish.assets/1569446342143.png" alt="1569446342143" style="width:800px;" />



## Code

### Syntax

```c++
Particle.publish(<<EVENT_NAME>>, <<EVENT_VALUE>>); 
```

### Example

```c++
Particle.publish("lightValue", "bright"); 
Particle.publish("tempFahr", String(85.9));
```

* Names and values must always be strings
* Should only publish 1 event / sec (or burst of 4 events in 1 sec)

## Documentation

* [Particle Cloud API](https://docs.particle.io/reference/device-os/firmware/#cloud-functions)
* [Publishing Events](https://docs.particle.io/reference/device-os/firmware/#particle-publish-)
