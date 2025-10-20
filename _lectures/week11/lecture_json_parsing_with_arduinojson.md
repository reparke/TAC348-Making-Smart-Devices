---
marp: true
theme: itp

week: 11
category: lectures
title: Parsing JSON with ArduinoJson Library
---
<!-- headingDivider: 2 -->

# Parsing JSON with `ArduinoJson` Library

## JSON Example Data

- Consider the following JSON data is being received by the Photon 2

```json
{
  "place": {
    "city": "los angeles",
    "state": "california"
  },
  "temperature": [
    78,
    89,
    93,
    77
  ]
}
```



## Parsing JSON with a Library:  `ArduinoJson` 

- `ArduinoJson` is a popular library for parsing JSON code and can be installed from **Workbench**
* Use the sample code below for your event handler
* The first part allows for responses from the webhook that come in multiple parts (you don't need to change this)
* The second part is where you can adapt your own code

### Configuration of `ArduinoJson`

- Import library and set up Arduino compatibility

```c++
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h> 
```

## Publishing and Subscribing

```c++
void setup() {
  // Subscribe to the integration response event
  Particle.subscribe("hook-response/JSONWeatherStack", myHandler,
                     MY_DEVICES);
}

void loop() {
  // Get some data
  String data = "90089";
  // Trigger the integration
  Particle.publish("JSONWeatherStack", data, PRIVATE);
  // Wait 60 seconds
  delay(60000);
}
```



## Parsing with `ArduinoJson`

### Example: Consider the following JSON

```json
{
  "place": {
    "city": "los angeles",
    "state": "california"
  },
  "temperature": [
    78,
    89,
    93,
    77
  ]
}
```

### Configuration of `ArduinoJson`

- Import library and set up Arduino compatibility
```c++
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h> 
```



### Configuration of Event Handler
- The JSON will be passed to the `data` parameter of event handler 
```c++
void myHandler(const char *event, const char *data) {
```


Here is an example

```c++
void myHandler(const char *event, const char *data) {
  	//declare object to store JSON response
	StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);
    
    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }
    
    /* Here is where your parsing code goes */
    
    String city = doc["place"]["city"];  // "los angeles"
    int temp = doc["temperature"][1];  // 89
    Serial.println("The second temperature for " + city + " is " + String(temp));
}
```
## Useful Links

- [ArduinoJson Library](https://arduinojson.org/)
- [JSON Online Formatter](https://jsonformatter.org/json-pretty-print)
- [Mustache Tester](http://rickkas7.github.io/mustache/) for identifying JSON values

## Credit

- [Webhooks by DioT Labs](https://diotlabs.daraghbyrne.me/docs/working-with-data/webhooks)
