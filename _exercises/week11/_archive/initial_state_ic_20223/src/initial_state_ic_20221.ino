#include "JsonParserGeneratorRK.h"
/*

make JSON manually
{ { "name":"Los Angeles"}}

instead use library
    JsonParserGeneratorRK

    [{"key": "temp", "value": TEMP_VAL}, {"key": "light_level", "value":
LIGHT_LEVEL}, {"key": "light_value", "value": LIGHT_VALUE}]



*/
String latitudeUSC = "34.02051";
String longitudeUSC = "-118.28563";
String latitudeUCLA = "34.0689";
String longitudeUCLA = "-118.4452";
int battery = 100;

unsigned long prevMillis = 0;

const int PIN_PHOTO = A5;
void setup() {
    pinMode(PIN_PHOTO, INPUT);
    Serial.begin(9600);
}

/*    [{"key": "temp", "value": TEMP_VAL}, {"key": "light_level", "value":
 * LIGHT_LEVEL}, {"key": "light_value", "value": LIGHT_VALUE}]
 */
void sendJsonData() {
    // create a "buffer" to store
    JsonWriterStatic<622> jw;
    jw.init();  // setup the buffer
    {
        JsonWriterAutoArray obj(&jw);

        jw.startObject();
        jw.insertKeyValue("key", "temperature");
        jw.insertKeyValue("value", random(65, 100));
        jw.finishObjectOrArray();

        int light_value = random(0, 4095);
        jw.startObject();
        jw.insertKeyValue("key", "light_value");
        jw.insertKeyValue("value", light_value);
        jw.finishObjectOrArray();

        String light_level = "";
        if (light_value > 0 && light_value <= 1600) {
            light_level = "dark";
        } else if (light_value > 2600 && light_value < 2800) {
            light_level = "ambient";
        } else {
            light_level = "bright";
        }
        jw.startObject();
        jw.insertKeyValue("key", "light_level");
        jw.insertKeyValue("value", light_level);
        jw.finishObjectOrArray();  // closes the third obj

        jw.finishObjectOrArray();  // closes the whole array
    }
    Serial.println(jw.getBuffer());
    Particle.publish("initial_state_json", jw.getBuffer());
}

void sendJsonGps() {
    JsonWriterStatic<622> jw;
    jw.init();  // empty buffer for reuse (since JsonWriterStatic is static)

    // Creating a scope like this in {} with a JsonWriterAutoObject in it
    // creates an object, and automatically closes the object when leaving the
    // scope. This is necessary because all JSON values must be in either an
    // object or an array to be valid, and JsonWriter requires all startObject
    // to be balanced with a finishObjectOrArray and JsonWriterAutoObject takes
    // care of doing that automatically.

    String coordsUSC = latitudeUSC + "," + longitudeUSC;
    String coordsUCLA = latitudeUCLA + "," + longitudeUCLA;

    {
        JsonWriterAutoArray obj(&jw);

        jw.startObject();
        jw.insertKeyValue("key", "locationUSC");
        jw.insertKeyValue("value", coordsUSC);
        jw.finishObjectOrArray();

        jw.startObject();
        jw.insertKeyValue("key", "locationUCLA");
        jw.insertKeyValue("value", coordsUCLA);
        jw.finishObjectOrArray();

        jw.startObject();
        jw.insertKeyValue("key", "battery");
        jw.insertKeyValue("value", battery);
        jw.finishObjectOrArray();

        jw.finishObjectOrArray();
    }

    Particle.publish("initial_state_json", jw.getBuffer());
    Serial.println(jw.getBuffer());
    // Wait 60 seconds
}

void loop() {
    unsigned long currMillis = millis();

    if (currMillis - prevMillis > 5000) {
        prevMillis = currMillis;

        // send the temperature and light level and photoresistor value to
        // initial state using JSON generate temp and photo level randomly
        sendJsonData();

        battery = battery - 10;
        if (battery == 0) {  // reset battery to 100% when it gets to 0%
            battery = 100;
        }
        latitudeUSC = String(latitudeUSC.toFloat() + 0.01);
        longitudeUSC = String(longitudeUSC.toFloat() - 0.01);
        sendJsonGps();
    }
}