
#include "JsonParserGeneratorRK.h"

unsigned long prevMillis = 0;
const int PIN_PHOTO = A5;

/*
    Initial state json format
 [
  {
    "key": "light_level",
    "value": "3000",
  },
  {
    "key": "light_value",
    "value": "dark",
  }
]

if we wanted to, we could create a string that looks exactly like above, and
 then do particle publish

*/

void setup() {
    pinMode(PIN_PHOTO, INPUT);
    Serial.begin(9600);
}

/*
 [
  {
    "key": "light_level",
    "value": "3000",
  },
  {
    "key": "light_value",
    "value": "dark",
  }
]
-----------
jw.insertKeyValue("a", true);
jw.insertKeyValue("b", 1234);
jw.insertKeyValue("c", "test");

{
  "a":"true",
  "b":"1234",
  "c":"test"
}

1) make each datapoint its own object
2) we need to make sure that we use "key" and "value"
3) to put all datapoints in an array
*/

/*
  send the GPS coordinates for USC to initial state
  send the GPS coordinates for UCLA to initial state
  try to update the GPS location for USC

  GPS format is
  LATITUDE,LONGITUTDE    ("34.558333","-84.445454") STRINGS!

*/

String latitudeUSC = "34.02051";
String longitudeUSC = "-118.28563";
String latitudeUCLA = "34.0689";
String longitudeUCLA = "-118.4452";

void loop() {
    int light_level = analogRead(PIN_PHOTO);  // random(0, 4095)
    String light_value = "";
    if (light_level > 0 && light_level <= 1600) {
        light_value = "dark";
    } else if (light_level > 1600 && light_level <= 2800) {
        light_value = "ambient";
    } else {
        light_value = "bright";
    }

    // following documentation
    JsonWriterStatic<625> jw;

    jw.init();  // not in example, but needed

    {  // from the forum
        JsonWriterAutoArray arr(
            &jw);  // our outer (or parent) container is an array

        jw.startObject();  // creates our first datapoint
        jw.insertKeyValue("key",
                          "light_level");  //"light_level" is the label that
                                           // will show up in initial state
        jw.insertKeyValue("value",
                          light_level);  // light_level is the int variable we
                                         // have that stores our photoresistor
        jw.finishObjectOrArray();

        jw.startObject();
        jw.insertKeyValue("key", "light_value");
        jw.insertKeyValue("value", light_value);
        jw.finishObjectOrArray();

        jw.startObject();
        jw.insertKeyValue("key", "temperature");
        jw.insertKeyValue(
            "value", random(70, 90));  // generate random temp from 70 to 90 deg
        jw.finishObjectOrArray();      // ends the last data point

        //how to adjust long and lat? because these are strings?
        
        latitudeUSC = String(latitudeUSC.toFloat() + 0.01);
        longitudeUSC = String(longitudeUSC.toFloat() + 0.01);

        String coordsUSC = latitudeUSC + "," + longitudeUSC;
        String coordsUCLA = latitudeUCLA + "," + longitudeUCLA;

        jw.startObject();
        jw.insertKeyValue("key", "locationUSC");
        jw.insertKeyValue("value", coordsUSC);
        jw.finishObjectOrArray();

        jw.startObject();
        jw.insertKeyValue("key", "locationUCLA");
        jw.insertKeyValue("value", coordsUCLA);
        jw.finishObjectOrArray();

        jw.finishObjectOrArray();  // ends the outer array
    }

    Serial.println(jw.getBuffer());
    Particle.publish("initial_state_json", jw.getBuffer());
    delay(5000);
}
