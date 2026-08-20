/*
    music: dont' think in frequency and seconds
                --> notes and beats

    music is divided in beats

    four beats per measure
        ---> quarter notes
        four quarter in a measure

    eighth note --> half as long as quarter note
        --> 8 8th notes per measure

    half notes --> twice as long as quarter
        --> 2 half notes per measure

    songs have BPM (beats per minute) aka tempo


*/
#include "pitches.h"

const int PIN_BUZZER = D2;
const int PIN_LED = D7;  // onboard led

unsigned long prevMillisTone = 0;
unsigned long prevMillisLed = 0;
bool ledState = false;
bool toneState = false;
int pauseBetweenNote = 0;  // change interval for our timer
int noteIndex = 0;         // current note in melody array we are playing

int melody[] = {NOTE_C5, NOTE_G5, NOTE_F5, NOTE_C5, 0};
int duration[] = {4, 4, 8, 2, 2};  // quarter, quarter, eighth, half

void setup() {
    Serial.begin(9600);
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_LED, OUTPUT);
}
void toneExamples() {
    // play tone
    // tone is NON-BLOCKING--does not pause / delay...therefore code continue
    // if we want to have a tone play for a specific duration, we nneed to
    // either
    //          use millis timer, or delay

    // tone(PIN_BUZZER, 5000);     //play forever
    tone(PIN_BUZZER, 2000, 1000);  // play 2k tone for 1s
    delay(1000);
    tone(PIN_BUZZER, 4000, 3000);  // play 4k tone for 3s
    delay(3000);
}
void toneWithMillis() {
    unsigned long currMillis = millis();
    // led to flash every 0.1s and a tone to play every 1s
    // led block
    if (currMillis - prevMillisLed > 100) {
        prevMillisLed = currMillis;
        ledState =
            !ledState;  // if (ledState == true){ ledSTate = false} else...
        digitalWrite(PIN_LED, ledState);
    }

    // tone block
    if (currMillis - prevMillisTone > 1000) {
        prevMillisTone = currMillis;
        toneState = !toneState;
        if (toneState == true) {     // we just turned on tone()
            tone(PIN_BUZZER, 4000);  // no duration
        } else {                     // we now want to turn off the tone
            noTone(PIN_BUZZER);
        }
    }
}
void playSong() {
    // DISCLAIMER: it is much preferable to use timer instead of a delay
    for (int index = 0; index < arraySize(melody); index = index + 1) {
        // lets just say that 1 measure is 1 second
        int noteTime = 1000 / duration[index];
        tone(PIN_BUZZER, melody[index], noteTime);
        delay(noteTime * 1.3);
    }
}
void playSongWithMillis() {
    unsigned long currMillis = millis();
    if (currMillis - prevMillisTone > pauseBetweenNote) {
        prevMillisTone = currMillis;
        int noteTime = 1000 / duration[noteIndex];
        tone(PIN_BUZZER, melody[noteIndex], noteTime);
        pauseBetweenNote = noteTime * 1.3;

        noteIndex = noteIndex + 1;
        if (noteIndex >= arraySize(melody)) {
            noteIndex = 0;
        }
    }
}
void loop() {
    // toneExamples();
    // toneWithMillis();
    // playSong();
    playSongWithMillis();
}
