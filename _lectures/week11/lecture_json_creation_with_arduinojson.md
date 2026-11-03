---
marp: true
theme: tac

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
- Our goal is to create the JSON string shown above, then send it with `Particle.publish()`

## Step 1: Create the JsonDocument

```c++
JsonDocument doc;
```

- This container will store all the JSON data we are creating before we publish it


## Step 2: Create the Outer Array

- In the JSON example at the top, the outer container is a JSON **array** and starts with `[` and ends with `]`

```json
[
    
]
```
- We start by creating the same outer container in C++:

```c++
JsonArray readings = doc.to<JsonArray>();
```

## Step 3: Add the First Object

- The first item inside the array is a JSON **object** and starts with `{` and ends with `}`
```json
[
 {"key":"temperature", "value":79.000000}
]
```
- Add an object to the array, then give it a key and value:

```c++
JsonObject obj0 = readings.add<JsonObject>();
obj0["key"] = "temperature";
obj0["value"] = 79.000000;
```

## Configuration of `ArduinoJson` Library

- Import library and set up Arduino compatibility (make sure these lines go AFTER `#include "Particle.h`")

```c++
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h> 
```

## Photon 2 code Example

```c++
void loop() {
  JsonDocument doc; // container for our JSON data
  JsonArray readings = doc.to<JsonArray>(); // create the outer array [ ]
  String output; // will store the JSON string for Particle.publish()

  /* Here is where JSON creation code goes */
  //create first JSON object inside the array
  JsonObject obj0 = readings.add<JsonObject>();
  obj0["key"] = "temperature";
  obj0["value"] = 79.000000;

  //create second JSON object
  JsonObject obj1 = readings.add<JsonObject>();
  obj1["key"] = "humidity";
  obj1["value"] = 22.000000;

  //create third JSON object
  JsonObject obj2 = readings.add<JsonObject>();
  obj2["key"] = "weather";
  obj2["value"] = "sunny";

  serializeJson(doc, output); //create JSON string
  
  //make sure to change the event name below to match the webhook you created  
  Particle.publish("initial_state_json", output);
  delay(60000);	//use delay or millis to avoid publishing too frequently
}
```

## Reference

- [Mustache Variable Reference](https://docs.particle.io/firmware/best-practices/json/#mustache-variables)
- [JSONValue Reference](https://docs.particle.io/reference/device-os/api/json/parsing/#jsonvalue)
- [JSON Parsing Code Sample](https://community.particle.io/t/weather-api-tutorial/60528)
- [JSONWriter Reference](https://docs.particle.io/reference/device-os/api/json/jsonwriter/#jsonwriter-beginarray-)
