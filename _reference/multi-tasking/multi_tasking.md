---
marp: true
theme: tac

category: reference
title: (Reference) Multi Tasking with millis()
show_in_list: true

---

<!-- headingDivider: 2 -->

# Multi-Tasking: Delay
## Main Idea

* `delay()` is **blocking**
  * This means the Photon 2 is essentially paused and can't do anything else
* We need to be able to synchronize events and **multi-task** just like our computers and phones
* `millis()` is a function that returns the "relative current time" (number of **milliseconds** that have elapsed since the Photon 2 last turned on / reset)
* We can call `millis()` at different points in time to compare the passage of time
* When a specific time has elapsed, we can take an action



## Code
```c++
unsigned long prevMillis = 0;		//last time we checked time
unsigned long interval = 1000;	//this could be any length, but here we set 1000 ms (1 sec)  between operations

void setup() {}

void loop() {
  unsigned long curMillis = millis();     //current time
  
  //check if (now - previous) is greater than our desired interval
  if (curMillis - prevMillis >= interval) {   
    previousMillis = curMillis;      //if YES, update previous
  	
    //Here is where you include any code you want to happen on the time interval
  }
}
```
