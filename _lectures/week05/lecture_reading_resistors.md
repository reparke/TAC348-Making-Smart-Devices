---
marp: true
theme: itp

week: 5
category: lectures
title: Reading Resistor Bands

---

<!-- headingDivider: 2 -->

# Resistors Bands

## Accessibility Note

* Resistor values are determined visually by color bands
* Unfortunately resistor labeling is not accessibly designed
* To support students who are color blind or have difficulty distinguishing colors, here are [resources for support](https://reparke.github.io/TAC348-Making-Smart-Devices/reference/general/reading_resistors_color_blind.html)

## Resistor Labels

* The color codes indicate the resistance in Ohms (and sometimes how precise they are)
* There are 4 bands (colors), 5 band, and 6 band resistors
* Four band resistors are the most common, and the ones we will encounter in this class

## Resistor Chart
<img src="lecture_reading_resistors.assets/sparkfun_resistor_guide.png" alt="Resistor band chart" style="width:750px" />

## Understanding Resistor Chart

<img src="lecture_reading_resistors.assets/1565824411750.png" alt="Resistor band chart" style="width:300px" />

* Align such that the group of three bands are on the left
* The first two bands are the digits
* The third band is the multiplier (a power of ten)
* The last band is the tolerance (acceptable range of Ohms)
* Nominal value (Ohms) use SI units: **Ohm**, **K Ohms** *(1,000 Ohms)*, or **M Ohms** *(1,000,000 Ohms)*

## Reading Bands Ex. 1

|                                                              |                                                              |                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ | --------------------------------------------------- |
| <img src="lecture_reading_resistors.assets/sparkfun_resistor_guide_digit_multiplier.png" alt="Resistor band chart" style="width:300px" /> | <img src="lecture_reading_resistors.assets/1565825024722.png" alt="Resistor example 1" style="width:300px" /> | 1. Orange<br />2. Orange<br />3. Brown<br />4. Gold |

## Reading Bands Ex. 1

|                                                              |                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| <img src="lecture_reading_resistors.assets/sparkfun_resistor_guide_digit_multiplier.png" alt="Resistor band chart" style="width:300px" /> | <img src="lecture_reading_resistors.assets/1565825024722.png" alt="Resistor example 1" style="width:300px" /> | 1. Orange = 3<br />2. Orange = 3<br />3. Brown = 10 (10^1)<br />4. Gold +-5% |

## Reading Bands Ex. 1

* Orange	Orange	Brown ==> 3	3	10  (or 10^1)
* 33 * 10 = **330 Ohms**

## Reading Bands Ex. 2

|                                                              |                                                              |                                                   |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------- |
| <img src="lecture_reading_resistors.assets/sparkfun_resistor_guide_digit_multiplier.png" alt="Resistor band chart" style="width:300px" /> | <img src="lecture_reading_resistors.assets/1565826990515.png" alt="Resistor example 1" style="width:300px" /> | 1. Gray<br />2. White<br />3. Yellow<br />4. Gold |

## Reading Bands Ex. 2

|                                                              |                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| <img src="lecture_reading_resistors.assets/sparkfun_resistor_guide_digit_multiplier.png" alt="Resistor band chart" style="width:300px" /> | <img src="lecture_reading_resistors.assets/1565826990515.png" alt="Resistor example 1" style="width:300px" /> | 1. Gray = 8<br />2. White = 9<br />3. Yellow = 4<br />4. Gold +-5% |

## Reading Bands Ex. 2

* Gray 	White	Yellow	==> 8	9	10000 (or 10^4)
* 89 * 10000 = **890000 Ohms**
* But! Since this is over 1000 Ohms, we should use K Ohms (1000 Ohms)
* 890000 = 890 * 1000 = **890 K Ohms**


## 
|                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| 1.<img src="lecture_reading_resistors.assets/1565824411750.png" alt="Resistor example 1" style="width:200px" /> 2.<img src="lecture_reading_resistors.assets/1565824589676.png" alt="Resistor example 2" style="width:200px" /><br/>3.<img src="lecture_reading_resistors.assets/1565824850342.png" alt="Resistor example 3" style="width:200px" /> 4.<img src="lecture_reading_resistors.assets/1565825090288.png" alt="Resistor example 4" style="width:200px" /> | <img src="lecture_reading_resistors.assets/sparkfun_resistor_guide_digit_multiplier.png" alt="Resistor band chart" style="width:590px" /> |

<!-- 1. 
4 7 3 = 47 x 10^2 = 47 x 1 00 = 4700 = 4.7 x 10^3 = 4.7K
1 0 3 = 10 x 10^3 = 10 x 1000 = 10000 = 10 x 10^3 = 10K
flip: 6 8 4 = 68x10^4 = 680000 = 680x1000 = 680K
3 3 1 = 33x10 = 330 tol +-0.5% -->

## Credit

- Chart adapted from [Sparkfun](https://learn.sparkfun.com/tutorials/resistors#types-of-resistors)
- Images created with [Fritzing](https://fritzing.org/home/)