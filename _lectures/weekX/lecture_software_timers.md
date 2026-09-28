---
marp: true
theme: tac

week: 16
category: lectures
title: Software Timers
---

<!-- headingDivider: 2 -->

## Software Timers

* Software timers are another way to have code repeat at a specific time
* They can be useful when the `loop` code is slow, but a separate small task needs to run quickly
* The drawback is that the action of the software timer will not be synchronized with the rest of the `loop` actions


## `millis()` vs Software Timers

| millis()                           | Software Timers                                              |
| ---------------------------------- | ------------------------------------------------------------ |
| no limit on timed actions          | limited to 10 timers                                         |
| repeat time can be less than 1ms   | 1 ms is smallest repeat                                      |
| need to execute action in `loop()` | timer runs on its own                                        |
| all actions are synchonous         | timers may execute out of order (this can be both good and bad) |

## Software Timer Syntax


```c++
//Step 1: Declare global timer
Timer timer(<<FUNCTION>>, <<delayInMS>>);

//Step 2: Create your own function to repeat
void <<FUNCTION>>() {}

void setup() {
    timer.start();		//Step 3: Start timer (repeats on its own)
}
```

