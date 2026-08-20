
const int NSRed = D2;
const int NSYel = D3;
const int NSGrn = D4;
const int WERed = A0;
const int WEYel = A1;
const int WEGrn = D5;
const int WALK = D6;
const int DONTWALK = D7;

const int GO_TIME = 5000;          // time for green, red, walk, don't walk
const int TRANSITION_TIME = 1000;  // time for yellow
const int BLINK_RATE = 500;        // time for blinking don't walk light

// for testing purposes onle
int lights[] = {NSRed, NSYel, NSGrn, WERed, WEYel, WEGrn, WALK, DONTWALK};

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(NSRed, OUTPUT);
  pinMode(NSYel, OUTPUT);
  pinMode(NSGrn, OUTPUT);
  pinMode(WERed, OUTPUT);
  pinMode(WEYel, OUTPUT);
  pinMode(WEGrn, OUTPUT);
  pinMode(WALK, OUTPUT);
  pinMode(DONTWALK, OUTPUT);
}
void loop() {
  // test all lights -- delete once wiring is verified
  turnAllLightsOn();
  delay(2000);
  turnAllLightsOff();
  cycleLights(500);
}

/* ======= FUNCTIONS =========== */
//TODO: COMPLETE
void setLight() {
  digitalWrite(NSRed, LOW);
  digitalWrite(NSYel, LOW);
  digitalWrite(NSGrn, LOW);
  digitalWrite(WERed, LOW);
  digitalWrite(WEYel, LOW);
  digitalWrite(WEGrn, LOW);
  digitalWrite(WALK, LOW);
  digitalWrite(DONTWALK, LOW);
}

//TODO: COMPLETE getNextState


//TODO: COMPLETE getNextStateDuration



/* ======= FUNCTIONS FOR DEBUGGING LED WIRING ========= */
// functions used for testing only
void cycleLights(int delayMS) {
  for (int i = 0; i < arraySize(lights); i++) {
    digitalWrite(lights[i], HIGH);
    delay(delayMS);
    digitalWrite(lights[i], LOW);
  }
}

void turnAllLightsOn() {
  for (int i = 0; i < arraySize(lights); i++) {
    digitalWrite(lights[i], HIGH);
  }
}

void turnAllLightsOff() {
  for (int i = 0; i < arraySize(lights); i++) {
    digitalWrite(lights[i], LOW);
  }
}