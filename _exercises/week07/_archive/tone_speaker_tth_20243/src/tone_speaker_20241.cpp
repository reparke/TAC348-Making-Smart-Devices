#include "Particle.h"
#include "pitches.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUZZER = A5;

unsigned long prevMillis = 0;
const unsigned long INTERVAL = 1000;
bool toneOn = false;

/*
    tone fn uses frequency and duration
    for music, we don't think of freq and duration
                ->              notes     lengths

    LENGTHS / DURATION

    music is divided into beat

    four beats in one measure --> quarter note
        four quarter notes in a measure

    eighth notes: --> half as long as quarter
        eighth 8th notes in a measure

    half notes --> twice as long as quarter notes
        2 half notes in a measure

    --
    NOTES / FREQUENCIES
        use pitches.h to convert freq to notes

        use array/list to store all the notes
        use another array to store the note lengths

    we are making an assumption --> 1 measure is 1 sec long

*/
// note array
int notes[] = {NOTE_C5, NOTE_G5, NOTE_F5, NOTE_C5, 0};
int lengths[] = {4, 3, 8, 2, 2};

void playSong() {
    // tone(PIN_BUZZER, NOTE_C4, 1000);
    // delay(2000);
    // tone(PIN_BUZZER, NOTE_G5, 500);
    // delay(100);

    // tip for python users: a c++ for loop is basically "range based for loop"
    for (int index = 0; index < arraySize(notes); index =    index + 1) {
        int currentNote = notes[index];
        int currentLength = 1000 / lengths[index];
        tone(PIN_BUZZER, currentNote, currentLength);
        delay(currentLength * 1.3); //add extra delay
    }
}

void playBasicToneMillis() {
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL) {
        prevMillis = currMillis;
        if (toneOn == false) {  // no sound is playing
            toneOn = true;
            tone(PIN_BUZZER, 1000);  // no duration!
                                     // this will play FOREVER!
        } else {  // sound is playing now
            toneOn = false;
            noTone(PIN_BUZZER);  // this stops the sound
        }
    }
}

void playBasicTone() {
    // basic syntax is tone(PIN, FREQ, DURATION) duration is optional
    //  doesn't play correctly because non-blocking
    //  tone(PIN_BUZZER, 2000, 1000);   //2000 Hz or 2KHz for 1000 ms or 1 sec
    //  tone(PIN_BUZZER, 4000, 500);    //4 KHz tone for 1/2 sec

    /*  tone fn is NON-BLOCKING
        delay   is BLOCKING

        when we use tone, we have to either use delay or use millis
    */

    tone(PIN_BUZZER, 2000, 1000);  // 2000 Hz or 2KHz for 1000 ms or 1 sec
    delay(2000);
    tone(PIN_BUZZER, 4000, 500);  // 4 KHz tone for 1/2 sec
    delay(1000);
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