---
marp: true
theme: itp

week: 9
order: 3
category: lectures
title: LiPo Battery
---

<!-- headingDivider: 2 -->

# LiPo Battery

## Power Untethered

* Photon 2 needs 3.3v to function
* DC hobby motors require 1-3v, but will handle up to 12v
* Best solution is to use LiPo battery which operates at 3.7v

## Lithium-Ion Polymer Battery (LiPo)

<img src="lecture_lithium_ion_battery.assets/1572470513438.png" alt="1572470513438" style="width:800px" />

## Lithium-Ion Polymer Battery (LiPo)

* Operates at 3.7v (many other voltages available)
* Rechargeable
* Has a standard 2-pin JST-PH connector (also on Photon 2)
* Lightweight

## LiPo Capacity

* Besides voltage, batteries have a **capacity** rating
* **Capacity** is measured in **Amp hours**
* **Amp hours** are *"amount of current the battery can supply for an hour before it is drained"*
* Our batteries are **1800 mAh**
  * 1800 milliamp hours = 1.8 Amp hours
* Increased capacity --> increased size --> increased cost

## LiPo Special Cautions

* LiPo (like batteries in your cell phone) are generally safe
* However, please follow a few cautions:
  * Only charge with LiPo charger
  * Do not expose battery to water
  * Do not puncture
  * If punctured or swells, **stop using immediately**
  * Please **please** do not throw battery in the trash--it contains toxic metals that pollute the environment
  * You can drop the battery off at a [recycling center in your area](https://earth911.com/) or at a [  ](https://www.homedepot.com/c/ab/how-to-dispose-of-batteries/9ba683603be9fa5395fab90124a115f1)

## LiPo and Photon 2

<img src="lecture_lithium_ion_battery.assets/1572471470052.png" alt="1572471470052" style="width:200px;" />

* Photon 2 has built-in charging port for LiPo batteries
* Connect Photon 2 to USB in order to charge battery

## New Photon 2 Pins

<img src="lecture_lithium_ion_battery.assets/Screenshot 2024-06-03 at 1.49.08 PM.png" alt="Screenshot 2024-06-03 at 1.49.08 PM" style="width:700px;" />

* `EN` is a basically **on/off** for the Photon 2. Connect to **GND** to turn off Photon 2 (and save battery power)
* `Li+` is internally-connected to the positive (+3.7v) of the battery





## References

* [Sparkfun](https://www.sparkfun.com/products/13853)
* [Particle](https://docs.particle.io/reference/datasheets/wi-fi/photon-2-datasheet/)

* Images created with [Fritzing](https://fritzing.org/home/)
