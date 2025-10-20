---
marp: true
theme: itp

week: 11
category: lectures
title: Creating JSON with ArduinoJson Library
---

<!-- headingDivider: 2 -->

# Creating JSON with `ArduinoJson` Library

## JSON Example Data

- Consider we want to send the following JSON data to a website

```json
[
 {"key":"temperature", "value":79.000000},
 {"key":"humidity", "value":22.000000},
 {"key":"weather", "value": "sunny"}
]
```

##  Creating JSON with a Library:  `ArduinoJson` 

- `ArduinoJson` is a popular library for generating JSON code and can be installed from **Workbench**

* Use the sample code below

### Configuration of `ArduinoJson`

- Import library and set up Arduino compatibility

```c++
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h> 
```

### Photon 2 code

```c++
void loop() {
  StaticJsonDocument<1024> doc; // object to store JSON response
  String output; 			   // will store JSON string which is used for Particle.publish()

  /* Here is where JSON creation code goes */
    //create first JSON object
  JsonObject obj0 = doc.createNestedObject();
  obj0["key"] = "temperature";
  obj0["value"] = 79.000000;

  //create second JSON object
  JsonObject obj1 = doc.createNestedObject();
  obj1["key"] = "humidity";
  obj1["value"] = 22.000000;

  //create third JSON object
  JsonObject obj2 = doc.createNestedObject();
  obj2["key"] = "weather";
  obj2["value"] = "sunny";

  serializeJson(doc, output); //create JSON string
  
  //make sure to change the event name below to match the webhook you created  
  Particle.publish("inital_state_json", output);
  delay(60000);	//use delay or millis to avoid publishing too frequently
}
```

## Reference

- [Mustache Variable Reference](https://docs.particle.io/firmware/best-practices/json/#mustache-variables)
- [JSONValue Reference](https://docs.particle.io/reference/device-os/api/json/parsing/#jsonvalue)
- [JSON Parsing Code Sample](https://community.particle.io/t/weather-api-tutorial/60528)
- [JSONWriter Reference](https://docs.particle.io/reference/device-os/api/json/jsonwriter/#jsonwriter-beginarray-)