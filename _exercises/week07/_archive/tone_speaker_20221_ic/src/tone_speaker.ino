#include "pitches.h"

const int PIN_SPEAKER = D2;

/* goal: is relate our code to musical notation
  frequency --> note
  time a note lasts (duration)

  one idea: lets do milliseconds

  music divided into beats

  four beats in one measure --> these are called quarter notes
    --> four quarters per measure

  half notes --> 2 per measure
  whole note --> 1 per measure

  a song has beats per minute (tempo or BPM)

  THESE ARE FRACTIONS!---> bigger notes are actually shorter (quarter note will
  play 25% as long as whole)
*/

/*
  store each note value in an array
  store each note duration is separate array (stored as "beat value" like 4, 2,
  1, 8)

*/

/*
Notes:
NOTE_C6
NOTE_G6
NOTE_E6
NOTE_B5
NOTE_C6

durations
4
4
4
8
8
*/

int melody[] = {NOTE_C6, NOTE_G6, NOTE_E6, NOTE_B5, NOTE_C6};
int duration[] = {4, 4, 4, 8, 8};

void setup() {
    Serial.begin(9600);
    pinMode(PIN_SPEAKER, OUTPUT);
}

void loop() {
    for (int i = 0; i < arraySize(melody); i++) {
        int noteTime = 1000 / duration[i];  // each note is some FRACTION of 1
                                            // sec (quarter is 1/4 sec = .25s)
        tone(PIN_SPEAKER, melody[i], noteTime);
        int delayTime = noteTime * 1.2; //1.2 is purely arbitrary  so adjust to what sounds good
        delay(delayTime);

    }
    //     tone(PIN_SPEAKER, NOTE_A4, 1000);
    //     delay(1000);
    //     tone(PIN_SPEAKER, NOTE_E5, 1000);
    //     delay(1000);
    //     tone(PIN_SPEAKER, NOTE_D5, 1000);
    //     delay(1000);

    // fixed duration
    //  tone(PIN_SPEAKER, 500, 1000);
    //  delay(1000);
    //  tone(PIN_SPEAKER, 1000, 1000);
    //  delay(1000);
    //  tone(PIN_SPEAKER, 2000, 1000);
    //  delay(1000);

    // tone(PIN_SPEAKER, 2000); // should play continuously
    // noTone(PIN_SPEAKER);   //stop playing
}
