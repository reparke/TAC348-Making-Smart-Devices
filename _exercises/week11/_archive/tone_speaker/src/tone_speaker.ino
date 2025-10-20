/* based on http://www.arduino.cc/en/Tutorial/Tone
 */
// #include "Servo.h"
#include "pitches.h"

unsigned long currentTime;  // for testing
int songChoice = 1;
const int PIN_SPEAKER = D2;
const int PIN_BUTTON = D3;

int pos = 0;  // variable to store the servo position

// notes in the melody:
int melody1[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3,
                 NOTE_G3, 0,       NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations1[] = {4, 8, 8, 4, 4, 4, 4, 4};

int maxNote = melody1[0];
int minNote = melody1[0];
void setup() {
  pinMode(PIN_SPEAKER, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);

  for (int i = 0; i < arraySize(melody1); i++) {
    if (melody1[i] > maxNote) {
      maxNote = melody1[i];
    }
    if (melody1[i] < minNote) {
      minNote = melody1[i];
    }
  }
}

void loop() {
  // updateSnooze();
  unsigned long curTime = millis();
  currentTime = curTime;
  // tone(PIN_SPEAKER, 2000, 500);
  int val = digitalRead(PIN_BUTTON);
  Serial.println("button: " + String(val));

  if(val == LOW) {
    tone(PIN_SPEAKER, 4000, 0);
  }
  // delay(1000);
  // playSong("");
}

int playSong(String input) {
  Serial.println("Inside play song");
  // iterate over the notes of the melody:
  if (songChoice == 1) {
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      // to calculate the note duration, take one second
      // divided by the note type.
      // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations1[thisNote];
      tone(PIN_SPEAKER, melody1[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(PIN_SPEAKER);
    }
  }
}
