
#include "Particle.h"
#include "pitches.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUZZER = A5;
const int PIN_ONBOARD_LED = D7;  // little light by the USB cable

unsigned long prevMillisTone = 0;
unsigned long prevMillisLed = 0;
const unsigned long INTERVAL_LED = 100;
const unsigned long INTERVAL_TONE = 1000;
boolean isLedOn = false;
boolean isToneOn = false;

#include "pitches.h"

//note array - all the notes in our song
int notes[] =     {NOTE_C5, NOTE_G5, NOTE_F5, NOTE_C5, 0}; //what is 0?
int durations[] = {   4,      4,       8,        8,    2}; 

//song
int noteIndex = 0;      //track which note we are on
int pauseBetweenNotes = 0;  //change for each time

/*
music: we don't think in terms of freq and duration
    4k tone for 1 sec
    --> NOTES and BEATS

    notes are pitches

    beats 

    music is divided into beats

    four beats in a measure --> quarter notes (4 quarters in 1 measure)

    8th notes --> half as long as quarters -- 8 8th notes per measure

    half notes --> twice as long as quarters -- 2 half notes in per measure

    songs have a tempo or beats per minute BPM

*/

void playTones() {
    /*
        tone() is NOT blocking (unlike delay() which is BLOCKING)
            --tone() does NOT pause or stop or delay our code
        BUT if we need to play a tone for a specific duration and then have it
       stop we need to either use MILLIS or DELAY
    */

    // simple way to make a tone
    tone(PIN_BUZZER, 4000, 1000);  // play 4khz tone for 1000ms or 1 s
    delay(1000);
    tone(PIN_BUZZER, 2000, 5000);  // play 2 khz tone for 5 s
    delay(5000);
}

void playTonesMillis() {
    /*  goal: flash an led on/off every 100 ms
              AND play 4 khz tone on for 1 sec, off for 1 sec, etc...
        what var do we need?
            curMillis
            prevMillisTone
            INTERVAL_TONE
            isToneOn

            INTERVAL_LED
            prevMillisLed
            isLedOn
    */
    unsigned long curMillis = millis();
    //led block
    if (curMillis - prevMillisLed > INTERVAL_LED) {
        prevMillisLed = curMillis;
        isLedOn = !isLedOn;  // invert boolean
        if (isLedOn == true) {
            digitalWrite(PIN_ONBOARD_LED, HIGH);
        }
        else
        {
            digitalWrite(PIN_ONBOARD_LED, LOW);
        }
    }

    //tone block
    if (curMillis - prevMillisTone > INTERVAL_TONE) {
        prevMillisTone = curMillis;
        isToneOn = !isToneOn;
        if (isToneOn == true) {
            tone(PIN_BUZZER, 4000);     //we don't specify a duration
                                        //this will play forever until we stop it
        }
        else {//now timer is up
            noTone(PIN_BUZZER);         //stops the tone

        }
    }
}

void playSongDelay() {
    // tone(PIN_BUZZER, NOTE_C4);
    // delay(1000);
    // tone(PIN_BUZZER, NOTE_G5);
    // delay(2000);

    //we have one array for notes and one array for duration
    for (int index = 0; index < arraySize(notes); index++ ) {
        // we are arbitrarily saying 1 measure is 1 sec or  1000ms
        int noteTime = 1000 / durations[index];
        int notePitch = notes[index];
        tone(PIN_BUZZER, notePitch, noteTime);
        delay(noteTime * 1.2);
    }

}

void playSongMillis() {
/*
    this is basically the same as above with delay
        EXCEPT we can't a for loop
    without FOR and DELAY, we need to manually play ONE note
        everytime we go through void loop()
    
    --> we need a new var to track which note we are on
*/
    unsigned long curMillis = millis();
    if (curMillis - prevMillisTone > pauseBetweenNotes) {
        prevMillisTone = curMillis;

        int noteTime = 1000 / durations[noteIndex];
        int notePitch = notes[noteIndex];
        tone(PIN_BUZZER, notePitch, noteTime);
        pauseBetweenNotes =  noteTime * 1.2;

        //update index
        noteIndex = noteIndex + 1;
        if (noteIndex >= arraySize(notes)) {
            noteIndex = 0;
        }
    }

}


/*
    green check - play song with millis timer instead of delay
    red x       - you create your own song array
*/

void setup() {
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_ONBOARD_LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // playTones();
    // playTonesMillis();
    // playSongDelay();
    playSongMillis();
}