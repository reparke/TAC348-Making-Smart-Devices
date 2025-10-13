/*
    for music, we don't think of freq and duration --> notes and beats / note
   length

    music divided into beats

    four beats per measure --> quarter notes
        four quarters in a measure

    eighth notes --> half as long as quarter note
        -> 8 8th notes in a measure

    half notes -> twice as long as quart
        --> 2 half notes in measure

    songs all have a beats per minute (BPM) - tempo


    what about frequencies?

*/
#include "Particle.h"
#include "pitches.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUZZER = A5;
const int PIN_LED = D7;  // onboard

unsigned long prevMillisTone = 0;
unsigned long prevMillisLed = 0;

bool ledOn = false;
bool toneOn = false;

// create two lists / arrays: one for the notes and one for the duration
// int notes[] = {NOTE_C5, NOTE_G5, NOTE_F5, NOTE_C5, 0};
// int duration[] = {4, 4, 8, 2, 2};
int notes[] = {NOTE_FS4, NOTE_E4,  NOTE_D4,  NOTE_CS4, NOTE_B3, NOTE_A3,
               NOTE_B3,  NOTE_CS4, NOTE_FS4, NOTE_E4,  NOTE_D4, NOTE_CS4,
               NOTE_B3,  NOTE_A3,  NOTE_B3,  NOTE_CS4, NOTE_D4, NOTE_CS4,
               NOTE_B3,  NOTE_A3,  NOTE_G3,  NOTE_FS3, NOTE_G3, NOTE_A3};
int duration[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

void basicTone() {
    // play tone
    // tone() is NON BLOCKING (unlike delay, our program doesn't stop while the
    // tone is playing) if you want a tone to play for a specific length, you
    // have to use delay or millis

    // syntax tone(PIN, FREQ, DURATION)
    // tone(PIN_BUZZER, 2000, 1000);  // play a 2000 Hz tone for 1 s
    // delay(1000);
    // tone(PIN_BUZZER, 4000, 500);  // play 4000 Hz for 0.5 s
    // delay(500);

    // try removing delays
    //  tone(PIN_BUZZER, 2000, 1000);  // play a 2000 Hz tone for 1 s
    //  tone(PIN_BUZZER, 4000, 500);  // play 4000 Hz for 0.5 s

    tone(PIN_BUZZER, 1000);  // plays forever

    // later on stop tone with
    noTone(PIN_BUZZER);
}

void basicToneWithMillis() {
    // flash a LED on and offevery 100ms
    // play a 4khz tone for 1s then off for 1s and repeat
    unsigned long curMillis = millis();

    // led
    if (curMillis - prevMillisLed > 100) {  // timer went off
        prevMillisLed = curMillis;          // reset
        if (ledOn == true) {
            ledOn = false;
            digitalWrite(PIN_LED, HIGH);
        } else {  // led is currethly OFF
            ledOn = true;
            digitalWrite(PIN_LED, LOW);
        }
    }

    // tone
    if (curMillis - prevMillisTone > 1000) {
        prevMillisTone = curMillis;
        toneOn = !toneOn;  // flips true -> false, and false -> true
        if (toneOn == true) {
            tone(PIN_BUZZER, 4000);
        } else {
            noTone(PIN_BUZZER);
        }
    }
}

void playSongWithDelay() {
    // tone(PIN_BUZZER, NOTE_C4, 1000);
    // delay(1000);
    // tone(PIN_BUZZER, NOTE_G5, 500);
    // delay(500);

    // build a for loop to iterate over all the indices of our arrays
    for (int index = 0; index < arraySize(notes); index = index + 1) {
        // calculate how a long is --> convert from "Quarter note" to actual
        // milliseconds
        int noteTime = 1000 / duration[index];  // ex: 1 second / 4 --> quarter
                                                // note will play for 1/4 sec
        tone(PIN_BUZZER, notes[index], noteTime);
        delay(noteTime * 1.3);
    }
}

void setup() {
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // basicTone();
    // basicToneWithMillis();
    playSongWithDelay();
}