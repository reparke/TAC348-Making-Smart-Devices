---
marp: true
theme: tac

category: reference
title: (Reference) Switches
show_in_list: true

---

<!-- headingDivider: 2 -->

# Switches

<img src="switches.assets/image-20200710132427002.png" alt="image-20200710132427002" style="width:600px;" />

## Wiring



<img src="switches.assets/image-20240521154735959.png" alt="image-20200711010114011" style="width:300px;" />

## Operations

* Similar to pushbuttons, switches open or close a circuit
* We are going to look at **maintained switches** that continue to close or open a circuit indefinitely
* We will typically just call these components "switches"



### Connections

<img src="switches.assets/image-20200711010114011.png" alt="image-20200711010114011" style="width:300px;" />

<img src="switches.assets/image-20200711010308308.png" alt="image-20200711010308308" style="width:300px;" />

## Code

```c++
const int PIN_SWITCH = S2;

void setup() {
   pinMode(PIN_SWITCH, INPUT);  //configure
   Serial.begin(9600);
}

void loop() {
	//read button state
   int switchVal = digitalRead(PIN_SWITCH); 
   
    if (switchVal == HIGH) {
     Serial.write("Switch HIGH");
   }
   else {
     Serial.write("Switch LOW");
   }
 }
```



## Credit

- [Sparkfun](https://learn.sparkfun.com/tutorials/switch-basics/all) has some great illustrations on this for a deep dive into switches
- Images created with [Fritzing](https://fritzing.org/home/)

