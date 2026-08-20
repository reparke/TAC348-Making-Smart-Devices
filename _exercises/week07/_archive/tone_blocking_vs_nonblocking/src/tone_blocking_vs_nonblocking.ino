#include "pitches.h"

const int PIN_BUZZER = D2;
const int PIN_LED = D7;

int melody[] = {NOTE_C6, NOTE_G6, NOTE_E6, NOTE_B5, NOTE_C6};
int duration[] = {4, 4, 4, 8, 8};
int noteIndex = 0;

unsigned long prevMillis = 0;
unsigned long prevMillisTone = 0;
bool ledState = false;
bool toneState = false;
void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);
}

// uses for loop
void toneBlockingExample1() {
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > 100) {
        prevMillis = currMillis;
        ledState = !ledState;
        digitalWrite(PIN_LED, ledState);
        Serial.println("LED is now " + String(ledState));
    }

    for (int index = 0; index < arraySize(melody); index = index + 1) {
        int noteTime = 1000 / duration[index];
        tone(PIN_BUZZER, melody[index], noteTime);
        delay(noteTime * 1.2);
    }
}

void toneNonBlockingExample() {
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > 100) {
        prevMillis = currMillis;
        ledState = !ledState;
        digitalWrite(PIN_LED, ledState);
        Serial.println("LED is now " + String(ledState));
    }
    if (currMillis - prevMillisTone > 500) {
        prevMillisTone = currMillis;
        toneState = !toneState;
        if (toneState == HIGH) {
            tone(PIN_BUZZER, NOTE_G5);
        } else {
            noTone(PIN_BUZZER);
        }
        Serial.println("\tTONE is now " + String(toneState));
    }
}

unsigned long pauseBetweenNotes = 0;

void toneNonBlockingExample2() {
    unsigned long currMillis = millis();

    if (currMillis - prevMillis > 100) {
        prevMillis = currMillis;
        ledState = !ledState;
        digitalWrite(PIN_LED, ledState);
        Serial.println("LED is now " + String(ledState));
    }
    // iterate over the notes of the melody:
    if (currMillis - prevMillisTone >= pauseBetweenNotes) {
        prevMillisTone = currMillis;

        // to calculate the note duration, take one second divided by the
        // note type.
        // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / duration[noteIndex];
        tone(PIN_BUZZER, melody[noteIndex], noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        pauseBetweenNotes = noteDuration * 1.30;

        noteIndex++;
        if (noteIndex >= arraySize(melody)) {
            noteIndex = 0;
        }
    }
}
void loop() {
    // toneNonBlockingExample();
    toneNonBlockingExample2();
    // toneBlockingExample1();
}