

double SPEED_SOUND_CM_ROOM_TEMP_FAHR = 0.03444;
double CONV_FACTOR_CM_TO_IN = 0.3437;
int MAX_RANGE_CM = 78;
int MIN_RANGE_CM = 0;

const int PIN_BUTTON = D4;
const int PIN_TRIGGER = D3;
const int PIN_ECHO = D2;

bool unitInCm = true;  // true is CM, false is IN
double distanceCm;

void setup() {
    Serial.begin(9600);
    Serial.println("Setup");

    pinMode(PIN_BUTTON, INPUT);
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

    Serial.println(digitalRead(PIN_BUTTON));
    if (digitalRead(PIN_BUTTON) == HIGH) {
        delay(50);             // crude way to address debouncing
        unitInCm = !unitInCm;  // toggle units if button pressed
    }

    Serial.print("Dist to object:");
    if (distanceCm >= MAX_RANGE_CM ||
        distanceCm <= MIN_RANGE_CM) {  // these units can be CM only because
                                       // that is what the sensor reports

        Serial.print("out of range");
    } else {
        if (unitInCm == true) {  // cm
            Serial.print(distanceCm);
            Serial.print(" cm");
        } else {  // in
            double distanceIn = distanceCm * CONV_FACTOR_CM_TO_IN;
            Serial.print(distanceIn);
            Serial.print(" in");
        }
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
