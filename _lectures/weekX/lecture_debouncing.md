---
marp: true
theme: tac

week: 16
category: lectures
title: Debouncing
---

<!-- headingDivider: 2 -->



# Debouncing



## Problem with Buttons
<img src="lecture_debouncing.assets/Bouncy_Switch.png" alt="switch_bounce.png" style="width:900px;" />

## Problem with Buttons

<img src="lecture_debouncing.assets/Bouncy_Switch.png" alt="switch_bounce.png" style="width:400px;" />

* Buttons and switches are mechanical and they tend to fluctuate briefly when pressed
* Leads to circuit "bounce" before the value stabilizes
* The Photon 2 typically goes through `loop()` multiple times before this stops so we can get false buttons presses or incorrect values

## Solving Debouncing

* This works by only considering input if the signal has been stable (*the same*) for a fixed amount of time 
* Everytime we see the signal is "bounce", we reset our `millis()` counter
* Once we verify the signal has been stable for long enough, we then check for a button press
* We need to distinguish **current button reading** (which may be noisy) from **current button state** (which we have confirmed is a legitimate HIGH / LOW value)

## Debouncing Algorithm

* If current button reading is **not** the same as last button state
  * Reset debounce counter
* If signal has been stable long enough (currentTime-lastDebounce > debounceDelay)
  * If current button reading is different from current button state
    * Update button state (legitimate button press)
    * **Here you execute desired code for button presses**
* Update previous button state with the reading value

##   Debouncing Code: Global Variables

```c++
int prevReading = HIGH;  // the last reading
int curButtonState;          // the current VERIFIED state
long lastDebounceTime = 0;   // the last time the output pin was toggled
long debounceDelay = 50;     // the debounce time; increase if the output
```

## Deboucing Code: Check if Bouncing Signal


```c++
void loop() {
    int curReading = digitalRead(PIN_BUTTON);  // check button read
    unsigned long currentDebounceTime = millis();

    if (curReading != prevReading) {
        lastDebounceTime = millis();
    }
```

## Debouncing Code: Register Valid Button Press

```c++
void loop() {
...
  if ((currentDebounceTime - lastDebounceTime) > debounceDelay) {
    // we know we have stable signal
    // see if input has changed
    if (curReading != curButtonState) {
      curButtonState = curReading;
      // legit button press so update current button state

      // FINALLY! here is your button code
      // if want to execute when button pressed down ONLY
     
    }
  }
  prevReading = curReading;  // update for next loop
}
```

## Debouncing Code: Full Example

```c++
void loop() {
  int curReading = digitalRead(PIN_BUTTON);  // check button read
  unsigned long currentDebounceTime = millis();

  if (curReading != prevReading) {
    lastDebounceTime = millis();
  }

  // debounce delay often 50-200 ms
  // we check for stable signal
  if ((currentDebounceTime - lastDebounceTime) > debounceDelay) {
    // we know we have stable signal
    // see if input has changed
    if (curReading != curButtonState) {
      curButtonState = curReading;
      // legit button press so update current button state

      // FINALLY! here is your button code
      // if want to execute when button pressed down ONLY
     
    }
  }

  prevReading = curReading;  // update for next loop
}
```