/*

  frequencies --> notes

  time

  music is divided into beats

  four beats  per meassure --> quarter
    --> four quarter notes per measure

  half note -> 2 half note per measure
  eighth notes --> 8 per measure 

  song has a tempo (Beats per minute)

  THESE NOTES ARE FRACTIONS! Bigger notes are shorter


*/

#include "pitches.h"

const int PIN_BUZZER = D2;

int melody[] =    {NOTE_C6, NOTE_G6, NOTE_E6, NOTE_B5, NOTE_C6};
int duration[] =  {4,       4,       4,       8,        8     };

void setup() { pinMode(PIN_BUZZER, OUTPUT); }

void loop() {
    // tone(PIN_BUZZER, 500, 2000);
    // delay(1000);               //tone is not blocking
    // tone(PIN_BUZZER, 3000, 1000);
    // delay(1000);

    // tone(PIN_BUZZER, NOTE_C4, 1000);
    // delay(1000);
    // tone(PIN_BUZZER, NOTE_F5, 500);
    // delay(500);
    // tone(PIN_BUZZER, NOTE_G5, 2000);
    // delay(2000);

  for (int index = 0; index < arraySize(melody); index = index + 1) {
    int noteTime = 1000/duration[index];
    tone(PIN_BUZZER, melody[index], noteTime);
    delay(noteTime*1.2);

    // if you needed to stop song before the end
    /*
      if buttonPress == LOW
        break;
    */
  }
}