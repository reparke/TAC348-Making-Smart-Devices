---
marp: false
theme: itp

week: 7
category: lectures
title: Sound and Piezo Buzzers
---

<!-- headingDivider: 2 -->

# Sound and Piezo Buzzers
 <img src="lecture_audio.assets/cropped.jpg" alt="Sound wave" style="height:500px;" />  





## Quick Review: Sound Frequencies

 <img src="lecture_audio.assets/cropped.jpg" alt="Sound wave" style="width:700px;" /> 

* Sound is created by vibrations in air pressure (sound waves)
* Commonly we measure the amplitude (volume) and the frequency (perceived pitch)

## Piezo Buzzer

 <img src="lecture_audio.assets/Buzzer1.jpg" alt="Buzzer" style="width:500px" /> 

## Piezo Buzzer
* Uses magnetic coil to vibrate a metal disc to produce sound
* Control the pitch by a form of pulse width modulation (PWM)

## Uses of piezo buzzers

* Buzzer are small and cost-effective
* Can be used for alarms, games, toys
* Can produce tones and simulate single notes

## Limitations of Buzzer

* Frequency
  * Human hearing is roughly 20 Hz to 20,000 KHz 
  * Hertz (Hz) is cycles per second
  * Piezo buzzer operates up to 2.048 KHz
* Sound Quality
  * Only generate tones through square waves

## Connecting Buzzers

<img src="lecture_audio.assets/Screenshot 2024-06-19 at 12.44.06 PM.png" alt="Screenshot 2024-06-19 at 12.44.06 PM" style="width:750px"/>

## Connecting Buzzers

<img src="lecture_audio.assets/buzzer_polarity.jpg" alt="buzzer polarity" style="height:300px;"/> <img src="lecture_audio.assets/Buzzer3.jpg" alt="buzzer polarity" style="height:300px;" /> 

* Buzzers are polarized so look for the **+**
* Negative pin to **gnd** and positive pin to Photon 2 output

## Producing Sound

Syntax

```c++
tone(<<PIN>>, <<FREQUENCY>>);		// will play tone indefinitely
tone(<<PIN>>, <<FREQUENCY>>, <<DURATION>>);
```

* `tone()` generates a square wave using PWM (50% duty cycle)

* `pin` is connected the speaker

* `frequency` is sound frequency in Hz (20Hz to 20KHz)

* `duration` is the length of tone in milliseconds 

## Producing Sound

  Example


```c++
tone(D6, 500, 1000);	// play 500Hz tone for 1000ms (1 sec)
tone(D2, 2000, 3000);	// play 2KHz tone for 3000 ms (3 sec)
tone(D2, 1000, 0);		// play 1KHz tone (don't stop)
```

## A Note on Photon 2 and `tone()`

* `tone()` requires a pin that supports PWM
* Only certain pins support PWM
  * `D1` (`SCL` or `A4`)
  * `A2`
  * `A5`
  * `MISO` (`D16`)
  * `MOSI` (`D15`)

* All PWM pins on the Photon 2 are assigned to the same timer, meaning you can only generate ONE frequency at a time. In other words, you cannot play different notes with different buzzers at the same time.

## Stopping Sound
Syntax

```cpp
noTone(<<PIN>>);
```

* To stop a continuous tone or stop tone before duration is over

## A Note about Tone and Blocking

- `tone()` is non-blocking (meaning it doesn't cause delays or interfere with other Photon 2 actions)
- This means the Photon 2 will not wait for one `tone()` to finish before playing the next. For example, in the code below, even though the first tone has a duration of 1 sec, the second tone will start immediately, meaning you will hear the second tone

```cpp
tone(D6, 500, 1000);	
tone(D2, 2000, 3000);	
```

* In order hear a tone for certain length of time, we either need to use a `millis()` timer or `delay()`

## Optional: Controlling Volume

<img src="lecture_audio.assets/Screenshot 2024-06-19 at 12.49.53 PM.png" alt="Screenshot 2024-06-19 at 12.49.53 PM" style="width:750px;" />

## Optional: Controlling Volume

* All tones will be at the same volume since Photon 2 can change only frequency (not amplitude)
* To control volume, connect a potentiometer between `negative` and `gnd`
* Potentiometer acts a current limit resistor to control volume

## Playing Melodies

* Musical notes can represented as constants 
* Add this file ([pitches.h](pitches.h)) to your `src` folder and then add `#include "pitches.h"` to your sketch
* You can then refer to music notes in the following manner

```cpp
tone(D2, NOTE_C4, 1000);  // play the note "middle C"	
```

## Finding Notes of Popular Songs

* [Notes for some popular songs](https://dragaosemchama.com/en/2019/02/songs-for-arduino/) (note that the format for playing notes is different in this code, but you can still extract the notes and duration from these examples)
* [MIDI to C converter](https://projects.neutonfoo.com/mc-piezo/) allows you convert a MIDI file directly into 

## References

* Images created with [Fritzing](https://fritzing.org/home/)
* [Pixabay](https://pixabay.com/illustrations/banner-header-sound-wave-music-1571999/)
* [Sparkfun](https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40/circuit-2a-buzzer)
* [Neuton Foo](https://projects.neutonfoo.com/mc-piezo/)
