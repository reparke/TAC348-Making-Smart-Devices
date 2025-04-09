#include "PulseSensor.h"

#include "Particle.h"

extern PulseSensor pulseSensor;

// THIS IS THE TIMING FUNCTION
// makes sure that we take a reading every 2 miliseconds
void pulseISR(void) {
    
    pulseSensor.rawSignal =
        analogRead(pulseSensor.pulsePin);  // read the Pulse Sensor
    pulseSensor.sampleCounter +=
        2;  // keep track of the time in mS with this variable
    int N = pulseSensor.sampleCounter -
            pulseSensor.lastBeatTime;  // monitor the time since the
                                       // last beat to avoid noise

    //  find the peak and trough of the pulse wave
    if (pulseSensor.rawSignal < pulseSensor.thresh &&
        N > (pulseSensor.IBI / 5) *
                3) {  // avoid dichrotic noise by waiting 3/5 of last IBI
        if (pulseSensor.rawSignal < pulseSensor.T) {  // T is the trough
            pulseSensor.T =
                pulseSensor
                    .rawSignal;  // keep track of lowest point in pulse wave
        }
    }

    if (pulseSensor.rawSignal > pulseSensor.thresh &&
        pulseSensor.rawSignal >
            pulseSensor.P) {  // thresh condition helps avoid noise
        pulseSensor.P = pulseSensor.rawSignal;  // P is the peak
    }  // keep track of highest point in pulse wave

    //  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
    // signal surges up in value every time there is a pulse
    if (N > 250) {  // avoid high frequency noise
        if ((pulseSensor.rawSignal > pulseSensor.thresh) &&
            (pulseSensor.Pulse == false) && (N > (pulseSensor.IBI / 5) * 3)) {
            pulseSensor.Pulse =
                true;  // set the Pulse flag when we think there is a pulse
            digitalWrite(pulseSensor.blinkPin, HIGH);  // turn on blink LED
            pulseSensor.IBI =
                pulseSensor.sampleCounter -
                pulseSensor.lastBeatTime;  // measure time between beats in mS
            pulseSensor.lastBeatTime =
                pulseSensor.sampleCounter;  // keep track of time for next pulse

            if (pulseSensor.secondBeat) {  // if this is the second beat, if
                                           // secondBeat ==
                                           // TRUE
                pulseSensor.secondBeat = false;  // clear secondBeat flag
                for (int i = 0; i <= 9; i++) {  // seed the running total to get
                                                // a realisitic BPM at startup
                    pulseSensor.rate[i] = pulseSensor.IBI;
                }
            }

            if (pulseSensor.firstBeat) {  // if it's the first time we found a
                                          // beat, if firstBeat == TRUE
                pulseSensor.firstBeat = false;  // clear firstBeat flag
                pulseSensor.secondBeat = true;  // set the second beat flag
                return;  // IBI value is unreliable so discard it
            }

            // keep a running total of the last 10 IBI values
            uint16_t runningTotal = 0;  // clear the runningTotal variable

            for (int i = 0; i <= 8; i++) {  // shift data in the rate array
                pulseSensor.rate[i] =
                    pulseSensor.rate[i + 1];  // and drop the oldest IBI value
                runningTotal +=
                    pulseSensor.rate[i];  // add up the 9 oldest IBI values
            }

            pulseSensor.rate[9] =
                pulseSensor.IBI;  // add the latest IBI to the rate array
            runningTotal +=
                pulseSensor.rate[9];  // add the latest IBI to runningTotal
            runningTotal /= 10;       // average the last 10 IBI values
            pulseSensor.BPM =
                60000 / runningTotal;  // how many beats can fit into a
                                       // minute? that's BPM!
            pulseSensor.QS = true;     // set Quantified Self flag
            // QS FLAG IS NOT CLEARED INSIDE THIS ISR
        }
    }

    if (pulseSensor.rawSignal < pulseSensor.thresh &&
        pulseSensor.Pulse ==
            true) {  // when the values are going down, the beat is over
        digitalWrite(pulseSensor.blinkPin, LOW);  // turn off pin blink LED
        pulseSensor.Pulse =
            false;  // reset the Pulse flag so we can do it again
        pulseSensor.amp =
            pulseSensor.P - pulseSensor.T;  // get amplitude of the pulse wave
        pulseSensor.thresh =
            pulseSensor.amp / 2 +
            pulseSensor.T;  // set thresh at 50% of the amplitude
        pulseSensor.P = pulseSensor.thresh;  // reset these for next time
        pulseSensor.T = pulseSensor.thresh;
    }

    if (N > 2500) {                // if 2.5 seconds go by without a beat
        pulseSensor.thresh = 512;  // set thresh default
        pulseSensor.P = 512;       // set P default
        pulseSensor.T = 512;       // set T default
        pulseSensor.lastBeatTime =
            pulseSensor.sampleCounter;   // bring the lastBeatTime up to date
        pulseSensor.firstBeat = true;    // set these to avoid noise
        pulseSensor.secondBeat = false;  // when we get the heartbeat back
    }

}  // end time function

void threadFunction(void) {
    system_tick_t lastThreadTime = 0;

    while (true) {
        // pulseSensor.counter++;
        pulseISR();

        // Delay so we're called every 10 milliseconds (100 times per second)
        os_thread_delay_until(&lastThreadTime, 2);
    }
    // You must not return from the thread function
}

PulseSensor::PulseSensor() { new Thread("pulseThread", threadFunction); }

void PulseSensor::attach(int pin) { pulsePin = pin; }

void PulseSensor::start() {
    counter = 0;

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
}

// int PulseSensor::getBPM() {
//     // QS = false;  // reset the for next time
//     return BPM;
// }

// boolean PulseSensor::beatDetected() { return QS; }

void PulseSensor::process(void) {
    // Put updates into foreground
    if (QS) {
        if (BPM >= 0)
            PulseSensorAmped_data(BPM, IBI, counter);
        else
            PulseSensorAmped_lost();
        QS = false;
    }
}
