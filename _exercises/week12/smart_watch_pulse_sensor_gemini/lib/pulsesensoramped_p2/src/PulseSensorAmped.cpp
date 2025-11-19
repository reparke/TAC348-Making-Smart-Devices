#include "PulseSensorAmped.h"

#include "Particle.h"

// Timer pulseTimer(2, pulseISR);
extern PulseSensor PulseSensorAmped;


// THIS IS THE TIMER (2 on Core, 3 on Photon) INTERRUPT SERVICE ROUTINE.
// The Timer makes sure that we take a reading every 2 miliseconds
// ISR(TIMER2_COMPA_vect){                         // triggered when Timer2
// counts to 124
void pulseISR(void) {
    noInterrupts();
    PulseSensorAmped.rawSignal =
        analogRead(PulseSensorAmped.pulsePin);  // read the Pulse Sensor
    PulseSensorAmped.sampleCounter +=
        2;  // keep track of the time in mS with this variable
    int N = PulseSensorAmped.sampleCounter -
            PulseSensorAmped.lastBeatTime;  // monitor the time since the
                                       // last beat to avoid noise

    //  find the peak and trough of the pulse wave
    if (PulseSensorAmped.rawSignal < PulseSensorAmped.thresh &&
        N > (PulseSensorAmped.IBI / 5) *
                3) {  // avoid dichrotic noise by waiting 3/5 of last IBI
        if (PulseSensorAmped.rawSignal < PulseSensorAmped.T) {  // T is the trough
            PulseSensorAmped.T =
                PulseSensorAmped
                    .rawSignal;  // keep track of lowest point in pulse wave
        }
    }

    if (PulseSensorAmped.rawSignal > PulseSensorAmped.thresh &&
        PulseSensorAmped.rawSignal >
            PulseSensorAmped.P) {  // thresh condition helps avoid noise
        PulseSensorAmped.P = PulseSensorAmped.rawSignal;  // P is the peak
    }  // keep track of highest point in pulse wave

    //  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
    // signal surges up in value every time there is a pulse
    if (N > 250) {  // avoid high frequency noise
        if ((PulseSensorAmped.rawSignal > PulseSensorAmped.thresh) &&
            (PulseSensorAmped.Pulse == false) && (N > (PulseSensorAmped.IBI / 5) * 3)) {
            PulseSensorAmped.Pulse =
                true;  // set the Pulse flag when we think there is a pulse
            digitalWrite(PulseSensorAmped.blinkPin, HIGH);  // turn on blink LED
            PulseSensorAmped.IBI =
                PulseSensorAmped.sampleCounter -
                PulseSensorAmped.lastBeatTime;  // measure time between beats in mS
            PulseSensorAmped.lastBeatTime =
                PulseSensorAmped.sampleCounter;  // keep track of time for next pulse

            if (PulseSensorAmped.secondBeat) {  // if this is the second beat, if
                                           // secondBeat ==
                                           // TRUE
                PulseSensorAmped.secondBeat = false;  // clear secondBeat flag
                for (int i = 0; i <= 9; i++) {  // seed the running total to get
                                                // a realisitic BPM at startup
                    PulseSensorAmped.rate[i] = PulseSensorAmped.IBI;
                }
            }

            if (PulseSensorAmped.firstBeat) {  // if it's the first time we found a
                                          // beat, if firstBeat == TRUE
                PulseSensorAmped.firstBeat = false;  // clear firstBeat flag
                PulseSensorAmped.secondBeat = true;  // set the second beat flag
                interrupts();
                return;  // IBI value is unreliable so discard it
            }

            // keep a running total of the last 10 IBI values
            uint16_t runningTotal = 0;  // clear the runningTotal variable

            for (int i = 0; i <= 8; i++) {  // shift data in the rate array
                PulseSensorAmped.rate[i] =
                    PulseSensorAmped.rate[i + 1];  // and drop the oldest IBI value
                runningTotal +=
                    PulseSensorAmped.rate[i];  // add up the 9 oldest IBI values
            }

            PulseSensorAmped.rate[9] =
                PulseSensorAmped.IBI;  // add the latest IBI to the rate array
            runningTotal +=
                PulseSensorAmped.rate[9];  // add the latest IBI to runningTotal
            runningTotal /= 10;       // average the last 10 IBI values
            PulseSensorAmped.BPM =
                60000 / runningTotal;  // how many beats can fit into a
                                       // minute? that's BPM!
            PulseSensorAmped.QS = true;     // set Quantified Self flag
            // QS FLAG IS NOT CLEARED INSIDE THIS ISR
        }
    }

    if (PulseSensorAmped.rawSignal < PulseSensorAmped.thresh &&
        PulseSensorAmped.Pulse ==
            true) {  // when the values are going down, the beat is over
        digitalWrite(PulseSensorAmped.blinkPin, LOW);  // turn off pin blink LED
        PulseSensorAmped.Pulse =
            false;  // reset the Pulse flag so we can do it again
        PulseSensorAmped.amp =
            PulseSensorAmped.P - PulseSensorAmped.T;  // get amplitude of the pulse wave
        PulseSensorAmped.thresh =
            PulseSensorAmped.amp / 2 +
            PulseSensorAmped.T;  // set thresh at 50% of the amplitude
        PulseSensorAmped.P = PulseSensorAmped.thresh;  // reset these for next time
        PulseSensorAmped.T = PulseSensorAmped.thresh;
    }

    if (N > 2500) {                // if 2.5 seconds go by without a beat
        PulseSensorAmped.thresh = 512;  // set thresh default
        PulseSensorAmped.P = 512;       // set P default
        PulseSensorAmped.T = 512;       // set T default
        PulseSensorAmped.lastBeatTime =
            PulseSensorAmped.sampleCounter;   // bring the lastBeatTime up to date
        PulseSensorAmped.firstBeat = true;    // set these to avoid noise
        PulseSensorAmped.secondBeat = false;  // when we get the heartbeat back
    }

    interrupts();
}  // end isr

PulseSensor::PulseSensor() : pulseTimer(2, pulseISR) {}

void PulseSensor::attach(int pin) { pulsePin = pin; }

void PulseSensor::timerSetup(void) {
    // Allocate a timer to throw an interrupt every 2mS.
    pulseTimer.start();
}
void PulseSensor::start() {
    sampleCounter = 0;  // used to determine pulse timing
    lastBeatTime = 0;   // used to find IBI
    P = 2048;           // used to find peak in pulse wave, seeded
    T = 2048;           // used to find trough in pulse wave, seeded
    thresh = 2048;      // used to find instant moment of heart beat, seeded
    amp = 410;          // used to hold amplitude of pulse waveform, seeded
    firstBeat =
        true;  // used to seed rate array so we startup with reasonable BPM
    secondBeat =
        false;  // used to seed rate array so we startup with reasonable BPM

    // these variables are volatile because they are used during the interrupt
    // service routine!
    BPM = 0;        // used to hold the pulse rate
    rawSignal = 0;  // holds the incoming raw data
    IBI = 600;      // holds the time between beats, must be seeded!
    Pulse = false;  // true when pulse wave is high, false when it's low
    QS = false;     // becomes true when Arduoino finds a beat.

    pulseTimer.start();
}
void PulseSensor::process(void) {
    // Put updates into foreground
    if (QS) {
        if (BPM >= 0)
            PulseSensorAmped_data(BPM, IBI);
        else
            PulseSensorAmped_lost();
        QS = false;
    }
}
