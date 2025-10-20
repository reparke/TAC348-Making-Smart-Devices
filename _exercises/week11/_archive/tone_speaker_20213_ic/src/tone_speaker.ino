#include "pitches.h"

int melody[] = {NOTE_C3, NOTE_G4, NOTE_G4, NOTE_C3, NOTE_F4, NOTE_F4};
// int duration[] = {...}; //millisecond
int duration[] = {4, 8, 8, 4, 4, 4}; //beats


/*
  there are four "beats" in "measure of music"
  we call these "quarter notes" --> 4
  if we have a note that is "half a beat" --> "eighth note" --> 8
  these are fractions so BIGGER numbers mean SHORTER time

  for (int i = 0; i < XXX; i++) {

  }

*/

const int PIN_BUZZER = D2;

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {
  for (int i = 0; i < arraySize(melody); i++ ) {
    int noteLength = 1000 / duration[i];
    tone(PIN_BUZZER, melody[i], noteLength);

    int pauseLength = noteLength * 1.3; //this ARBITRARY
    delay(pauseLength);

  }

}
