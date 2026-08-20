
const int PIN_NS_RED = D2;
const int NSYel = D3;
const int NSGrn = D4;
const int PIN_WE_RED = A0;
const int WEYel = A1;
const int WEGrn = D5;
const int PIN_WALK = D6;
const int PIN_DONT_WALK = D7;

const int LONG_LIGHT_DURATION = 5000;          // time for green, red, walk, don't walk
const int SHORT_LIGHT_DURATION = 1000;  // time for yellow
const int BLINK_RATE = 500;        // time for blinking don't walk light

// for testing purposes onle
int lights[] = {PIN_NS_RED, NSYel, NSGrn, PIN_WE_RED, WEYel, WEGrn, PIN_WALK, PIN_DONT_WALK};

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(PIN_NS_RED, OUTPUT);
  pinMode(NSYel, OUTPUT);
  pinMode(NSGrn, OUTPUT);
  pinMode(PIN_WE_RED, OUTPUT);
  pinMode(WEYel, OUTPUT);
  pinMode(WEGrn, OUTPUT);
  pinMode(PIN_WALK, OUTPUT);
  pinMode(PIN_DONT_WALK, OUTPUT);
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
  digitalWrite(PIN_NS_RED, LOW);
  digitalWrite(NSYel, LOW);
  digitalWrite(NSGrn, LOW);
  digitalWrite(PIN_WE_RED, LOW);
  digitalWrite(WEYel, LOW);
  digitalWrite(WEGrn, LOW);
  digitalWrite(PIN_WALK, LOW);
  digitalWrite(PIN_DONT_WALK, LOW);
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