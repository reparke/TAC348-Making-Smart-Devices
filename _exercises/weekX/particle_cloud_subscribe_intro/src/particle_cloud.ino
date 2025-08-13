
const int PIN_LED = D7;
const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;  // aka MOSI
const int PIN_SWITCH = D2;
enum Color { WHITE, GREEN, MAGENTA, YELLOW, RED };

// make sure to list this function BEFORE setup and loop
void displayColors(Color c) {
    // if (c == WHITE)
    // {
    //   analogWrite(PIN_RED, 255);
    //   analogWrite(PIN_GREEN, 255);
    //   analogWrite(PIN_BLUE, 255);
    // }
    // else if (c == GREEN) {
    //   analogWrite(PIN_RED, 0);
    //   analogWrite(PIN_GREEN, 255);
    //   analogWrite(PIN_BLUE, 0);
    // }
    // else if (c == MAGENTA) {
    //   analogWrite(PIN_RED, 255);
    //   analogWrite(PIN_GREEN, 0);
    //   analogWrite(PIN_BLUE, 255);
    // }
    // else if (c == YELLOW) {
    //   analogWrite(PIN_RED, 255);
    //   analogWrite(PIN_GREEN, 255);
    //   analogWrite(PIN_BLUE, 0);
    // }
    switch (c) {
        case WHITE:
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 255);
            break;
        case GREEN:
            analogWrite(PIN_RED, 0);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 0);
            break;
        case MAGENTA:
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 0);
            analogWrite(PIN_BLUE, 255);
            break;
        case YELLOW:
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 255);
            analogWrite(PIN_BLUE, 0);
            break;
        case RED:
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 0);
            analogWrite(PIN_BLUE, 0);
            break;
    }
}
void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);

    Serial.begin(9600);
    Particle.subscribe("TAC348_color_change_event", colorHandler, ALL_DEVICES);
    displayColors(MAGENTA);
}

void colorHandler(const char *event, const char *data) {
    String colorStr = String(data);
    Serial.println("In color handler: color = " + colorStr);

    int colorInt = colorStr.toInt();

    Color color = (Color)colorInt;

    displayColors(color);
}

// For Rob only--message sent to students
void loop() {
    Particle.publish("TAC348_color_change_event", String(random(0, 5)), PUBLIC);
    delay(3000);
}
