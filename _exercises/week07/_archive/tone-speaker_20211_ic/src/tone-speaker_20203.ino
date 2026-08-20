#include "pitches.h"

const int PIN_BUZZER = D2;

// int melody[] = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_E4};
// int duration[] = {4,      4,      4,        4,        4,      4};
int melody[] = {NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_F5, NOTE_C6,
                NOTE_AS5, NOTE_A5,  NOTE_G5,  NOTE_F6, NOTE_C6};
int duration[] = {8, 8, 8, 2, 2, 8, 8, 2, 4};

/*
  there are four "beats" in a "measure" music
  we will call each "beat" a quarter note --> 4
  ex: if a note is "half a beat" --> 4/2 --> 8
  these are fractions so large numbers mean shorter time
*/


void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  for (int i = 0; i < arraySize(melody); i++) {
    int noteTime = 1000 / duration[i];
    tone(PIN_BUZZER, melody[i], noteTime);
    
    int pauseTime = noteTime * 1.3;
    delay(pauseTime);
  }

  // //tone(PIN, FREQ, TIME)
  // tone(PIN_BUZZER, NOTE_C4, 500);
  // delay(500);
  // tone(PIN_BUZZER, NOTE_DS4, 500);
  // delay(500);

  // tone(PIN_BUZZER, NOTE_G4, 500);
  // delay(500);
}