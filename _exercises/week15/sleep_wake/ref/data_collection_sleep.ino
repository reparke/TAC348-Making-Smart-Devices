
boolean shouldSleep = true;  // set to false, but gets inverted in setup()
int count = 0;
const int MAX_SIZE = 2;
int data[MAX_SIZE];

SYSTEM_MODE(SEMI_AUTOMATIC);    //when argon turns on, it does NOT connect to cloud (no wifi)

void setup() {
    Serial.begin(9600);
    pinMode(WKP, INPUT);  // not strictly necessary
}

// String getValueString() {

// }
void loop() { dataCollection(); }

void dataCollection() {
    if (count < MAX_SIZE) {
        Serial.print("Read value, but don't publish: ");
        data[count] = random(60, 120);
        Serial.print(String(data[count]) + ", ");
        count += 1;
        data[count] = random(60, 120);
        Serial.print(String(data[count]) + ", ");
        count += 1;
        data[count] = random(60, 120);
        Serial.print(String(data[count]) + ", ");
        count += 1;
        Serial.println();
    }
    else if (count == MAX_SIZE) {
        Particle.connect();
        String msg = "";
        for (int i = 0; i < MAX_SIZE; i++) {
            msg += String(data[i]) + ",";
        }
        Particle.publish("Data Collection", msg);
        Serial.println("This is publish data: " + msg);
        count = 0;
        Particle.disconnect();
    }
    Serial.println("About to ULTRA_LOW_POWER! on time");
    SystemSleepConfiguration config;
    config.mode(SystemSleepMode::ULTRA_LOW_POWER).duration(10s);
    System.sleep(config);
}
