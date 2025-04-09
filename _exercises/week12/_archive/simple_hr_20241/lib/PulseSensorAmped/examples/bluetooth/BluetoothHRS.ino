/*
 * Project Bluetooth Device Info. Service and Heart Rate Monitor example
 * Description:
 * Author:  Bill Siever
 * Date: 
 */


const int pulseSignalPin = A4;

#include <PulseSensorAmped.h>



/**
 * Device Information Service
 * 
 * UUIDs, Characteristics, and Setup 
 *
 *  See: https://www.bluetooth.org/docman/handlers/downloaddoc.ashx?doc_id=244369
 * 
 * */
void disSetup() {

  struct DISServiceItem {    // Define a structure to hold the data
    uint16_t uuid;           // UUID of an item of data (i.e. "Data type")
    const char *value;       // The specific value
  };

  // Create an array of all items that should be added
  // These are all optional. Any can be commented out.
  // Each of these is optional:
  DISServiceItem disData[] = {
    0x2a29, "Testing",    // Manufacturer name
    0x2A24, "V1",         // Model Number String
    0x2A25, "001",        // Serial Number String
    0x2A27, "0.1.0",      // Hardware Revision String
    0x2A26, "0.1.0",      // Firmware Revision String
    0x2A28, "0.0.1",      // Software Revision String
    // System ID omitted
    // IEEE Reg Cert Data List omitted
    // PnP ID omitted
  };

  // Build the service (add all characteristics defined above)
  BleUuid deviceInfoService(0x180A); // Device Info Service UUID 

  // Loop through and add each.  (All are just "Readable" for this service)
  for(unsigned i=0;i<sizeof(disData)/sizeof(DISServiceItem); i++) {
    BleCharacteristic characteristic(NULL, BleCharacteristicProperty::READ, BleUuid(disData[i].uuid), deviceInfoService);
    BLE.addCharacteristic(characteristic);
    // Values can only be set AFTER the characteristic is added
    characteristic.setValue((uint8_t*)disData[i].value, strlen(disData[i].value)); 
  }
}



/**
 * Simple Heart Rate Service:  This only supports simple heart rate
 *     The service can also support some optional features:
 *           The location of where the sensor is on the body
 *           Data about energy expended and RR interval  
 *           Or an additional byte for heart rate (for animals that have a BPM>256)
 * */
BleUuid heartRateService(0x180D);
// The characteristic is declared as a global variable so it can be changed (via Setvalue)
                                // Name,   Properties,                  , UUID (Type),   , Service
BleCharacteristic hrsMeasurement(NULL, BleCharacteristicProperty::NOTIFY, BleUuid(0x2A37), heartRateService); // The heart rate measurement 
BleCharacteristic hrsBodyLocation(NULL, BleCharacteristicProperty::READ, BleUuid(0x2A38), heartRateService); // The sensor location

// Setup function here just adds the single characteristic
void hrsSetup() {
  // Setup the heart rate service
  // https://www.bluetooth.org/docman/handlers/downloaddoc.ashx?doc_id=239866
  BLE.addCharacteristic(hrsMeasurement);
  BLE.addCharacteristic(hrsBodyLocation);
  uint8_t location = 3;  // Finger: https://github.com/oesmith/gatt-xml/blob/master/org.bluetooth.characteristic.body_sensor_location.xml
  hrsBodyLocation.setValue(&location,1);
}

// Set the heart rate to a specific value (and "notify" listeners)
// rr val is measured in ms
void hrsUpdateRateHR(uint8_t rate, bool contactSensorAvail=false, bool contact=true, bool rrAvail=false, uint16_t rr=0) {
  uint8_t flags = 0;
  if(contactSensorAvail) {
    flags |= 1<<2;
    if(contact==false)  // Bit set when no contact
      flags |= 1<<1;
  }
  if(rrAvail) {
    flags |= 1<<4;
  }
  // Convert rr to 1024s
  rr = rr*1024/1000;
  uint8_t rrHigh = ((rr&0xFF00)>>8);
  uint8_t rrLow = rr&0xFF;
  uint8_t data[4] = {flags, rate, rrHigh, rrLow};  // First byte is "flags" (all zeros for 1-byte heart rate only data)
  hrsMeasurement.setValue(data, rrAvail?4:2);
}

// setup() runs once, when the device is first turned on.
void setup() {
  disSetup();   // Configure device info service
  hrsSetup();   // Configure the heart rate service

  // Advertise a name heart rate service (so heart rate apps can discover it!)
  BleAdvertisingData advData;
  advData.append(BleAdvertisingDataType::SHORT_LOCAL_NAME, (const uint8_t *)"test", 4);
  advData.appendServiceUUID(heartRateService);
  BLE.advertise(&advData);

  Serial.begin(115200);
  // Serial.println("Starting");
  Serial.println("signal,peak,trough,thresh");
  PulseSensorAmped.attach(pulseSignalPin);
  PulseSensorAmped.start();
}

bool sensorConnected = false;

// An optional function to recieve the Beats Per Minute (BPM) and Interbeat Interval (IBI) in mS
void PulseSensorAmped_data(int BPM, int IBI) {
  if(BPM>0) {
    sensorConnected = true;
  }
  hrsUpdateRateHR(BPM, true, sensorConnected, true, IBI);
  Serial.print("BPM:");
  Serial.print(BPM);
  Serial.print(" IBI: ");
  Serial.println(IBI);
}

// An optional function to indicate that the pulse signal has been lost
// (Due to the nature of pulse detection via reflected light, spurios signals are possible. 
//  i.e. received data may not be valid) 
void PulseSensorAmped_lost(void) {
  Serial.println("Pulse Lost");
  sensorConnected = false;
}


// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // Check for updates every 100ms
  PulseSensorAmped.process();
  delay(100);
}