
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUZZER = A5;
const int PIN_ONBOARD_LED = D7;

unsigned long prevMillisLed = 0;
unsigned long prevMillisTone = 0;
const unsigned long INTERVAL_TONE = 1000;
const unsigned long INTERVAL_LED = 100;
boolean isLedOn = false;
boolean isToneOn = false;

#include "pitches.h"

int notes[] = {NOTE_C5, NOTE_G5, NOTE_F5, NOTE_C5, 0};  // what does 0 mean?
int beats[] = {4, 4, 8, 8, 8};
const int DURATION_MEASURE = 1600;  // 1

int pauseBetweenNotes = 0; //this will change every time
int noteIndex = 0;  //which note we are playing
/*
    music: we don't think in terms of freq and duration
        --> NOTES and BEATS

    for notes, just a file that maps frequency to notes

    music is divided into beats and measure

    four beats per measure --> four beats per measure (4 quarter notes)

    8th notes --> half as long as quarter notes -- 8 8th notes per measure

    half notes --> twice as long as quarter notes --2 half notes per measure

    how long is a measure? --> this is where TEMPO or BPM (beats per minutes)
*/

void playTone() {
    // tone(PIN, FREQ, DURATION)
    tone(PIN_BUZZER, 4000, 2000);  // play a 4k tone for 2 s
    delay(2000);
    tone(PIN_BUZZER, 1000, 5000);  // play 1k tone for 5 s
    delay(5000);

    /*
    tone() is NOT blocking -- what does this mean?
        the photon doesn't stop when we ask to play a tone
        BUT if we want to play a tone for a specific we need to use
            MILLIS or DELAY
    */
}

void playToneMillis() {
    /*
    goal: flash onboard led on/off every 100 ms
    AND   play a 4k tone for 1s, then off for 1s, and so on
    */
    unsigned long curMillis = millis();
    // led block
    if (curMillis - prevMillisLed > INTERVAL_LED) {
        prevMillisLed = curMillis;
        isLedOn = !isLedOn;  // inverts T -> F      F -> T
        if (isLedOn == true) {
            digitalWrite(PIN_ONBOARD_LED, HIGH);
        } else {
            digitalWrite(PIN_ONBOARD_LED, LOW);
        }
    }

    // tone block
    if (curMillis - prevMillisTone > INTERVAL_TONE) {
        prevMillisTone = curMillis;
        isToneOn = !isToneOn;
        if (isToneOn == true) {
            tone(PIN_BUZZER, 4000);  // no duration
        } else {
            noTone(PIN_BUZZER);
        }
    }
}

void playSongDelay() {
    // tone(PIN_BUZZER, NOTE_C4, 2000);
    // delay(2000);
    // tone(PIN_BUZZER, NOTE_G4, 3000);
    // delay(3000);
    for (int index = 0; index < arraySize(notes); index++) {
        int notePitch = notes[index];
        int noteTime = DURATION_MEASURE / beats[index];
        tone(PIN_BUZZER, notePitch, noteTime);
        delay(noteTime * 1.2);
    }
}

void playSongMillis() {
/*
    basically this is the same as the delay version EXCEPT 
        we can't use a for loop
    without FOR or DELAY, we need to manually play ONE note everytime 
        we go through this function
    --> we need a new var to track which note are we playing


*/
    unsigned long curMillis = millis();

    if(curMillis - prevMillisTone > pauseBetweenNotes) {
        prevMillisTone = curMillis;
        int notePitch = notes[noteIndex];
        int noteTime = DURATION_MEASURE / beats[noteIndex];
        pauseBetweenNotes = noteTime * 1.2;
        tone(PIN_BUZZER, notePitch, noteTime);

        noteIndex = noteIndex + 1;
        if (noteIndex >= arraySize(notes)) {
            noteIndex = 0;
        }
    }

}

// green - show how to play with millis
// red - create own song

// ********* ----------

void setup() {
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_ONBOARD_LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // playTone();
    // playToneMillis();
    // playSongDelay();
    playSongMillis();
}