

#include "Particle.h"
#include "pitches.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUZZER = A5;
const int PIN_ONBOARD_LED = D7;  // always connnected to d7

unsigned long prevMillisLed = 0;
unsigned long prevMillisBuzzer = 0;

const unsigned long INTERVAL_LED = 100;
const unsigned long INTERVAL_BUZZER = 1000;

bool isLedOn = false;
bool isBuzzerOn = false;

// C++ array notation
int notes[] = {NOTE_C5, NOTE_G5, NOTE_F5, NOTE_C5,
               0};  // 0 silent (like a rest)
int beats[] = {4, 4, 8, 8, 8};
const int MEASURE_DURATION = 1000;

// playSongMillis variables
int noteIndex = 0;          // which note are we playing
int pauseBetweenNotes = 0;  // this will change each time

/*
music: we don't think in terms of freq and duration
    --> notes (freq)  and beats (duration)

for notes, that's easy
    there is a file called pitches.h

for beats

music is divided into BEATS and MEASURES

four beats per measure -> 4 quarters in one measusre

8th notes -> eight  8th notes per meaure --> half as long as a quarter

half notes -> 2 half notes per measure --> twice as long as a quarter

how long is a measure? -> this is where TEMPO or BPM (beats per minute)

*/

void playTone() {
    // tone function syntax
    // tone(PIN< FREQ, DURATION)
    //  tone(PIN_BUZZER, 4000, 2000); //play a 4000 Hz tone for 2 sec
    //  tone(PIN_BUZZER, 1000, 5000); //play 1 KHZ tone for 5 sec

    tone(PIN_BUZZER, 4000, 2000);  // play a 4000 Hz tone for 2 sec
    delay(2000);
    tone(PIN_BUZZER, 1000, 5000);  // play 1 KHZ tone for 5 sec
    delay(5000);

    /*
        tone() is NOT BLOCKING -- what does this mean
            the photon doesn't stop when we play a tone
            IF we want to play a tone for a specific amount of time,
                we need to use DELAY or millis timer
    */
}

void playToneMillis() {
    /*
    goal: flash onboard LED on/off every 100 ms
       AND play a 4k tone for 1 s, then off for 1 s, and so on

    hint: two version of tone
        tone(PIN, FREQ, DURATION)

        tone(PIN, FREQ) --> just keeps going forever
        noTone(PIN) --> stops the buzzing
    */
    unsigned long curMillis = millis();
    // led block
    if (curMillis - prevMillisLed > INTERVAL_LED) {
        prevMillisLed = curMillis;
        isLedOn = !isLedOn;  // flip LED state
        if (isLedOn == true) {
            digitalWrite(PIN_ONBOARD_LED, HIGH);
        } else {
            digitalWrite(PIN_ONBOARD_LED, LOW);
        }
    }

    // tone block
    if (curMillis - prevMillisBuzzer > INTERVAL_BUZZER) {
        prevMillisBuzzer = curMillis;
        isBuzzerOn = !isBuzzerOn;    // true -> false,  false -> true
        if (isBuzzerOn == true) {    // should play tone
            tone(PIN_BUZZER, 4000);  // no duration
        } else {                     // time to stop playing tone
            noTone(PIN_BUZZER);
        }
    }
}

void playSongDelay() {
    // want to play multiple notes--how should we store them? array (list)
    //    initital cond; boundary (when to stop) ;  increment
    for (int index = 0; index < arraySize(notes); index++) {
        int notePitch = notes[index];
        int noteDuration = MEASURE_DURATION / beats[index];
        tone(PIN_BUZZER, notePitch, noteDuration);
        delay(noteDuration * 1.2);
    }
}

void playSongMillis() {
    /*
    basically the same as the delay version EXCEPT we can't use for loop

    without FOR or DLEAY, we need to manually play ONE note everytime
        we go through the this function
        ==> we need a new var to track which we are one
    */
    unsigned long curMillis = millis();
    if (curMillis - prevMillisBuzzer > pauseBetweenNotes) {
        prevMillisBuzzer = curMillis;
        int notePitch = notes[noteIndex];
        int noteDuration = MEASURE_DURATION / beats[noteIndex];
        pauseBetweenNotes = noteDuration * 1.2;
        tone(PIN_BUZZER, notePitch, noteDuration);

        noteIndex = noteIndex + 1;
        if (noteIndex >= arraySize(notes)) {
            noteIndex = 0;
        }
    }
}

void setup() {
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_ONBOARD_LED, OUTPUT);
    Serial.begin(9600);
}
void loop() {
    playSongMillis();
    // playSongDelay();
    // playToneMillis();
    // playTone();
}