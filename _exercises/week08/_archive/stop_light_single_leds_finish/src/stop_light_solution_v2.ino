// cf: http://siever.info/cse132/weeks/3/studio/
// this code is adapted from Bill Siever
// two lane stoplight and pedestrian walk light

// it uses a timing approach based on cur and prevMillis

const int NSRed = D2;
const int NSYel = D3;
const int NSGrn = D4;
const int WERed = A0;
const int WEYel = A1;
const int WEGrn = D5;
const int WALK = D6;
const int DONTWALK = D7;

const int GO_TIME = 5000;          // time for green, red, walk, don't walk
const int TRANSITION_TIME = 2000;  // time for yellow
const int BLINK_RATE = 500;        // time for blinking don't walk light

unsigned long prevMillisState = 0;
unsigned long prevMillisBlink = 0;

enum State { NSY, WEG, WEY, PED, PEDDW, NSG };
State currentState = NSG;

unsigned long stateLength = 0;

bool pedOn = true;    //controls LED blinking for don't walk
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

  digitalWrite(WALK, HIGH);
  digitalWrite(DONTWALK, HIGH);
}
void setLight(State s) {
  digitalWrite(NSRed, LOW);
  digitalWrite(NSYel, LOW);
  digitalWrite(NSGrn, LOW);
  digitalWrite(WERed, LOW);
  digitalWrite(WEYel, LOW);
  digitalWrite(WEGrn, LOW);
  digitalWrite(WALK, LOW);
  digitalWrite(DONTWALK, LOW);
  switch (s) {
    case NSY:
      digitalWrite(NSYel, HIGH);
      digitalWrite(WERed, HIGH);
      break;
    case WEG:
      digitalWrite(NSRed, HIGH);
      digitalWrite(WEGrn, HIGH);
      break;
    case WEY:
      digitalWrite(NSRed, HIGH);
      digitalWrite(WEYel, HIGH);
      break;
    case PED:
      digitalWrite(NSRed, HIGH);
      digitalWrite(WERed, HIGH);
      digitalWrite(WALK, HIGH);
      break;
    case PEDDW:
      digitalWrite(NSRed, HIGH);
      digitalWrite(WERed, HIGH);
      digitalWrite(DONTWALK, HIGH);
      break;
    case NSG:
      digitalWrite(NSGrn, HIGH);
      digitalWrite(WERed, HIGH);
      digitalWrite(DONTWALK, HIGH);
      break;
  }
}
int getNextStateDuration(State s) {
  switch (s) {
    case NSY:
    case WEY:
    case PEDDW:
      return TRANSITION_TIME;
    default:
      return GO_TIME;
  }
}
State getNextState(State s) {
  switch (s) {
    case NSY:
      return WEG;
    case WEG:
      return WEY;
    case WEY:
      return PED;
    case PED:
      // Reset the blink rate when changing OUT of PED
      pedOn = true;
      return PEDDW;
    case PEDDW:
      return NSG;
    case NSG:
      return NSY;
  }
}
void loop() {
  unsigned long curMillis = millis();  // current time

  if ((curMillis - prevMillisState) > stateLength) {
    prevMillisState = curMillis;
    Serial.println("Changing State");
    currentState = getNextState(currentState);
    stateLength = getNextStateDuration(currentState);
    setLight(currentState);
  }

  if ((curMillis - prevMillisBlink) > BLINK_RATE && currentState != PED) {
    prevMillisBlink = curMillis;

    pedOn = !pedOn;
    digitalWrite(DONTWALK, pedOn);
  }
}
