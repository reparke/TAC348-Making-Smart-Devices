---
marp: true
theme: itp

category: reference
title: Powering 5V Devices from a Battery
show_in_list: true

---

<!-- headingDivider: 2 -->

# Powering 5V Devices from a Battery



## Problem

* Some devices such as servos and ultrasonic sensor require 5V to operate
* LiPo (lithium ion) batteries provide 3.7V so these devices might have enough power to operate correctly
* *Note: generally the ultrasonic sensor will function with 3.7V if device power is connected to `Li+` in*

## Solution #1 - Use 5V USB Battery

* Any USB battery pack (like you would use to connect to your phone) with a **USB A** (the older, larger flat type) connecter should work
* Connect the battery pack to the Photon 2's USB port and the Photon 2 will now have 5V
* Connect your 5V devices to `GND` and `VUSB` on the Photon 2
* Example: [Power Bank](https://www.amazon.com/INIU-Portable-10000mAh-Charging-External/dp/B0DCHWWBNS)

## Solution #2 - Use a Step-Up 5V Voltage Regulator

* A step-up voltage regulator will "step-up" (increase) the 3.3V (or 3.7V) from the Photon 2 to 5V
* Example 1: [Sparkfun Qwiic Boost](https://www.sparkfun.com/products/17238)
* Example 2: [Pololu 5V Step-Up Voltage Regulator](https://www.pololu.com/product/2564)
