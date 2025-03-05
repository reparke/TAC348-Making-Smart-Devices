
#include "Particle.h"
#include "pitches.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUZZER = A5;
const int PIN_LED = D7;  // on board / built in LED

unsigned long prevMillisTone = 0;
unsigned long prevMillisLed = 0;

boolean isLedOn = false;
boolean isToneOn = false;

const unsigned long INTERVAL_LED = 100;
const unsigned long INTERVAL_TONE = 1000;

int noteIndex = 0; //track which note of the melody we are on

int pauseBetweenNote = 0;   //start at 0, but change with every note

//note array
int notes[] =     {NOTE_C5, NOTE_G5, NOTE_F5, NOTE_C5, 0};  
int durations[] = {4,          4,        8,    8,      2};
/*
    music: we don't think in terms of freq and duration
        --> notes and beats

    notes 

    beats

    music is divided into beats

    four beats in a measure --> quarter notes (4 quarters in a measure)

    8th notes --> half as long as quarter notes
            --> 8 - 8th notes per measures

    half notes --> twice as long as quater note
            --> 2 half notes per measure

    songs have a BPM (beats per minute)
*/

void playTones() {

    // tone(PIN_BUZZER, 4000); //generate a tone at 4 KHz for ever!
    /*
        tone() function is NOT blocking (e.g. delay IS BLOCKING)
            --does not pause or delay our code
        BUT if we want to play a tone for specific duration and then have it stop
            we need to EITHER use millis OR delay
    */
   tone(PIN_BUZZER, 4000, 1000);        //play 4 khz tone for 1 sec
//    delay(1000);
   tone(PIN_BUZZER, 2000, 5000);        // play 2 Khz for 5 seconds
//    delay(5000);

}

void playTonesMillis() {
    //goal: flash led on/off every 100ms 
    // and play a 4khz tone for 1 sec, off for 1 sec, on for 1 sec...
    unsigned long curMillis = millis();
    //led block
    if (curMillis - prevMillisLed > INTERVAL_LED) {
        prevMillisLed = curMillis;
        isLedOn = !isLedOn; //turns true -> false, and false -> true
        if(isLedOn == true) {
            digitalWrite(PIN_LED, HIGH);
        }
        else {
            digitalWrite(PIN_LED, LOW);
        }
    }

    //tone block
    if(curMillis - prevMillisTone > INTERVAL_TONE) {
        prevMillisTone = curMillis;
        isToneOn = !isToneOn;
        if(isToneOn == true) {      //we want the tone to start playing
            tone(PIN_BUZZER, 4000);     //we don't include a duration
        }
        else {
            noTone(PIN_BUZZER);     //stop playing
        }
    }
}

void playSongDelay() {
    
    // tone(PIN_BUZZER, NOTE_C4)
    // tone(PIN_BUZZER, NOTE_F4)

    //lets create an array to store all the notes
    //  and an array to store all the beat duration
    for (int index = 0; index < arraySize(notes); index++) {
        //lets say that 1 measure is 1 sec
        int noteTime = 1000 / durations[index];
        tone(PIN_BUZZER, notes[index], noteTime);
        delay(noteTime * 1.2); //1.2 is not magic, you can adjust to your liking
    }

}

void playSongMillis() {
    //this code is basically the same as using delay
    //  EXCEPT we can't use a for loop
    //  without a for loop and delay, we need to manually play ONE note everytime we 
    //                              go through void loop()
    // we need a NEW VAR to track which note (index) we are on
    
    //try on your own to play one note of the song each time through

    unsigned long curMillis = millis();
    //for a melody, the INTERVAL might change
    // so one idea is that the interval is dynamic and changes based on the note duration
    if(curMillis - prevMillisTone > pauseBetweenNote){
        prevMillisTone = curMillis;
        int noteTime = 1000 / durations[noteIndex];
        tone(PIN_BUZZER, notes[noteIndex], noteTime);

        pauseBetweenNote = noteTime * 1.3;

        //update our index
        noteIndex = noteIndex + 1; //noteIndex++;
        if (noteIndex >= arraySize(notes)) {
            noteIndex = 0;
        }
    }

}

void setup() {
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // playTones();
    // playTonesMillis();
    // playSongDelay();
    playSongMillis();
}


/*
    green check: show how to build melody with millis()
    red x:       you can create your own melody from existing songs online
*/