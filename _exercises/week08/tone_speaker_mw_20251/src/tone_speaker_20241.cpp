
#include "Particle.h"
#include "pitches.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUZZER = A5;
const int PIN_LED = D7; //on board LED

unsigned long prevMillisTone = 0;
unsigned long prevMillisLed = 0;

boolean isLedOn = false;
boolean isToneOn = false;

//create an array store the notes (list in python)
int melody[] =   {NOTE_C5, NOTE_G5, NOTE_F5, NOTE_C5, 0};
int duration[] = {4,        4,       8,        2,     2};

/*
    music: don't think of frequency and duration
        --> notes and beats

    notes: think notes on a piano -- C F Bb 

    beats:

        music is divided into beats

        four beats is a measure --> quarter notes --> four quarters in a measure

        eighth notes --> half as long as quarter notes --> 8 8th notes per measure

        half notes --> twice as long as quarter --> 2 half notes per measure 

        songs have a BPM (beats per minute)
*/

void simpleTones() {
/*
    play a tone with tone()
    tone() is non-blocking -- does not pause / delay
    therfore code can continue

    --> if we want to play a tone for a specific duration, we either need
        millis timer   OR    delay
*/
    tone(PIN_BUZZER, 2000, 1000);       //play 2 khz tone for 1 sec
    // delay(1000);
    tone(PIN_BUZZER, 4000, 3000);       //play 4 khz tone for 3 sec
    // delay(3000);

    //without delay, the tone duration is unreliable and inconsistent

}

void simpleToneMillis() {
    unsigned long curMillis = millis();

    // //have led flash every 0.1s and the tone to play every 1 sec
    if(curMillis - prevMillisLed > 100) {
        prevMillisLed = curMillis;
        isLedOn = !isLedOn;     //flips true->false, and false->true
        if(isLedOn == true) {
            digitalWrite(PIN_LED, HIGH);
        }
        else {
            digitalWrite(PIN_LED, LOW);
        }
    }

    if (curMillis - prevMillisTone > 1000) {
        prevMillisTone = curMillis;
        isToneOn = !isToneOn;
        if (isToneOn == true) {//tone SHOULD start
            tone(PIN_BUZZER, 4000);     //we don't add a duration (3rd param)
            Serial.println("tone on");
        }
        else{       // tone SHOULD STOP
            noTone(PIN_BUZZER);
            Serial.println("tone off");
        }
    }

}

void playSongDelay() {
    // tone(PIN_BUZZER, NOTE_A4, 1000);
    // c++ for loop is basically a RANGE BASED for loop in python

    //start noteIndex at 0; continue as long as noteIndex < the melody size; 
    //              increase noteIndex by 1 each time
    for(int noteIndex = 0; noteIndex < arraySize(melody); noteIndex++) {
        //assumption: 1 measure takes 1 second
        int noteTime = 1000 / duration[noteIndex];
        tone(PIN_BUZZER, melody[noteIndex], noteTime);
        delay(noteTime * 1.3);
    }
}

//try creating your own array and playing a song--

//green check: how to build this song player with millis
//red x      : you can experiment with creating your own melody arrays based on                 existing songs online

void setup()
{
    Serial.begin(9600);
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_LED, OUTPUT);
}

void loop()
{
    //simpleTones();
    // simpleToneMillis();
    playSongDelay();
}