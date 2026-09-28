---
marp: true
theme: tac

category: reference
title: (Reference) Serial Monitor
show_in_list: true

---

<!-- headingDivider: 2 -->

# Serial Monitor

## Main Idea

* Serial monitor lets you receive status messages from Photon 2
* Serial Monitor lets you print debug messages

## Operation

- Open Serial Monitor in Workbench
  - View > Command Palette > Serial Monitor

<img src="serial_monitor.assets/1565664078373.png" alt="width:300px" style="width:300px" />

* Serial Monitor is **only** available while the Photon 2 is connected to your computer via USB


## Code

- Below is a basic example which displays the following on the screen

```html
Hello World
There are 7 days in a week
```



```c++
void setup() {
    //initialize Serial object
    Serial.begin(9600);
}

void loop() {
    //Display message
    Serial.println("Hello World");
	
	//Display string and int
	int days = 7;
	Serial.println("There are " + String(days) + " days in a week")
}

```

