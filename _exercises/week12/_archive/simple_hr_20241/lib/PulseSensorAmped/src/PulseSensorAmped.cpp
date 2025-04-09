/*
 * Developed by Bill Siever (http://siever.info)
 * 
 * Based on http://pulsesensor.com/
 * (Uses algorithm / code from https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/PulseSensorAmped_Arduino_1dot4/Interrupt.ino)
 *
 */

/*
  PulseSensorAmped.h - Collect data from one (or more) Amped Pulse Sensors
  (http://pulsesensor.com/)
  Copyright (c) 2016 William Siever.  All right reserved.
*/

#include "PulseSensorAmped.h"

#include "Arduino.h"

// Declare the instance
PulseSensorAmpedClass PulseSensorAmped;


// ************   Timer handler 
// Thanks to: https://www.jaredwolff.com/how-to-real-time-processing-on-particle-mesh/
// See: https://github.com/jaredwolff/particle_mesh_ppi_example
#include "spark_wiring_interrupts.h"
nrfx_timer_t timer4 = NRFX_TIMER_INSTANCE(4);

void timer_isr(nrf_timer_event_t event_type, void * p_context) {
    // Timer Event 
    //if (NRF_TIMER4->EVENTS_COMPARE[0] != 0)
    PulseSensorAmped.update();
}

void timer(unsigned ms) {
    // Setup for timer control
    attachInterruptDirect(TIMER4_IRQn,nrfx_timer_4_irq_handler);

    // Timer configuration
    nrfx_timer_config_t timer_config = NRFX_TIMER_DEFAULT_CONFIG;

    // Set priority as high as possible.
    timer_config.interrupt_priority = 3;

    // Init the timer
    (void)nrfx_timer_init(&timer4,&timer_config,timer_isr);
    // if( err_code != NRF_SUCCESS ) Log.error("nrfx_timer_error");

    // Disable and clear the timer.
    nrfx_timer_disable(&timer4);
    nrfx_timer_clear(&timer4);

    // Calculate the ticks for 50 uS
    uint32_t ticks = nrfx_timer_us_to_ticks(&timer4,ms*1000);

    // Set the compare for the start and the end
    nrfx_timer_extended_compare(&timer4, NRF_TIMER_CC_CHANNEL0, ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);
}

// Constructor
PulseSensorAmpedClass::PulseSensorAmpedClass() {
  analogPin = -1;
  fakeData = false;
}

void PulseSensorAmpedClass::spoofedData(boolean spoof) {
  fakeData = spoof;
}                     
                                                                                                                                                                                                                                                                              
// Configure the sensor
void PulseSensorAmpedClass::attach(int pin) {
  // Do not allow analog pin to change
  if(analogPin==-1) {
    analogPin = pin;
  }
  timer(2); // Enable a 2ms timer.
}

void PulseSensorAmpedClass::start(void) {
  // Only allow the sensor to start/stop if the pin is configured
  // Start TIMER (If pin configured)
  if(analogPin != -1)
      nrfx_timer_enable(&timer4);

  // Re-initialize variables:
  sampleCounter = 0;
  lastBeatTime = 0; 
  peak = 512;
  trough = 512;
  thresh = 525;
  amplitude = 100;
  IBI = 600;
  pulse = false;
  pulseLost = true;
  beatCount = 0;
  postUpdate = false;
}

void PulseSensorAmpedClass::stop(void) {
  // Stop measurements
  nrfx_timer_disable(&timer4);
  postUpdate = false;
}



