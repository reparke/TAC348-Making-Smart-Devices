
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;

int prevSwitch = HIGH;


/*
    to use Blynk library in our code, there are 4 steps
    1 add your unique api token from blynk website
    2 include library
    3 start blynk in setup()
    4 use blynk.run in loop()
*/

// blynk #1: add the variables from blynk website
#define BLYNK_TEMPLATE_ID "TMPL2Ae87sVgT"
#define BLYNK_TEMPLATE_NAME "Week 6 TTh Exercise"
#define BLYNK_AUTH_TOKEN "7GJZYcv0gh1X_X7-gW2pp4pibH_0dB3l"

// blynk #2: include blynk library
#include <blynk.h>

unsigned long prevMillis = 0;
const unsigned long INTERVAL_BLYNK = 10000;

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

/*
    how do we get data FROM APP TO PHOTON

EVENT DRIVEN PROGRAMMING

    we write a function but WE DONT CALL IT!
    --> when the photon detect "a specific event"
        then THE PHOTON itself calls the function AUTOMATICALLY

    BLYNK_WRITE(VIRTUAL_PIN) {
        //action you want to take went the data on virtual pin changes
    }
*/

//event handler for button datastream on V5
//anytime there is ANY change for pin V5, this function is called automatically
//when you press button, func is called
//when you release, func is called

BLYNK_WRITE(V5) {
    //this funct has a special object called param
    //param stores whatever data was sent from app


    int buttonVal = param.asInt();      // param.asString()

    if (buttonVal == 1) {
        Serial.println("Button!");
        changeLedColor(random(0, 256), random(0, 256), random(0, 256));
    }
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);

    //blynk #3:
    Blynk.begin(BLYNK_AUTH_TOKEN);
}

/*
    mag switch is normally open or closed? OPEN

    when swtich is closed, publish ONE message to cloud that says "switch was
   closed" and show white on LED

    when switch is open, publish ONE message to cloud "switch was opened" and
   show Red on LED

    typically with a latch, we have cared the falling edge H->L (ignore rising
   edge)

    CurSwitch               PrevSwitch
      L                         H               --> switch was just closed
      H                         L               --> switch was just opened
      L                         L               --> still closed
      H                         H               --> still open

------

go app store and download Blynk

    blynk can send data FROM app TO photon
              send data FROM photon TO app

    start with sending FROM photon to APP
        Blynk.virtualWrite(VIRTUAL_PIN, VALUE)
        ex
        Blynk.virtualWrite(V10, "hello world")
    BE ADVISED
        we can't call virtualWrite too often
    instead,
        use virtualWrite either in a millis timer or trigger infrequently

*/

void loop() {
    //blynk step 4
    Blynk.run(); // continually keep in contact with app
    // this needs to run fast and WITHOUT delay

    
    //lets send a random number to blynk with millis timer

    unsigned long curMillis = millis();
    if (curMillis - prevMillis > INTERVAL_BLYNK) {
        prevMillis = curMillis;
        Blynk.virtualWrite(V6, random(0, 256));
    }

    int curSwitch = digitalRead(PIN_SWITCH);

    if (curSwitch == HIGH && prevSwitch == LOW) {
        // falling edge
        Particle.publish("Switch", "switch was opened");
        changeLedColor(255, 0, 0);
        Serial.println("opened");
        Blynk.virtualWrite(V3, "open");
    } else if (curSwitch == LOW && prevSwitch == HIGH) {
        // rising edge
        Particle.publish("Switch", "switch was closed");
        changeLedColor(255, 255, 255);
        Serial.println("closed");
        Blynk.virtualWrite(V3, "closed");
    }
    prevSwitch = curSwitch;
}