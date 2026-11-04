---
marp: true
theme: tac

week: 11
category: lectures
title: Parsing JSON with ArduinoJson Library
---
<!-- headingDivider: 2 -->

# Parsing JSON with `ArduinoJson` Library

## JSON Example Data

- Consider this shortened [Open-Meteo](https://open-meteo.com/) response received by the Photon 2
- This example assumes the webhook requests temperature in Fahrenheit

```json
{
  "current": {
    "temperature_2m": 72.4,
    "relative_humidity_2m": 45,
    "weather_code": 1
  }
}
```

## Publishing and Subscribing

```c++
void setup() {
  // Subscribe to the integration response event
  Particle.subscribe("hook-response/open_meteo_json", myHandler,
                     MY_DEVICES);
}

void loop() {
  // Trigger the integration
  Particle.publish("open_meteo_json", "");
  // Wait 10 seconds
  delay(10000);
}
```


## Parsing JSON with a Library:  `ArduinoJson` 

- `ArduinoJson` is a popular library for parsing JSON code and can be installed from **Workbench**
* Use the sample code below for your event handler
* The first part allows for responses from the webhook that come in multiple parts (you don't need to change this)
* The second part is where you can adapt your own code

## Configuration of `ArduinoJson`

- Import library and set up Arduino compatibility

```c++
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h> 
```

## Helper File

- A long webhook response may arrive in several parts
- Download the library [`json_webhook_response_helper.h`](json_webhook_response_helper.h)
- The library includes a helper function`json_webhook_response_helper()` which puts the parts together and returns the complete JSON as a `String`
- Until all the parts arrive, it returns an empty `String`

```c++
#include "json_webhook_response_helper.h"
```



## Configuration of `ArduinoJson` Library

- Import library and set up Arduino compatibility
```c++
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h> 
```




## Configuration of Event Handler
- Each time the event handler runs, `data` contains one part of the webhook response. A short response fits in one part
- The helper puts the parts together in `fullJson`
```c++
void myHandler(const char *event, const char *data) 
```


Here is an template for `myHandler`

```c++
void myHandler(const char *event, const char *data) {
// Part 1: helper function allows for webhook responses to be delivered in multple "chunks"; you don't need to change these lines
    String fullJson = json_webhook_response_helper(event, data);
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, fullJson);

// Part 2 is where you can parse the actual data; you code goes in the IF
    if (!error) {
        
    /*          ============ 
    Here is where your parsing code goes 
    	        ============
    */
    }
}
```
## Parsing JSON

* Add you code to parse JSON to `myHandler`
* Each JSON response will look different
* Here is how to read the temperature from the Open-Meteo response above

```c++
    float tempF = doc["current"]["temperature_2m"];  // 72.4
    Serial.println("The temperature is " + String(tempF, 1) + " F");
```

* Try reading `relative_humidity_2m` from the same `current` object

## Exercise: Sunrise Sunset API

* Download the [sunset_sunrise_start project](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_exercises/week11/sunset_sunrise_start)
  * Go to [ProjectZipGH](https://tinyurl.com/ProjectZipGH)
  * Paste this GitHub folder URL into the top right:
    `https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_exercises/week11/sunset_sunrise_start`

## Lab: Open-Meteo

* Download the [open-meteo_start project](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_exercises/week11/open-meteo_start)
  * Go to [ProjectZipGH](https://tinyurl.com/ProjectZipGH)
  * Paste this GitHub folder URL into the top right:
    `https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_exercises/week11/open-meteo_start`

## Useful Links

- [ArduinoJson Library](https://arduinojson.org/)
- [JSON Online Formatter](https://jsonformatter.org/json-pretty-print)
- [Mustache Tester](http://rickkas7.github.io/mustache/) for identifying JSON values

## Credit

- [Webhooks by DioT Labs](https://diotlabs.daraghbyrne.me/docs/working-with-data/webhooks)
