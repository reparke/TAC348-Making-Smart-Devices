
#ifndef PULSE_INTERRUPT_H
#define PULSE_INTERRUPT_H

#include "Particle.h"

volatile int rate[10];                     // array to hold last ten IBI values
volatile unsigned long sampleCounter = 0;  // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;   // used to find IBI
volatile int P = 2048;  // used to find peak in pulse wave, seeded
volatile int T = 2048;  // used to find trough in pulse wave, seeded
volatile int thresh =
    2048;                // used to find instant moment of heart beat, seeded
volatile int amp = 410;  // used to hold amplitude of pulse waveform, seeded
volatile boolean firstBeat =
    true;  // used to seed rate array so we startup with reasonable BPM
volatile boolean secondBeat =
    false;  // used to seed rate array so we startup with reasonable BPM

// these variables are volatile because they are used during the interrupt
// service routine!
volatile int BPM;        // used to hold the pulse rate
volatile int rawSignal;  // holds the incoming raw data
volatile int IBI = 600;  // holds the time between beats, must be seeded!
volatile boolean Pulse =
    false;  // true when pulse wave is high, false when it's low
volatile boolean QS = false;  // becomes true when Arduoino finds a beat.

// SparkIntervalTimer uses hardware timers that are otherwise allocated for
// PIN functions (ADC/PWM) The first allocated timer is TIMR2 on Core and
// TIMR3 on Photon which is assigned to A0 & A1 ADC/PWM channels So use A2
// (though A0 & A1 ADC should still work on Core and not affected on Photon)
// for pulse input, D7 (onboard LED) for blink LED and D6 for fancy LED
//  VARIABLES
int pulsePin = A0;  // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = D7;  // pin to blink led at each beat
int fadePin = D6;   // pin to do fancy classy fading blink at each beat
int fadeRate = 0;   // used to fade LED on with PWM on fadePin

void timerSetup();
void pulseISR(void);
#endif