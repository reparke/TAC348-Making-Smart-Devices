const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;  // aka MOSI

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    analogWrite(PIN_RED, 255);
    analogWrite(PIN_GREEN, 255);
    analogWrite(PIN_BLUE, 255);
    delay(1000);
    analogWrite(PIN_RED, 0);
    analogWrite(PIN_GREEN, 0);
    analogWrite(PIN_BLUE, 0);
    delay(1000);
    Serial.println("off");
}

// const int PIN_LED = D7;
// const int PIN_RED = A2;
// const int PIN_GREEN = A5;
// const int PIN_BLUE = D15; // aka MOSI
// const int PIN_SWITCH = D2;

// unsigned long prevMillis = 0;

// // 0 is white, 1 is green, 2 is magenta, 3 is yellow, 4 is red
// // define our enum
// // enum YOUR_ENUM_TYPE_NAME {VALUES}
// //            0      1       2        3      4
// enum Color { WHITE, GREEN, MAGENTA, YELLOW, RED };
// // consider this is sort of like 5 constants to make your code more readable

// // 0 is white, 1 is green, 2 is magenta, 3 is yellow, 4 is red
// void displayColor(Color color) {
//     switch (color) {
//         case MAGENTA:  // green
//             analogWrite(PIN_RED, 255);
//             analogWrite(PIN_BLUE, 255);
//             analogWrite(PIN_GREEN, 0);
//             break;
//         case WHITE:  // white
//             analogWrite(PIN_RED, 255);
//             analogWrite(PIN_BLUE, 255);
//             analogWrite(PIN_GREEN, 255);
//             break;
//         case GREEN:  // green
//             analogWrite(PIN_RED, 0);
//             analogWrite(PIN_BLUE, 0);
//             analogWrite(PIN_GREEN, 255);
//             break;

//         case YELLOW:  // green
//             analogWrite(PIN_RED, 255);
//             analogWrite(PIN_BLUE, 0);
//             analogWrite(PIN_GREEN, 255);
//             break;
//         case RED:  // green
//             analogWrite(PIN_RED, 255);
//             analogWrite(PIN_BLUE, 0);
//             analogWrite(PIN_GREEN, 0);
//             break;
//         default:  // else
//             analogWrite(PIN_RED, 0);
//             analogWrite(PIN_BLUE, 0);
//             analogWrite(PIN_GREEN, 0);
//             // if (color == 0) {
//             //     analogWrite(PIN_RED, 255);
//             //     analogWrite(PIN_BLUE, 255);
//             //     analogWrite(PIN_GREEN, 255);
//             // } else if (color == 1) {  // green
//             //     analogWrite(PIN_RED, 0);
//             //     analogWrite(PIN_BLUE, 0);
//             //     analogWrite(PIN_GREEN, 255);
//             // }
//     }
// }

// void setup() {
//     pinMode(PIN_LED, OUTPUT);
//     pinMode(PIN_RED, OUTPUT);
//     pinMode(PIN_BLUE, OUTPUT);
//     pinMode(PIN_GREEN, OUTPUT);
//     pinMode(PIN_SWITCH, INPUT);

//     Serial.begin(9600);
//     // subscribe to event
//     //                 (eventname, eventhanflerFunction, all or my devices)
//     Particle.subscribe("TAC348_color_change_event", colorEventHandler,
//                        ALL_DEVICES);
// }

// // event handler - pointer memory address of the beginning of an array of
// // character
// //    "kinda" like a string
// void colorEventHandler(const char *event, const char *data) {
//     // step 1: convert your const char * to string
//     String eventString = String(event);
//     String dataString = String(data);  // e.g. "4"
//     Serial.println(eventString + " " + dataString);

//     // convert the string to int
//     int colorAsInt = dataString.toInt();
//     Color color = (Color) colorAsInt;       //casting int to color

//     displayColor(color);
// }

// // public are no longer supported :(
// void loop() {
//     //use millis timer every 5 sec
//     //check the switch, turn on board LED if switch is open, turn if closed
//     unsigned long curMillis = millis();
//     if (curMillis - prevMillis > 5000) {
//         int switchVal = digitalRead(PIN_SWITCH); //HIGH is open, LOW is
//         closed if (switchVal == HIGH) { // open
//             digitalWrite(PIN_LED, HIGH);
//         }
//         else {
//             digitalWrite(PIN_LED, LOW);
//         }
//         prevMillis = curMillis;
//     }

//     Particle.publish("TAC348_color_change_event", String(random(0, 5)));
//     delay(3000);
// }
