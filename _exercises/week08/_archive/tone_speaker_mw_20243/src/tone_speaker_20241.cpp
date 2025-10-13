
#include "Particle.h"
#include "pitches.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUZZER = A5;

unsigned long prevMillis = 0;
const int TONE_INTERVAL = 1000;
bool toneOn = false;

/*
    for music, we don't think in terms of freq and duration
        --> notes and length

    length
    -
    music is divided into beats

    four beats per measure --> quarternote
        four quarter notes in a measure

    eighth notes --> half as long as quarter notes
        8  8th notes in  measure 

    half notes -> twice as long as quarter notes
        --> 2 half notse per measure 

    notes
    -
    we use a "lookup table" which converts musical notes (AKA notes on piano) 
        into actual frequencies
*/

/*
    a song is a collection of notes and lengths in order

    --> we can use an array (list) to store all the notes
            and another array to store the lengths
*/


//lets define an array for the notes
int notes[] =   {NOTE_C5, NOTE_G5, NOTE_D4, NOTE_F5, 0};
//define array for duration using quater notes, 8th notes, etc
int duration[] = {  4,       4,      4,        2,     1};

void playSong() {
//     tone(PIN_BUZZER, NOTE_C4, 1000);
//     delay(2000);
//     tone(PIN_BUZZER, NOTE_G5, 500);
//     delay(2000);
    // a c++ for loop is similar to "range based for loop" in python
    //      for loop that is based on a counter
    for(int index = 0; index < arraySize(notes); index = index + 1) {
        //we need the duration
        //we are going to assume that 1 measure is 1 second
        int noteLength = 1000 / duration[index];
        tone(PIN_BUZZER, notes[index], noteLength);
        delay(noteLength * 1.3);

    }

}

void playBasicTone() {
    // syntax is tone(PIN, FREQ, DURATION) duration is optional
    tone(PIN_BUZZER, 2000, 1000);  // 2 KHz for 1000
    delay(3000);
    tone(PIN_BUZZER, 4000, 500);  // 4 KHz for 1/2 sec
    delay(3000);

    /*
        the TONE function is non-blocking (hint: delay is blocking)
        if we want a tone to play for a specific amount of time, we need to use
        millis or delay
    */
}

void playBasicToneMillis() {
    unsigned long currMillis = millis();

    if (currMillis - prevMillis > TONE_INTERVAL) {
        prevMillis = currMillis;
        // we are going to turn a tone on and off (just like we turn a LED on
        // and off)
        if (toneOn == false) {       // no tone is playing
            tone(PIN_BUZZER, 4000);  // no duration--this will play FOREVER
            toneOn = true;
        } else {                 // tone IS playing
            noTone(PIN_BUZZER);  // stop the tone playing
            toneOn = false;
        }
    }
}

void setup() {
    pinMode(PIN_BUZZER, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // playBasicTone();
    // playBasicToneMillis();
    playSong();
}