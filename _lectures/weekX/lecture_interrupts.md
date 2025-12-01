---
marp: true
theme: itp

week: 16
category: lectures
title: Interrupts
---

# Interrupts


## Polling

- Often, we check for events (e.g. button press, accelerometer taps, potentiometer changes) using `if` statements inside `loop()`

- This is called **Polling**

- Timing depends on the code, but `loop()` might run 100,000 times per second so we are checking for a button press every 10 microsecond

- Quick button presses might last 100 milliseconds so this approach works to check for button presses

- *Analogy*: Imagine check every few minutes for your food delivery

## Problems with Polling

* We could **miss events** if `loop()` take longer to read (e.g. the code becomes more complex) OR we have faster sensor 
* **Wastes battery power** because device has to stay awake to poll for events
* Could **delay reacting to critical and emergency events**

## The Solution: Interrupts

- **Interrupts** are like notifications on our phones
- Rather than us constantly checking for a DM, our phone immediately notifies us when it arrives
- Similar idea to event-driven programming used with Bluetooth, Blynk, and webhooks
- **Benefits:**
  - Efficient (processor can sleep or do other math)
  - Responsive (catches signals that happen very fast)

## Program Flow with Interrupts


1. The main program runs `loop()`
2. An event occurs on pin designated for interrupts (e.g. voltage goes **HIGH**)
3. Photon 2 pauses `loop()` immediately
4. Photon 2 specific function called a function called **ISR** (Interrupt Service Routine)
5. Once the ISR finishes, `loop()` resumes exactly where it stopped

## The ISR (Interrupt Service Routine)

- This is the event handler for our interrupt
- **Key rules for ISRs:**
  - Must be **short and fast** 
  - Avoid `delay()` or `Serial.println()` 
  - Typically, just change a variable (flag) and handle the heavy lifting back in the `loop()`

## Steps to Using Interrupts

1) Wire input (e.g. button) to any pin 
2) In `setup()`, attach pin to interrupt
3) Create global variable to track flag (common but not required)
4) Create ISR function


## Step 2: Track Flags

- Create a global to check if event has occured

```c++
// global variable
volatile bool buttonPressed = false;
````

- `volatile` is C++'s way of telling the Photon 2 that this variable might change unexpectedly so it should always check its value (and not use a cached copy)
- Since we will change the variable INSIDE an **ISR** and then ACCESS it in `loop()`, we need to use `volatile`

 <!-- volatile isn't needed for polling because flow of control is sequential so compiler sees it changing; with interrupts the variable change happens outside of loop so compiler will think it's cached version is the variable is still valid, but it's changed-->



## Step 3: Attaching Pin to Interrupt

  - To set up an interrupt, use `attachInterrupt()` in `setup()`

```c++
attachInterrupt(pin, function, mode);
```

  - **pin**: Input signal
  - **function**: The name of the ISR function to run
  - **mode**: `RISING`, `FALLING`, or `CHANGE`



## Step 4: Create ISR

* This is the event handler that is trigged when the interrupt happens
* Function should be `void` and take no parameters
* Should be fast so usually just change the flag

```c++
void myISR() {
    buttonPressed = true;
}
```
## Final Note on Interrupts

| When to Use `millis()` and Polling                           | When to Use Interrupts                                       |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| Slow events (e.g., human input, slow temperature change)     | Events requiring **microsecond precision** (e.g., RPM counting) |
| When the device is **plugged in** and power is not a concern | When we want to conserve battery life and put the device to **sleep** |
| For long, complex logic since ISRs must be kept fast         | For time-critical safety features (e.g. emergency stop)      |

## Example 

```c++
// Step 1: wire input to interrupt
const int PIN_BUTTON = D2;
const int PIN_ONBOARD_LED = D7;

// Step 2: track flag
volatile bool toggleState = false; // use volatile if changed in ISR

// Step 4: Create ISR 
void myISR() {
  toggleState = !toggleState;
}

void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_ONBOARD_LED, OUTPUT);  

// Step 3: Attach the interrupt
// When D2 goes from HIGH to LOW, run the 'myISR' function
  attachInterrupt(buttonPin, myISR, FALLING);
}
void loop() {
// The loop just checks the variable state
  
  if (toggleState == true) {
    digitalWrite(PIN_ONBOARD_LED, HIGH);
  } else {
    digitalWrite(PIN_ONBOARD_LED, LOW);
  }
  
  delay(1000); 
}
```


## Exercise #1

1.  Connect button sensor to D2
3.  Create a `volatile` counter variable
4.  Create ISR to increment counter
5.  Every time the button is sensor triggers (FALLING), increment the counter
6.  In your loop, print the total count to `Serial.print` every 3 seconds

## Exercise #2

1.  Connect motion sensor to D3
2.  Connect an LED to D4
3.  Create a `volatile` alarm variable
4.  Create ISR to turn on LED
5.  Every time the motion triggers (RISING), turn on LED

<!--interrupts are critical when you require extreme speed or maximum power efficiency-->

<!--High-Speed or Fleeting Events: Interrupts guarantee you catch events that are too fast for the `loop()` to reliably catch like Rotary Encoders / Flow Meters / Tachometers Used for counting rapid pulses (RPM, volume) where microsecond precision is required to capture every event and calculate accurate speed or position; also Fast Sensor Spikes in a high-speed sensor (like an accelerometer detecting sudden impact) goes above a threshold-->

<!--Maximizing Battery Life: put device to sleep, avoid having to run loop, and wake immediately on interrupt-->

<!-- Real-Time events like emergency shutoff or alarm needs to happen immediately-->



## Credits

  * [Particle Documentation](https://docs.particle.io/reference/device-os/firmware/photon/interrupts/)
