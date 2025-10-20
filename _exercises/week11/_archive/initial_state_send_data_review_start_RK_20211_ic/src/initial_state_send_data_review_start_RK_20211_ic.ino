#include "JsonParserGeneratorRK.h"
/*
  send data to initial state
  - Create a "bucket" at IS which has our ACCESS KEY and BUNDLE KEY
  - Create a Webhook in Particle console (with ACCESS KEY and BUNDLE KEY) so our
  data gets relay to IS
  - Create string value that has JSON data we want to send to IS
  - Publish the string to via Particle.cloud
*/

/*
[
  {
    "key":"USC coords",
    "value": <USC coords var>
  },
  {
    "key":"UCLA coords",
    "value": <UCLA coords var>
  },
  {
    "key":"battery",
    "value": <battery level var>
  },
]
*/

String latitudeUSC = "34.02051";
String longitudeUSC = "-118.28563";
String latitudeUCLA = "34.0689";
String longitudeUCLA = "-118.4452";
int battery = 100;

unsigned long batteryDecreaseTime = 3000;
unsigned long prevMillis = 0;

void setup() { Serial.begin(9600); }

void loop() {
    unsigned long curMillis = millis();
    if (curMillis - prevMillis >
        batteryDecreaseTime) {  // decrease battery level by 10% ever 3 sec
        battery = battery - 10;
        if (battery < 0) {
          battery = 100;
        }
        //initial state format for GPS
        //"lat,lon"
        String coordsUSC = latitudeUSC + "," + longitudeUSC;
        String coordsUCLA = latitudeUCLA + "," + longitudeUCLA;

        //this is now the JSON RK library
        //we need an extra {}
        JsonWriterStatic<622> jw;   //this is overall object that allows to create json
        jw.init();      //sets up object
        {
          //we need to create the json package
          JsonWriterAutoArray writer(&jw);
          
          //let's add the USC coords
          jw.startObject();
          jw.insertKeyValue("key", "USC_coords");
          jw.insertKeyValue("value", coordsUSC);
          jw.finishObjectOrArray();

          //let's add the UCLA coords
          jw.startObject();
          jw.insertKeyValue("key", "UCLA_coords");
          jw.insertKeyValue("value", coordsUCLA);
          jw.finishObjectOrArray();

          // let's add the UCLA coords
          jw.startObject();
          jw.insertKeyValue("key", "battery");
          jw.insertKeyValue("value", battery);
          jw.finishObjectOrArray();

          jw.finishObjectOrArray();
        }
        Particle.publish("week10_20203", jw.getBuffer());
        Serial.println(String(jw.getBuffer()));

        prevMillis = curMillis;
    }
}