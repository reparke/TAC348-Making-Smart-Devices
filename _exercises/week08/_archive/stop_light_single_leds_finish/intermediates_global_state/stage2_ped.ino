
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

// stage 1: NS state changes
unsigned long prevMillisState = 0;
unsigned long stateLength = 0;
// enum State { NSG, NSY, NSR }; //stage 2: add pedestrians
enum State { NSG, NSY, PED, PEDDW };
State currentState = NSG;

void setup() {
  Serial.begin(9600);
  pinMode(NSRed, OUTPUT);
  pinMode(NSYel, OUTPUT);
  pinMode(NSGrn, OUTPUT);
  pinMode(WERed, OUTPUT);
  pinMode(WEYel, OUTPUT);
  pinMode(WEGrn, OUTPUT);
  pinMode(WALK, OUTPUT);
  pinMode(DONTWALK, OUTPUT);
}

/* ======== FUNCTIONS =========== */
// stage 1: create function with NSY NSR NSG
void updateNextState() {
  switch (currentState) {
    case NSY:
      // return NSR; //stage 2
      currentState =  PED;
    case PED:        // stage 2
      currentState =  PEDDW;  // stage 2
    // case NSR:    //stage 2
    case PEDDW:
      currentState =  NSG;
    case NSG:
      currentState =  NSY;
  }
}
// stage 1: time for NSY and then NSR NSG
void updateNextStateDuration() {
  switch (currentState) {
    case NSY:
    case PEDDW:  // stage 2
      stateLength =  TRANSITION_TIME;
    default:
      stateLength =  GO_TIME;
  }
}
// stage 1: add state parameter; add
void setLight(State s) {
  digitalWrite(NSRed, LOW);
  digitalWrite(NSYel, LOW);
  digitalWrite(NSGrn, LOW);
  digitalWrite(WERed, LOW);
  digitalWrite(WEYel, LOW);
  digitalWrite(WEGrn, LOW);
  digitalWrite(WALK, LOW);
  digitalWrite(DONTWALK, LOW);
  // stage 1: add switch statement
  switch (s) {
    case NSY:
      digitalWrite(NSYel, HIGH);
      digitalWrite(DONTWALK, HIGH);  // stage 2
      break;
    // case NSR:                    //stage 2
    case PED:
      digitalWrite(WALK, HIGH);
      digitalWrite(NSRed, HIGH);

      break;
    case PEDDW:
      digitalWrite(DONTWALK, HIGH);
      digitalWrite(NSRed, HIGH);

      break;
    case NSG:
      digitalWrite(NSGrn, HIGH);
      digitalWrite(DONTWALK, HIGH);
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
    updateNextState();
    updateNextStateDuration();
    setLight(currentState);
  }
}
