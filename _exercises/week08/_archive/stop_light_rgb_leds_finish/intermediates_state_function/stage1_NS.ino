
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

// stage 1: NS state changes
unsigned long prevMillisState = 0;
unsigned long stateLength = 0;
enum State { stateNSG, stateNSY, NSR };
State currentState = stateNSG;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_NS_RED, OUTPUT);
  pinMode(NSYel, OUTPUT);
  pinMode(NSGrn, OUTPUT);
  pinMode(PIN_WE_RED, OUTPUT);
  pinMode(WEYel, OUTPUT);
  pinMode(WEGrn, OUTPUT);
  pinMode(PIN_WALK, OUTPUT);
  pinMode(PIN_DONT_WALK, OUTPUT);
}

/* ======== FUNCTIONS =========== */
// stage 1: create function with NSY NSR NSG
State getNextState(State s) {
  switch (s) {
    case stateNSY:
      return NSR;
    case NSR:
      return stateNSG;
    case stateNSG:
      return stateNSY;
  }
}
// stage 1: time for NSY and then NSR NSG
int getNextStateDuration(State s) {
  switch (s) {
    case stateNSY:
      return SHORT_LIGHT_DURATION;
    default:
      return LONG_LIGHT_DURATION;
  }
}
// stage 1: add state parameter; add 
void setLight(State s) {
  digitalWrite(PIN_NS_RED, LOW);
  digitalWrite(NSYel, LOW);
  digitalWrite(NSGrn, LOW);
  digitalWrite(PIN_WE_RED, LOW);
  digitalWrite(WEYel, LOW);
  digitalWrite(WEGrn, LOW);
  digitalWrite(PIN_WALK, LOW);
  digitalWrite(PIN_DONT_WALK, LOW);
  //stage 1: add switch statement
  switch (s) {
    case stateNSY:
      digitalWrite(NSYel, HIGH);
      break;
    case NSR:
      digitalWrite(PIN_NS_RED, HIGH);
      break;
    case stateNSG:
      digitalWrite(NSGrn, HIGH);
      break;
  }
}

void loop() {
  // stage 1: NS state changes
  unsigned long curMillis = millis();  // current time

  if ((curMillis - prevMillisState) > stateLength) {
    // update state timer
    prevMillisState = curMillis;
    Serial.println("Changing State");
    currentState = getNextState(currentState);
    stateLength = getNextStateDuration(currentState);
    setLight(currentState);
  }
}

