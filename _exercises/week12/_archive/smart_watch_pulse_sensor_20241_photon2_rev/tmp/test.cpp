
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

void setup() {
    Serial.begin(9600);
    Particle.publish("SETUP", "SETUP DATA");
    Serial.println("Setup publish");
}

void loop() {
    Particle.publish("test", "data");
    Serial.println("testing");
    delay(5000);
}