---
marp: true
theme: itp

category: reference
title: (Reference) Potentiometers
show_in_list: true

---

<!-- headingDivider: 2 -->

# Potentiometers

## Potentiometer (Pot)

<img src="potentiometers.assets/515deb26ce395f3959000000.png" style="width:500px" alt="potentiometers" />

## Wiring

- Requires analog input pin
  - `A0`
  - `A1`
  - `A2`
  - `A5`
  - `A3` (`SDA` or `D0`)
  - `A4` (`SCL` or `D1`)

<img src="potentiometers.assets/image-20240521154022998.png" style="width:400px;" />



## Operation

* As you turn the knob, Photon 2 will measure a voltage change on analog input (due to voltage divider)
* Since this is an analog input, we use **analog to digital conversion** to read input
* Voltage on pin will varies 0v to 3.3v, and Photon 2 will read 0 to 4095 

## Code

```c++
const int PIN_POT = A0;		//input pin
int potValue = 0;			//value from read

void setup() {
    pinMode(PIN_POT, INPUT);
}
void loop() {
   	// read analog value (ADC); range 0-4095
    int potValue = analogRead(PIN_POT);
    
    // if you want to know the actual voltage 
	int voltage = (float) lightReading / 4095 * 3.3;
}
```



## Credit

- [Pixabay](https://pixabay.com/photos/potentiometer-guitar-electric-guitar-482082/)
- [Pixabay](https://pixabay.com/vectors/variable-resistance-resistors-36565/)
- [Sparkfun](https://learn.sparkfun.com/tutorials/resistors#types-of-resistors)
- [Sparkfun](https://learn.sparkfun.com/tutorials/voltage-dividers)
- Diagrams created with [Fritzing](https://fritzing.org)