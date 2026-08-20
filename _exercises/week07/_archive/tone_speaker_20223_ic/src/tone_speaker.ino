
/*
  frequency -->  note

  time a note laste (duration)

  let's try milliseconds

  music is divided into beats

  four beats in one measure --> quarter
    --> four quarter notes per measure

  half notes --> 2 per measure
  whole --> 1 per measure
  eighth --> 8 per measure

  song has a tempo (BPM)

  THESE ARE FRACTIONS --> bigger notes are actually shorter   
*/

#include "pitches.h"
const int PIN_BUZZER = D2;

int melody[] = {NOTE_C6, NOTE_G6, NOTE_E6, NOTE_B5, NOTE_C6};
int duration[] = {4, 4, 4, 8, 8};


void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {
  // // tone(PIN_BUZZER, 500);//500 Hz tone played constantly  
  // tone(PIN_BUZZER, NOTE_C4, 2000);  //play 1KHz tone for 2 seconds
  // delay(2000);
  // tone(PIN_BUZZER, NOTE_E4, 2000);
  // delay(2000);
  // tone(PIN_BUZZER, NOTE_G4, 2000);
  // delay(2000);

  for (int index = 0; index < arraySize(melody); index++) {
    //arbitrarily make notes fractions of 1 sec
    int noteTime = 1000 / duration[index];
    tone(PIN_BUZZER, melody[index], noteTime);
    delay(noteTime * 1.2);

    //if you need to respond to events (like button presses)
    //  need to add an if statement that checks for events 
    //  break;      --> automatically exit loop
  }

}