

double SPEED_SOUND_CM_ROOM_TEMP_FAHR = 0.03444;

const int MIN_RANGE = 2;      // cm
const int WARNING_RANGE = 12;  // 5 in ~~ 12 cm
const int MAX_RANGE_CM = 400;    // cm


const int PIN_TRIGGER = D6;
const int PIN_ECHO = D5;


double distanceCm;

void setup() {
    Serial.begin(9600);
    Serial.println("Setup");

    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

void loop() {
    // start trigger
    digitalWrite(PIN_TRIGGER, LOW);  // prepare
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);  // prepare
    delayMicroseconds(10);

    digitalWrite(PIN_TRIGGER, LOW);  // prepare

    int timeRoundTrip = pulseIn(PIN_ECHO, HIGH);  // wait for round trip time
    distanceCm = timeRoundTrip * SPEED_SOUND_CM_ROOM_TEMP_FAHR / 2;

    Serial.print("Dist to object:");
    if (distanceCm >= MAX_RANGE_CM ||
        distanceCm <= MIN_RANGE_CM) {  // these units can be CM only because
                                       // that is what the sensor reports

        Serial.print("out of range");
        Particle.publish("out of range");
    } else {
        Serial.print(distanceCm);
        Serial.print(" cm");
        Particle.publish(String(distanceCm) + " cm");
    }
    Serial.println();

    // debug
    /*
    Serial.print("Round trip time: ");
    Serial.println(timeRoundTrip);
    Serial.print("Distance in cm: ");
    Serial.println(distanceCm);
    */
    delay(500);
}
