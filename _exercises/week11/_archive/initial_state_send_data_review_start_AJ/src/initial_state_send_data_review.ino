
/*
How to send single values to Initial state in JSON format
  format: {}
  ex:
    {"key":"temperature", "value":79}

How to send multiple values to Initil
  format: [ {}, {} ]
  ex:
    [
      {"key":"temperature":"value":TEMP_VAR},
      {"key":"weather", "value":"WEATHER_VAR"}
    ]
    */

// format for GPS
// lat,long       --> "23.4993,343.3999"

/*
  send data to initial state
  - Create a "bucket" at IS which has our ACCESS KEY and BUNDLE KEY
  - Create a Webhook in Particle console (with ACCESS KEY and BUNDLE KEY) so our data gets relay to IS
  - Create string value that has JSON data we want to send to IS
  - Publish the string to via Particle.cloud
*/

String latitudeUSC = "34.02051";
String longitudeUSC = "-118.28563";
String latitudeUCLA = "34.0689";
String longitudeUCLA = "-118.4452";
int battery = 100;

unsigned long batteryDecreaseTime = 3000;
unsigned long prevMillis = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > batteryDecreaseTime) {  //decrease battery level by 10% ever 3 sec
        battery = battery - 10;
        if (battery == 0) {  //reset battery to 100% when it gets to 0%
            battery = 100;
        }
        prevMillis = curMillis;
    }
}