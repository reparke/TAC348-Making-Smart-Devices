
// ref: https://github.com/CollinCunningham/BLE_UART_Controller_Test

#include "argon_ble_setup.h"
/*
  Use Adafruit Bluefruit app
  (https://learn.adafruit.com/bluefruit-le-connect/controller) Connect to
  Argon
  -> controller -> enable accelerometer

  X Y Z acceleration will modulate RGB LED color

  Uses smoothing filter (average)

  CONFIGURATION
  RGB LED (common cathode) connected to Argon
    R - A2
    G - A1
    B - A0


*/
const int PIN_RED = A2;
const int PIN_GREEN = A1;
const int PIN_BLUE = A0;

const int AVERAGING_LENGTH = 2;  // smoothing

float phoneAccel[3][AVERAGING_LENGTH];  // x, y, z with averaging of 20
int rgb[3];                             // r, g, b

void setup() {
  /* === START BLE SETUP === */
  argon_ble_setup();
  /* === END BLE SETUP === */

  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_RED, OUTPUT);
  Serial.begin(9600);
}

const unsigned long UPDATE_INTERVAL_MS =
    100;                       // delay for update of temperature
unsigned long prevUpdate = 0;  // time of last update in millis()
int curIndex = 0;

void loop() {
  if (millis() - prevUpdate >= UPDATE_INTERVAL_MS) {
    prevUpdate = millis();

    updateRgbValues();
    changeRgbLight(rgb[0], rgb[1], rgb[2]);

    /* === DEBUG PRINTING === */
    Serial.print("(r,g,b): (" + String(rgb[0]) + ", " + String(rgb[1]) + ", " +
                 String(rgb[2]) + ")");
    Serial.println(" -- (x,y,z): (" + String(phoneAccel[0][0], 2) + ", " +
                   String(phoneAccel[1][0], 2) + ", " +
                   String(phoneAccel[2][0], 2) + ")");
  }
}

void updateRgbValues() {
  float x = avg(phoneAccel[0]);
  float y = avg(phoneAccel[1]);
  float z = avg(phoneAccel[2]);
  rgb[0] = (x - (-1)) * (float)(255 - 0) / (1 - (-1)) + 0;
  rgb[1] = (y - (-1)) * (float)(255 - 0) / (1 - (-1)) + 0;
  rgb[2] = (z - (-1)) * (float)(255 - 0) / (1 - (-1)) + 0;
}

float avg(const float *accel) {
  float sum = 0;
  for (int i = 0; i < AVERAGING_LENGTH; i++) {
    sum += accel[i];
  }
  return sum / AVERAGING_LENGTH;
}

void changeRgbLight(int r, int g, int b) {
  analogWrite(PIN_RED, r);
  analogWrite(PIN_GREEN, g);
  analogWrite(PIN_BLUE, b);
}

// onDataReceived() is event handler for incoming data via RX characteristic
// When the RXCharacteristic receives data, the event handler is called

// Note: uint8_t is a byte ("unsigned integer of length 8 bits")
void onDataReceived(const uint8_t *buffer, size_t len,
                    const BlePeerDevice &peer, void *context) {
  /* === START DEBUG PRINTING ===
           uncomment following loop to see commands being sent by app ==
   */
  // for (size_t ii = 0; ii < len; ii++) {
  //   Serial.print(buffer[ii]);
  //   Serial.print(" ");
  // }
  // Serial.println();
  // for (size_t ii = 0; ii < len; ii++) {
  //   Serial.write(buffer[ii]);
  //   Serial.print(" ");
  // }
  // Serial.println();
  /* === END DEBUG PRINTING === */

  //  char pfx[2] = { (char)buffer[0], (char)buffer[1] };
  if ((char)buffer[0] == '!') {  // Sensor data flag
    switch ((char)buffer[1]) {
      case 'Q':
        Serial.println("Quaternion Data:");
        printQuaternionData(buffer);
        break;
      case 'A':
        // Serial.println("Accelerometer Data:");
        // printSensorDataXYZ(buffer);
        updateSensorDataXYZ(buffer);
        break;
      case 'G':
        Serial.println("Gyro Data:");
        printSensorDataXYZ(buffer);
        break;
      case 'M':
        Serial.println("Magnetometer Data:");
        printSensorDataXYZ(buffer);
        break;
      case 'L':
        Serial.println("Location Data:");
        printLocationData(buffer);
        break;
      case 'B':
        Serial.print("Button ");
        Serial.print((char)buffer[2]);
        Serial.print(" ");
        printButtonState((char)buffer[3]);
        break;
      case 'C':
        Serial.println("Color ");
        printColorData(buffer);
        break;
      default:
        Serial.println("Unknown Data Type");
        break;
    }
    // Serial.println("");
  }
}

// ================ ADAFRUIT ==============

void printSensorDataXYZ(const uint8_t *buffer) {
  float x = *((float *)(buffer + 2));
  Serial.print("x = ");
  Serial.println(x, 7);

  float y = *((float *)(buffer + 6));
  Serial.print("y = ");
  Serial.println(y, 7);

  float z = *((float *)(buffer + 10));
  Serial.print("z = ");
  Serial.println(z, 7);
}
void updateSensorDataXYZ(const uint8_t *buffer) {
  float x = *((float *)(buffer + 2));

  float y = *((float *)(buffer + 6));

  float z = *((float *)(buffer + 10));

  phoneAccel[0][curIndex] = x;
  phoneAccel[1][curIndex] = y;
  phoneAccel[2][curIndex] = z;

  curIndex++;
  if (curIndex >= AVERAGING_LENGTH) {
    curIndex = 0;
  }
}

void printLocationData(const uint8_t *buffer) {
  float x = *((float *)(buffer + 2));
  Serial.print("lat = ");
  Serial.println(x, 7);

  float y = *((float *)(buffer + 6));
  Serial.print("lng = ");
  Serial.println(y, 7);

  float z = *((float *)(buffer + 10));
  Serial.print("alt = ");
  Serial.println(z, 7);
}

void printColorData(const uint8_t *buffer) {
  byte r = *(buffer + 2);
  Serial.print("r = ");
  Serial.println(r, DEC);

  byte g = *(buffer + 3);
  Serial.print("g = ");
  Serial.println(g, DEC);

  byte b = *(buffer + 4);
  Serial.print("b = ");
  Serial.println(b, DEC);
}

void printQuaternionData(const uint8_t *buffer) {
  float x = *((float *)(buffer + 2));
  Serial.print("x = ");
  Serial.println(x, 7);

  float y = *((float *)(buffer + 6));
  Serial.print("y = ");
  Serial.println(y, 7);

  float z = *((float *)(buffer + 10));
  Serial.print("z = ");
  Serial.println(z, 7);

  float w = *((float *)(buffer + 14));
  Serial.print("w = ");
  Serial.println(w, 7);
}

void printButtonState(char buttonState) {
  if (buttonState == '0') {
    Serial.println("released");
  } else if (buttonState == '1') {
    Serial.println("pressed");
  } else {
    Serial.println("unknown state");
  }
}