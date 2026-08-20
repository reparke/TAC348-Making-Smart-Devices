//cf: http://siever.info/cse132/weeks/3/studio/
// this code is from Bill Siever
// two lane stoplight and pedestrian walk light

//it uses a timing approach to calculate "next period"

const int PIN_NS_RED = D2;
const int NSYel = D3;
const int NSGrn = D4;
const int PIN_WE_RED = A0;
const int WEYel = A1;
const int WEGrn = D5;
const int PIN_WALK = D6;
const int PIN_DONT_WALK = D7;

const int LONG_LIGHT_DURATION = 5000;  // time for green, red, walk, don't walk
const int SHORT_LIGHT_DURATION = 1000; //time for yellow
const int BLINK_RATE = 500; // time for blinking don't walk light

enum State {
   stateNSY,   
   stateWEG, 
   stateWEY, 
   statePED, 
   statePEDDW,
   stateNSG
}; 
State currentState = stateNSG;
unsigned long nextStateChange = 0;
unsigned long nextBlink = 0;
bool pedOn = true;
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
  
  digitalWrite(PIN_WALK, HIGH);
  digitalWrite(PIN_DONT_WALK, HIGH);
}
void setLight(State s) {
  digitalWrite(PIN_NS_RED, LOW);
  digitalWrite(NSYel, LOW);
  digitalWrite(NSGrn, LOW);
  digitalWrite(PIN_WE_RED, LOW);
  digitalWrite(WEYel, LOW);
  digitalWrite(WEGrn, LOW);
  digitalWrite(PIN_WALK, LOW);
  digitalWrite(PIN_DONT_WALK, LOW);
  switch(s) {
    case stateNSY:
      digitalWrite(NSYel, HIGH);
      digitalWrite(PIN_WE_RED, HIGH);  
    break;
    case stateWEG:
      digitalWrite(PIN_NS_RED, HIGH);
      digitalWrite(WEGrn, HIGH);
    break;
    case stateWEY:
      digitalWrite(PIN_NS_RED, HIGH);
      digitalWrite(WEYel, HIGH);
    break;
    case statePED:
      digitalWrite(PIN_NS_RED, HIGH);
      digitalWrite(PIN_WE_RED, HIGH);
      digitalWrite(PIN_WALK, HIGH);
    break;
    case statePEDDW:
      digitalWrite(PIN_NS_RED, HIGH);
      digitalWrite(PIN_WE_RED, HIGH);
      digitalWrite(PIN_DONT_WALK, HIGH);
    break;
    case stateNSG: 
      digitalWrite(NSGrn, HIGH);
      digitalWrite(PIN_WE_RED, HIGH);
      digitalWrite(PIN_DONT_WALK, HIGH);
    break;
  }
}
int stateDuration(State s) {
  switch(s) {
    case stateNSY:
    case stateWEY:
    case statePEDDW:
      return SHORT_LIGHT_DURATION;
    default:
      return LONG_LIGHT_DURATION;
  }
}
State nextState(State s) {
  switch(s) {
    case stateNSY:
      return stateWEG;
    case stateWEG:
      return stateWEY;
    case stateWEY: 
      return statePED;
    case statePED:
      // Reset the blink rate when changing OUT of PED
      pedOn = true;
      nextBlink = millis() + BLINK_RATE;
      return statePEDDW;
    case statePEDDW:
      return stateNSG;
    case stateNSG:
      return stateNSY;   
  }
}
void loop() {
  if(millis()>nextStateChange) {
    Serial.println("Changing State");
    currentState = nextState(currentState);
    nextStateChange += stateDuration(currentState);
    setLight(currentState);
  }
  
  if(millis()>nextBlink && currentState != statePED) {
      nextBlink += BLINK_RATE;
      pedOn = !pedOn;
      digitalWrite(PIN_DONT_WALK, pedOn);
   }
}