void PulseSensorAmpedClass::update() {              // Update this ever 2ms
  static unsigned rate[10];                         // array to average IBI values for average rate
  static unsigned beatCount = 0;

  if(fakeData) {
    // Send an update once per second
    if(beatCount >= 500) {
       if(random(100)<2) {
         BPM = -1;
       } else {
        IBI = random(770,1100);
        BPM = 60000/IBI;        
       }
       postUpdate = true;
       beatCount = 0;
    }
    beatCount++;
    return;
  }

  static unsigned int signalFilter[5];
  static unsigned int filterIndex = 0;
  signalFilter[filterIndex] =  HAL_ADC_Read(analogPin);
  filterIndex = (filterIndex+1)%5;
  int signal = (signalFilter[0] + signalFilter[1] + signalFilter[2] + signalFilter[3] + signalFilter[4])/5;

  sampleCounter += 2;                          // keep track of the time in mS with this variable

  // For debugging of signal
  // Serial.printf("%d,%d,%d,%d,%d\n",signal,peak,trough,thresh, postUpdate?2000:1000);
  //Serial.printf("%d\n",thresh-trough);
  unsigned elapsedTime = sampleCounter - lastBeatTime;  // Time passed since the last beat
  boolean beyondDicrotic = elapsedTime > (IBI/5)*3;    // Has sufficient time passed to avoid the dichrotic noise?
 
  //  find the peak and trough of the pulse wave
  if(signal < thresh) {         // Update trough based on threshold
    if(beyondDicrotic) {       // avoid dicrotic noise when finding trough
      trough = min(signal, trough);
    } 
  } else {                      // Signal is > threshold;  Potentially update peak
    peak = max(signal, peak);  
  }                                        

  // Search for a beat
  if(elapsedTime > 250){                         // Assume at least 250ms between beats (i.e., BPM<240); Helps avoid noise
    // See if the signal indicates the beginning of a pulse phase
    if((signal > thresh) && (pulse == false) && beyondDicrotic) {        
      // A pulse phase has started 
      pulse = true;

      IBI = sampleCounter - lastBeatTime;         // measure time between beats in mS (Starting from point the threshold is exceeded)
      lastBeatTime = sampleCounter;               // keep track of the start time of this beat

      // Add the count to the buffer
      rate[beatCount%10] = IBI;

      // Assuming this won't roll over (4Billion beats?)
      beatCount++;

      // If too few beats, discard them
      if(beatCount<3) {
        return;
      } else if(beatCount==3) {
        // First measurement is iffy. Average 2nd and 3rd
        rate[0]=(rate[1]+rate[2])/2;  
      }

      // Total the available beats
      word runningTotal = 0;
      int maxIndex = min(beatCount, 10);      
      for(int i=0; i<maxIndex; i++) {
        runningTotal += rate[i];              
      }
      runningTotal /= maxIndex;               // average the last 10 IBI values 
      BPM = 60000/runningTotal;               // how many beats can fit into a minute? that's BPM!

    }                       
  }

  if(signal < thresh && pulse == true) {      // when the values are going down the beat is over
    amplitude = peak - trough;                // Compute the amplitude of the last sample
    pulse = false;                            // Update status
    thresh = amplitude/2 + trough;            // Use 50% of the last amplitude as new threshold
    peak = thresh;                            // Peak won't update until beyond threshold
    trough = thresh;                          // Trough won't update until beyond threshold
  
    pulseLost = false;                      // Definitely have a valid pulse now
    // If minimum average and last amplitude appropriate, relay data
    if(amplitude>300)
      postUpdate = true;
   }

  if(elapsedTime > 2500) {                 // if 2.5S elapse without a valid beat
    if(!pulseLost) {                       // If it was good, notify the loss
      BPM = -1;
      postUpdate = true;
    }
    // Reset state variables to default state
    thresh = trough + (peak-trough)/3;  // set thresh default
    peak = signal;                   // set P default
    trough = signal;                 // set T default
    lastBeatTime = sampleCounter;    // bring the lastBeatTime up to date        
    pulseLost = true;
    beatCount = 0;
  }
}

void PulseSensorAmpedClass::process(void) {
  // Put updates into foreground
  if(postUpdate) {
    if(BPM>=0)
      PulseSensorAmped_data(BPM, IBI);
    else 
      PulseSensorAmped_lost();	         
    postUpdate = false;
  } 
}
