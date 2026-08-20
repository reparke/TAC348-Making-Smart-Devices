
#include "pitches.h"

const int PIN_BUZZER = D2;

//store a melody of notes
int melody[] = {NOTE_C6, NOTE_G6, NOTE_E6, NOTE_B5, NOTE_C6};
int duration[] = {4,      4,       4,        8,       8    };

/*
  there are four "beats" in a "measure" of music
  we call each beat a quarter note --> 4
  a note that is "half a beat" --> 4/2 --> 8
*/

void setup() {
  Serial.begin(9600);
  pinMode(PIN_BUZZER, OUTPUT);

}

//human hearing: 20 hz to 20000 hz
void loop() {

  for (int i = 0; i < arraySize(melody); i++) {
    int noteTime = 1000 / duration[i];    //each note is some FRACTION of 1 sec (quarter is 1/4 sec = .25s)

    tone(PIN_BUZZER, melody[i], noteTime);
    //need a pause between each note
    //the value we are going to use was found experimentally
    int pauseTime = noteTime * 1.00;
    delay(pauseTime);
  }

  // tone(PIN_BUZZER, NOTE_C6, 1000);
  // tone(PIN_BUZZER, 1000, 2000);
  // tone(PIN_BUZZER, 4000, 500);
  // tone(PIN_BUZZER, 1000, 2000);
  // tone(PIN_BUZZER, 500, 1000);

  delay(5000);

}