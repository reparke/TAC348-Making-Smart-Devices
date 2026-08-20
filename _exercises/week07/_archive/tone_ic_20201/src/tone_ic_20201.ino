#include "pitches.h"

const int PIN_SPEAKER = D2;

int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3,
                NOTE_G3, 0,       NOTE_B3, NOTE_C4};

int duration[] = {4, 8, 8, 4, 4, 4, 4, 4}; //4 is quarter note, 8 is an eighth note
// quarter note is TWICE as long as eighth 

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(PIN_SPEAKER, OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // // The core of your code will likely live here.
  // tone(PIN_SPEAKER, NOTE_C4, 500);
  // delay(500);
  // tone(PIN_SPEAKER, NOTE_E4, 1000);
  // delay(500);
  // tone(PIN_SPEAKER, NOTE_G4, 500);
  // delay(250);

  for (int i = 0; i < arraySize(melody); i++) {
    //look at duration
    //if you're using actual time in ms
    // int noteDuration = duration[i];

    int noteDuration = 1000 / duration[i];  //relative measure of time length

    tone(PIN_SPEAKER, melody[i], noteDuration);
    Serial.println("note: " + String(melody[i]));

    int pauseBetweenNotes = noteDuration * 1.3;  // 1.3 is just an value we got through experimentation'
    delay(pauseBetweenNotes);

    // noTone(PIN_SPEAKER);  //preventative for making sure tone stops
  }
  delay(1000);
}

