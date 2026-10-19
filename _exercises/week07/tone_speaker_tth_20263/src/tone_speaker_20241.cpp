

#include "Particle.h"
#include "pitches.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUZZER = A5;
const int PIN_BUILT_IN_LED = D7;  // already on board, by USB cable

unsigned long prevMillisBuzzer = 0;
const unsigned long INTERVAL_BUZZER = 1000;
unsigned long prevMillisLed = 0;
const unsigned long INTERVAL_LED = 100;

bool isLedOn = false;
bool isBuzzerOn = false;  // state var

// C++ array
int notes[] = {NOTE_C4, NOTE_G5, NOTE_F5, NOTE_C4,
               0};              // what is 0? silence /rest
int beats[] = {4, 4, 8, 8, 8};  // note "duration"

// if beats are parts of measure, then how long is a measure?
const int MEASURE_TIME = 1000;  // 1 measure lasts for 1 sec

int noteIndex = 0;
int timeBetweenNotes = 0;  // this is not a constant value

/*

freq and duration

music: we don't think in terms of freq and duration
    --> NOTES (freq)  and BEATS (duration)

for notes, just use a file that maps frequency to musical notes
    "pitches.h"

for beats

music is divided into beats and measure

    how long is a measure? this is where TEMPO and BPM (beats per minute) are
used
        --> we can set in our code how long a measure

    four "beats" per measure --> 4 quarter notes

    8th notes -> half as long as quarter -- eight 8th notes per measure

    half notes -> twice as long as quarter -- two half notes per measure
*/

void playSongMillis() {
    /*
        basically the same as the delay version EXCEPT we can't a for loop

        w/o FOR or DELAY, we need to manually play ONE note every time we call
       this func --> we need a way to track which note we are on
    */
    unsigned long currMillis = millis();
    if (currMillis - prevMillisBuzzer > timeBetweenNotes) {
        prevMillisBuzzer = currMillis;
        int notePitch = notes[noteIndex];
        int noteTime = MEASURE_TIME / beats[noteIndex];

        timeBetweenNotes = noteTime * 1.2;  // this allows us to have variablle
                                      // intervals for our millis timer
        tone(PIN_BUZZER, notePitch, noteTime);

        // we need to update/track the index
        noteIndex = noteIndex + 1;
        if (noteIndex >= arraySize(notes)) {
            noteIndex = 0;
        }
    }
}

void playSongDelay() {
    // tone(PIN_BUZZER, NOTE_C4, 2000);  //now we can use the pitches.h
    // how should we store the notes in our melody? --> array (list)
    // how do we easily process an array / list? --> for loop

    // in c++, a for loop is what might be called a range-based for
    // syntax: for (initialize temp var;  stopping condition ;  increment)

    // ex: if we want to count to 10
    //  for (int counter = 0; counter <= 10; counter = counter +1){
    //      Serial.println(counter);
    //  }
    for (int index = 0; index < arraySize(notes); index = index + 1) {
        int notePitch = notes[index];  // get pitch at current index
        int noteTime = MEASURE_TIME / beats[index];
        tone(PIN_BUZZER, notePitch, noteTime);
        delay(noteTime);
    }
}

// green check - walk through play song with millis
// red x - you try making your song

void playToneDelay() {
    // syntax: tone(PIN, FREQ, DURATION)   * duration is optional
    //  tone(PIN_BUZZER, 4000, 2000);  //4000 Hz (4 KHz) for 2 s
    //  tone(PIN_BUZZER, 1000, 5000);  // 1 Khz tone for 5 s

    /*
        tone is NOT blocking -- what does this mean?
            --> photon does not stop when we ask to play a tone

        ===> we need to use millis or delay whenever we want a tone to play
        for a specific amount of time

    */
    tone(PIN_BUZZER, 4000, 2000);  // 4000 Hz (4 KHz) for 2 s
    delay(2000);
    tone(PIN_BUZZER, 1000, 5000);  // 1 Khz tone for 5 s
    delay(5000);

    // downside: delay blocks us from multitasking
}

void playToneMillis() {
    /*
    goal: flash built-in led on/off every 100ms
        AND play a 4k tone for 1s, stop playing for 1 s, and repeat

        hint: tone(PIN, FREQ) with no duration
         AND  noTone(PIN) to stop playing
    */
    unsigned long currMillis = millis();
    // led block
    if (currMillis - prevMillisLed > INTERVAL_LED) {
        prevMillisLed = currMillis;
        isLedOn = !isLedOn;     // flips true -> false; and false -> true
        if (isLedOn == true) {  // led is on
            digitalWrite(PIN_BUILT_IN_LED, HIGH);
        } else {  // led is off
            digitalWrite(PIN_BUILT_IN_LED, LOW);
        }
    }

    // tone block
    if (currMillis - prevMillisBuzzer > INTERVAL_BUZZER) {
        prevMillisBuzzer = currMillis;
        isBuzzerOn = !isBuzzerOn;
        if (isBuzzerOn == true) {
            tone(PIN_BUZZER, 4000);  // no duration so tone plays forever
        } else {                     // now is time to stop the buzzer
            noTone(PIN_BUZZER);
        }
    }
}

void setup() {
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_BUILT_IN_LED, OUTPUT);
    Serial.begin(9600);
}
void loop() {
    playSongMillis();
    // playSongDelay();
    // playToneMillis();
    // playToneDelay();
}