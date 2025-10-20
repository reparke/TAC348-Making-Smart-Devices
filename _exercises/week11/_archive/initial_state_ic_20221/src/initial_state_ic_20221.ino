#include "JsonParserGeneratorRK.h"

/*


*/

// send GPS and battery data (should be global)
//  battery: 100 to 0, decrease by 1
//  GPS format: Latitiude_asString,Longitide_asSTring
//               ex: "34.0224,-118.2851"
//      have the long/lat move by a little bit

void setup() { Serial.begin(9600); }

unsigned long prevMillis = 0;
int batteryLevel = 100;
float latitude = 34.0224;
float longitude = -118.2851;

void loop() {
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > 5000) {
        prevMillis = curMillis;
        int temperature = random(70, 100);
        int lightLevel = random(0, 4095);
        // [ {key:value, key:value}, {key:value, key:value} ]

        JsonWriterStatic<622> jw;
        jw.init();  // empty buffer for reuse (since jw is static)

        {
            JsonWriterAutoArray obj(&jw);   // start array []

            // Start of code for one data value
            jw.startObject();                           //creates first {
            jw.insertKeyValue("key", "temperature");
            jw.insertKeyValue("value", temperature);
            jw.finishObjectOrArray();                  //end first }

            jw.startObject();  // creates second {
            jw.insertKeyValue("key", "light level");
            jw.insertKeyValue("value", lightLevel);
            jw.finishObjectOrArray();  // end second }

            jw.finishObjectOrArray();  // end array ]
        }

        Particle.publish("initial_state_json", jw.getBuffer());
        Serial.println(jw.getBuffer());
    }
}