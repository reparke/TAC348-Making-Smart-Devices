---
marp: false
theme: itp

week: 15
category: lectures
title: Sleep and Battery Conservation
---

<!-- headingDivider: 2 -->

#  Sleep and Battery Conservation

![bg opacity:.85 right:58%](lecture_sleep.assets/david-clode-Yg_sNKOiXvY-unsplash.jpg)

## Power Conservation

- Continuously keeping the Photon 2 on uses a lot of power

  - Connection to Particle Cloud

  - Running `loop ()`

  - Responding to any interrupts or inputs
- To limit wasting electricity and extend the time between battery charges, use **sleep**, which turns off some or all of the Photon 2 components
- Note: **sleep** for more than 10 seconds. Less than that use more power turning it on / off than you will be saved

## Zzzz....Three Sleep Modes

- `STOP` (most wake options, highest power)
- `ULTRA_LOW_POWER` (ULP)
- `HIBERNATE` (fewest wake options, lowest power)

## Sleep Considerations

- Choosing the specific sleep mode and options depends on your specific application

- Some things you'll need to consider
  - How do you want to wake up the device?
  - How long in between wake periods will you have?
  - How quickly do you need the device to respond once it wakes?
- In general, choose the mode that uses the least power but support the features you want

## Power vs. Responsiveness

<img src="lecture_sleep.assets/sleep-power.png" alt="Sleep Power" style="width:550px;" />

<!-- This shows that you can conserve power if you hibernate but it will take longer to publish a message -->



## Waking Photon 2 from Ultra Low Power Mode

* Specific time duration
* Input on any GPIO
  * `RISING` (low to high)
  * `FALLING` (high to low)
  * `CHANGE` (either low to high or high to low) 

## What Happens After Waking

<img src="lecture_sleep.assets/sleep-variables.png" alt="Wake Methods" style="width:900px" />

<!-- note HIBERNATE wakes as if it has been reset. It goes through setup() again and starts with all non-retained variables cleared. In ULTRA_LOW_POWER and STOP modes, execution continues after the line of code that put the device to sleep, with all variables preserved. -->

## Sleep Syntax

- Here is the general syntax to sleep 

```c++
SystemSleepConfiguration config;
config.mode(SystemSleepMode::<<ADD SLEEP MODE>>).<<ADD WAKE OPTIONS>>;
System.sleep(config);
```
## Sleep Example #1
- Put device in `HIBERNATE` and wake after 10 min

```c++
SystemSleepConfiguration config;
config.mode(SystemSleepMode::ULTRA_LOW_POWER).duration(10min);
System.sleep(config);
```
## Sleep Example #2
- Put device in `ULTRA_LOW_POWER` and wake with a falling (`HIGH` to `LOW`) signal on pin D10

```c++
SystemSleepConfiguration config;
config.mode(SystemSleepMode::ULTRA_LOW_POWER).gpio(D10, FALLING);
System.sleep(config);
```
## Sleep Example #3

- Put device in `ULTRA_LOW_POWER`, and wake with a rising (`LOW` to `HIGH`) signal on pin D10 **or** after 2 hours

```c++
SystemSleepConfiguration config;
config.mode(SystemSleepMode::ULTRA_LOW_POWER).gpio(D10, RISING).duration(2h);
System.sleep(config);
```

### Note on Inputs

* Some sensors might not work as wake input triggers

* For example, the Sparkfun PIR (JST) doesn't work as a wake trigger. As soon as the Photon 2 goes to sleep, the alarm pin drops from HIGH to LOW and triggers waking. A different PIR might work

  

## Waking but Staying Silent

- Using the wifi to connect to the cloud takes time and uses battery

- If you don't need to update in real-time, you can do the following

  - Sleep the Photon 2

  - Wake up after a fixed time, but do **not** connect to the cloud

  - Read / store sensor data

  - Sleep the Photon 2

- After a certain amount of time or number of sensor readings, you can send all the saved data to the cloud at once


## Controlling Cloud Connection

- To prevent automatic connection to the cloud, use the following command at the top of your code (**not** inside `loop` or `setup`)

```c++
SYSTEM_MODE(SEMI_AUTOMATIC);
```

- When you are ready to connect to the cloud, run the following command in your code

```c++
Particle.connect();
```

  

## Exercise

<img src="lecture_sleep.assets/Screenshot 2024-06-29 at 11.56.12 PM.png" alt="Screenshot 2024-06-29 at 11.56.12 PM" style="width:700px;" />

## Credit

* [Particle - About Sleep](https://docs.particle.io/tutorials/learn-more/about-sleep/)
* [Particle - `sleep()` documentation](https://docs.particle.io/cards/firmware/sleep-sleep/sleep-sleep/)
* Photo by [David Clode](https://unsplash.com/photos/Yg_sNKOiXvY) on [Unsplash](https://unsplash.com/s/photos/sleep?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText)

























