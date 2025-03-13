#include "Particle.h"

/* This is what shows up in Bluefruit
   You can change this to something that is short
   only has letters (no spaces, numbers, or special characters)
*/
const String DEVICE_NAME = "Photon2";

/*
1) ADD BLUETOOTH SERVICES ===============================
  see https://www.bluetooth.com/specifications/gatt/services/
  ===========================================================
*/
// service UUID is used for the peripheral device to advertise it supports UART
// These UUIDs are standard for serial / UART over BLE
// Supported by many mobiles apps including Adafruit Bluefruit app
const BleUuid serviceUuid("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");

/*
2) ADD BLUETOOTH CHARACTERISTICS ===============================
  see https://www.bluetooth.com/specifications/gatt/characteristics/
  ==================================================================
*/
// RX and TX characteristics necessary for serial UART communicaiton
// These UUIDs are standard for serial / UART over BLE
// Supported by many mobiles apps including Adafruit Bluefruit app
const BleUuid rxUuid("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid txUuid("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");

/*
3) EVENT HANDLER FORWARD DECLARATION ===========================
  You need to define onDataReceived() in the *.ino file.
  However, we need to have a "forward declaration" (i.e. the function
  header) as a C++ requirement because onDataReceived() is
  referenced below in the rxCharacteristic
  ==================================================================
*/
// Forward declaration (header) for onDataReceived()
void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer,
                    void* context);

/*
4) CREATE BLE CHARACTERISTIC OBJECTS ========================
  ===============================================================
*/
// create BLE TX characteristic object
BleCharacteristic txCharacteristic("tx", BleCharacteristicProperty::NOTIFY,
                                   txUuid, serviceUuid);

// create BLE RX characteristic object; connect to onDataReceived handler
BleCharacteristic rxCharacteristic("rx",
                                   BleCharacteristicProperty::WRITE_WO_RSP,
                                   rxUuid, serviceUuid, onDataReceived, NULL);

/*
5) BLE CONFIGURATION ========================================
  Add characterisitcs and begin advertising peripheral device
  Call this function in setup()
  ===========================================================
*/
// call this function from within SETUP
void argon_ble_setup() {
    BLE.addCharacteristic(txCharacteristic);
    BLE.addCharacteristic(rxCharacteristic);

    BleAdvertisingData data;              // build peripheral's advertising data
    data.appendServiceUUID(serviceUuid);  // advertise serial / UART service
    data.appendLocalName(
        DEVICE_NAME);      // include custom name visible in mobile app
    BLE.advertise(&data);  // advertise to mobile app (central device)
}

/*-------------------- DEBUG FUNCTIONS -----------------------*/
/*
  bluetoothSerialDebug
      used for printing debug info to serial monitor ===
*/
void bluetoothSerialDebug(const uint8_t* data, size_t len) {
    for (size_t index = 0; index < len; index++) {
        Serial.print((char)data[index]);
        Serial.print(" ");
    }
    Serial.println();
}