---
marp: true
theme: tac

category: reference
title: (Reference) Buttons
show_in_list: true

---

<!-- headingDivider: 2 -->

# Push Buttons

<img src="buttons.assets/518189efce395f1f45000000.jpg" alt="various types of switches" style="width:700px" />



## Wiring

<img src="buttons.assets/Screenshot 2024-07-03 at 8.34.08 PM.png" alt="Screenshot 2024-07-03 at 8.34.08 PM" style="width:300px;" />

## Operation (Normally Open Button)

### Placement

 <img src="buttons.assets/1565910237122.png" alt="switch on breadboard" style="width:350px" />

### Unpressed / Open Circuit

<img src="buttons.assets/pushbutton_open.png" alt="switch on breadboard" style="width:400px"/>

* In the picture, each set of pins "vertically across" from each other are **always** connected (purple and blue)
* Each set of pins "horizontally next to" each other are **not connected** until the button is presed

### Pressed / Closed Circuit

* When button is pressed, all four pins are connected (yellow pins)

<img src="buttons.assets/pushbutton_closed.png" alt="switch on breadboard" style="width:400px"/>

### Values

* Open / unpressed is `HIGH`
* Closed / pressed is `LOW`

## Code

```c++
const int PIN_BUTTON = D2;

void setup() {
   pinMode(PIN_BUTTON, INPUT);  //configure
   Serial.begin(9600);
}

void loop() {
	//read button state
   int buttonVal = digitalRead(PIN_BUTTON); 
   
    if (buttonVal == HIGH) {
     Serial.write("Button not pressed");
   }
   else {
     Serial.write("Button pressed");
   }
 }
```





## Credit

- [Sparkfun](https://learn.sparkfun.com/tutorials/switch-basics/momentary-switches)
- [SVG]()
- Images created with [Fritzing](https://fritzing.org/home/)
