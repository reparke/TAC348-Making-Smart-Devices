---
marp: true
theme: tac
 
category: reference
title: Captive Wifi Networks
show_in_list: true
---




## Captive Wifi Networks

- "Captive Wifi" networks are networks where you need to login or click accept before connecting such as
  - Some apartments / dorms
  - Hotels
  - Starbucks
- The Photon 2 can **not** connect to captive wifi networks

## Solution 1: Campus wifi 

- Use the guest wireless network 
- Guaranteed to work, but obviously annoying

## Solution 2: Hotspot

- You can use your phone or Windows computer as a hotspot (Mac computer doesn't work at the moment)
- Note this uses the internet from your phonr or computer so if you have limited cell phone data plans, please be cautious doing this
- The "name" of your hotspot needs to be a word with no spaces or special symbols.

- Instructions
  - [iPhone](https://support.apple.com/en-us/HT204023)
  - [Android](https://support.google.com/android/answer/9059108?hl=en)
  - [Windows](https://support.microsoft.com/en-us/windows/use-your-windows-pc-as-a-mobile-hotspot-c89b0fad-72d5-41e8-f7ea-406ad9036b85)

## Solution 3: Register Your Photon 2

- Some networks allow you to register your Photon 2 so it doesn't need to login to connect
- You will need to contact your dorm / apartment to see if this is available
- You will need
  1. Webpage to MAC Address to wifi network. This might be provided to you when you connect a new device (like your phone) to the wifi
  2. Your Photon 2's MAC address (unique number for device)

### Code to Get Photon 2 MAC Address

- To obtain the MAC address, add this code to a project and flash it

```c++
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_WARN);

//if you don't have wifi access, uncomment the line below and flash using "Flash Application (local)"
//SYSTEM_MODE(MANUAL);

byte mac[6];  // the MAC address of your Wifi shield
int LED = D7;

void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    WiFi.macAddress(mac);
}

void loop() {
    for (int i = 0; i < 6; i++) {
        Serial.printf("%02x%s", mac[i], i != 5 ? ":" : "");
    }
    Serial.println();

    // blink an LED - this is just here as a validation that it's working...
    digitalWrite(LED, HIGH);
    delay(250);
    digitalWrite(LED, LOW);
    delay(1000);
}

```

### MAC Address

- After flashing the code above, open the Serial Monitor
- You should see something like this. Copy it.

`c8:2b:96:b6:40:B4` *(just an example)*

 

### Registering Your MAC Address

- Open the webpage provided by your residence
- Register your Photon 2 by entering your unique MAC address
- Here is an example

![image-20220125190440788](captive_wifi.assets/add_mac.png)

- Put the Photon 2 in listening mode (dark blue) and go through process of claiming the device again (you do not need to unclaim the device)

## Credits

- Zach Ji
- [Particle Community](https://community.particle.io/t/how-to-get-mac-address/1411/9)