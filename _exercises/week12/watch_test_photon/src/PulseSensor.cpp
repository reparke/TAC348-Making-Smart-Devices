#include "PulseSensor.h"

#include "Particle.h"

Timer pulseTimer(2, pulseISR);

void timerSetup(void) {
    // Allocate a timer to throw an interrupt every 2mS.
    pulseTimer.start();
}

// THIS IS THE TIMER (2 on Core, 3 on Photon) INTERRUPT SERVICE ROUTINE.
// The Timer makes sure that we take a reading every 2 miliseconds
// ISR(TIMER2_COMPA_vect){                         // triggered when Timer2
// counts to 124
void pulseISR(void) {
    noInterrupts();
    rawSignal = analogRead(pulsePin);  // read the Pulse Sensor
    sampleCounter += 2;  // keep track of the time in mS with this variable
    int N =
        sampleCounter -
        lastBeatTime;  // monitor the time since the last beat to avoid noise

    //  find the peak and trough of the pulse wave
    if (rawSignal < thresh &&
        N > (IBI / 5) *
                3) {  // avoid dichrotic noise by waiting 3/5 of last IBI
        if (rawSignal < T) {  // T is the trough
            T = rawSignal;    // keep track of lowest point in pulse wave
        }
    }

    if (rawSignal > thresh &&
        rawSignal > P) {  // thresh condition helps avoid noise
        P = rawSignal;    // P is the peak
    }  // keep track of highest point in pulse wave

    //  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
    // signal surges up in value every time there is a pulse
    if (N > 250) {  // avoid high frequency noise
        if ((rawSignal > thresh) && (Pulse == false) && (N > (IBI / 5) * 3)) {
            Pulse = true;  // set the Pulse flag when we think there is a pulse
            digitalWrite(blinkPin, HIGH);  // turn on blink LED
            IBI = sampleCounter -
                  lastBeatTime;            // measure time between beats in mS
            lastBeatTime = sampleCounter;  // keep track of time for next pulse

            if (secondBeat) {  // if this is the second beat, if secondBeat ==
                               // TRUE
                secondBeat = false;             // clear secondBeat flag
                for (int i = 0; i <= 9; i++) {  // seed the running total to get
                                                // a realisitic BPM at startup
                    rate[i] = IBI;
                }
            }

            if (firstBeat) {  // if it's the first time we found a beat, if
                              // firstBeat == TRUE
                firstBeat = false;  // clear firstBeat flag
                secondBeat = true;  // set the second beat flag
                interrupts();
                return;  // IBI value is unreliable so discard it
            }

            // keep a running total of the last 10 IBI values
            uint16_t runningTotal = 0;  // clear the runningTotal variable

            for (int i = 0; i <= 8; i++) {  // shift data in the rate array
                rate[i] = rate[i + 1];      // and drop the oldest IBI value
                runningTotal += rate[i];    // add up the 9 oldest IBI values
            }

            rate[9] = IBI;               // add the latest IBI to the rate array
            runningTotal += rate[9];     // add the latest IBI to runningTotal
            runningTotal /= 10;          // average the last 10 IBI values
            BPM = 60000 / runningTotal;  // how many beats can fit into a
                                         // minute? that's BPM!
            QS = true;                   // set Quantified Self flag
            // QS FLAG IS NOT CLEARED INSIDE THIS ISR
        }
    }

    if (rawSignal < thresh &&
        Pulse == true) {  // when the values are going down, the beat is over
        digitalWrite(blinkPin, LOW);  // turn off pin blink LED
        Pulse = false;         // reset the Pulse flag so we can do it again
        amp = P - T;           // get amplitude of the pulse wave
        thresh = amp / 2 + T;  // set thresh at 50% of the amplitude
        P = thresh;            // reset these for next time
        T = thresh;
    }

    if (N > 2500) {                    // if 2.5 seconds go by without a beat
        thresh = 512;                  // set thresh default
        P = 512;                       // set P default
        T = 512;                       // set T default
        lastBeatTime = sampleCounter;  // bring the lastBeatTime up to date
        firstBeat = true;              // set these to avoid noise
        secondBeat = false;            // when we get the heartbeat back
    }

    interrupts();
}  // end isr
