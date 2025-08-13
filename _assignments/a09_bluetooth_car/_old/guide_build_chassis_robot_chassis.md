---
week: 9
category: assignments
title: Guide to Car Chassis Assembly
show_in_list: false
---

## TAC 348: Car Chassis Setup

Note: These instructions are deprecated because they use the old red robot chassis

## Items You will Need

1.  Screwdriver
2.  2 DC Gear Motors
3.  1 Ball Caster and 1 Hex Jam Nut
4.  4 Standoffs and 8 Small Screws
5.  Bottom and Top Plates with DC Motor Brackets
6.  2 Wheels and 2 Screws
7.  4 Long Screws and 4 Hex Jam Nuts

## Instructions

* Follow the steps in this guide to assemble the
* The following video can be helpful in assembling the chassis: [Two-Layer Chassis Assembly](https://youtu.be/L7-98Ejmb4M)
* The following 

<!--[Pictures of installation](https://learn.sparkfun.com/tutorials/assembly-guide-for-sparkfun-jetbot-ai-kit/1-circular-robotics-chassis-kit-two-layer-assembly) (only relevant through half of the first page)-->

![](guide_build_chassis_robot_chassis.assets/c7cbec04e8eb2bfc5708d466e2ac705d.png)



## Part 1: Building Chassis

### Step 1: Attach Caster

Screw the Ball Caster to the Bottom Plate

![](guide_build_chassis_robot_chassis.assets/d4885311ab7a43d46a3035689fcfd7f4.jpg)



### Step 2: Attach Standoffs

Screw on 3 of the Standoffs to the Bottom Plate using 6 of the screws.

*Top View*

![](guide_build_chassis_robot_chassis.assets/8c481584b3bbfe36d2092d0c39cca46c.jpg)

![](guide_build_chassis_robot_chassis.assets/da932b50dda027b65e1a2724b6f53415.jpg)

*Bottom View*

![](guide_build_chassis_robot_chassis.assets/dca82f235a741b1534f81c5ad4fe8dfe.jpg)



### Step 3: Attach Motor Brackets

Screw the DC Motor Brackets to the DC Motors using the Long Screws and Hex Nuts

![](guide_build_chassis_robot_chassis.assets/ca378b55e3a4180eeb95efdd73fafddd.jpg)

![](guide_build_chassis_robot_chassis.assets/17d3e93effc3c8ba7fa6a97362dd0eba.jpg)



### Step 4: Align Brackets

Align the Top Plate with DC Motor Brackets and Standoffs attached to the Bottom
Plate

![](guide_build_chassis_robot_chassis.assets/7a8d1f17a1c6233a8143f056c6b3f0bc.jpg)

![](guide_build_chassis_robot_chassis.assets/cd162a4e8f12a6a2e828e31dc17e1bd6.jpg)



### Step 5: Attach Top Plate

Screw the Top Plate to the standoffs.

*Note: Make sure DC Motor wires are on the inside of the chassis pointing
inwards not outward*

![](guide_build_chassis_robot_chassis.assets/b47bafe129f196ea279d7a423f365106.jpg)



### Step 6: Attach Wheels

Screw on Wheels to DC Motors and add the wheel rubber tires.

![](guide_build_chassis_robot_chassis.assets/75230dba370e9f156209643918d2aeea.jpg)

![](guide_build_chassis_robot_chassis.assets/555c117f7e3ac01c870d992c6e08c129.jpg)



## Part 2: Wiring

### Step 7: Attaching the Battery

* The battery can be attached to either the top or bottom of the chassis, but to avoid damaging it, it is recommended to attach the battery to the top of the chassis
* The breadboard can then be attached to the battery

<img src="guide_build_chassis_robot_chassis.assets/IMG_8467.JPG" style="400px" />
<img src="guide_build_chassis.assets/IMG_8468.JPG" alt="IMG_8468" style="width:400px" />

<img src="guide_build_chassis_robot_chassis.assets/car_lipo_hookup_no_wires_bb.png" style="width:500px;" />



*==Important: If you are working on another assignment concurrently, consider building the this project on a different breadboard==*

### Step 8: Build Circuit with Motor Controller


#### Motor Controller Wiring Guide

| Motor Controller | Photon 2 | --   | Motor Controller | Photon 2 |
| ---------------- | ----- | ---- | ---------------- | ----- |
| PWMA             | D8    |      | VCC              | 3v3   |
| AIN2             | D7    |      | GND              | GND   |
| AIN1             | D6    |      | VM               | Li+   |
| BIN1             | D5    |      | STBY             | 3v3   |
| BIN2             | D4    |      |                  |       |
| PWMB             | D3    |      |                  |       |

#### Wiring Diagram

* Note the diagram below uses two mini breadboard. This was because the diagram because the switch was move to keep the diagram readable.
* If you prefer, you use a single mini breadboard instead. You can do this by moving the switch onto the first breadboard between motor controller and the Photon 2

<img src="guide_build_chassis_robot_chassis.assets/1572472040619.png" style="width:1000px" />




## References

* [Sparkfun](https://www.sparkfun.com/products/13853)
* [Particle](https://docs.particle.io/reference/datasheets/wi-fi/photon-2-datasheet/)
