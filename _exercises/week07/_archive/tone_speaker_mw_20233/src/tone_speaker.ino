/*

    frequencies --> notes (use pitches.h)

    time ?

    music is divided in beats
    four beats per measure --> quarter notes
        --> four quarter notes in a measure

    half note --> twice as long as quarter note
        two quarters in a measure
    eighthnotes --> half as long as quarter
        --> 8 per measure

    songs have BPM (beats per minute) aka tempo

    solution: lets have a array for the music notes, and array for the durations
*/
#include "pitches.h"

const int PIN_BUZZER = D2;
const int PIN_LED = D7;

unsigned long prevMillisLed = 0;
unsigned long prevMillisTone = 0;
unsigned long pauseBetweenNotes = 0;
int noteIndex = 0;  // track the currently playing note

bool ledState = false;
bool toneState = false;

// array for notes
int melody[] = {NOTE_C6, NOTE_G6, NOTE_E6, NOTE_B5, NOTE_C6};
int duration[] = {4, 4, 4, 8, 8};  // quarter quarter quarter eighth eighth

void toneWithMillis() {
    // goal - play tone every 1 sec, and flash led every 0.1 sec
    unsigned long currMillis = millis();
    // LED Block
    if (currMillis - prevMillisLed > 100) {
        prevMillisLed = currMillis;
        ledState = !ledState;  // another way to "flip" true to false, and false
                               // to true shortcut from having if(ledState ==
                               // true)... else ...
        digitalWrite(PIN_LED, ledState);
    }

    // tone block
    if (currMillis - prevMillisTone > 1000) {
        prevMillisTone = currMillis;
        toneState = !toneState;
        // to play tone
        if (toneState == true) {
            tone(PIN_BUZZER, NOTE_C4);  // no duration
        } else {
            noTone(PIN_BUZZER);  // stops the tone
        }
    }
}
void playSong() {
    // just for now, we're going to use delay (which is bad I know...)
    for (int index = 0; index < arraySize(melody); index = index + 1) {
        // play note and have a delay
        // to calculate the note time, we arbitrarily make the notes fractions
        // of 1 second we are saying a measure is one second
        int noteTime = 1000 / duration[index];
        tone(PIN_BUZZER, melody[index], noteTime);
        delay(noteTime * 1.30);  // adds a very short silence in between
    }
}

void playSongWithMillis() {
    // delay is blocking
    // tone is not blocking
    // we are used to having timers were the interval is always the same
    // but here, notes can be different lengths
    unsigned long currMillis = millis();
    if (currMillis - prevMillisTone > pauseBetweenNotes) {
        prevMillisTone = currMillis;
        int noteTime = 1000 / duration[noteIndex];
        tone(PIN_BUZZER, melody[noteIndex], noteTime);
        pauseBetweenNotes =
            noteTime * 1.3;  // this is exactly what we did before with DELAY

        noteIndex = noteIndex + 1;
        if (noteIndex >= arraySize(melody)) {
            noteIndex = 0;  //reset
        }
    }
}

void setup() {
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_LED, OUTPUT);
}

void loop() {
    // // tone funciton generate a tone
    // // TONE function is NON-BLOCKING (there's no delay)
    // // because TONE is nonblocking, we will need to use delay or millis if we
    // // want to have a "melody"
    // tone(PIN_BUZZER, 2000, 3000);  // 2000 Hz for 3s
    // delay(3000);
    // tone(PIN_BUZZER, 4000, 1000);  // 4000 Hz for 1s
    // delay(1000);
    // toneWithMillis();
    // playSong();
    playSongWithMillis();
}