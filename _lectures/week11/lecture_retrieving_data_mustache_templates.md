---
marp: true
theme: itp

week: 11
category: lectures
title: Retrieving Data from APIs using Mustache Templates (optional)
---

<!-- headingDivider: 2 -->

# Retrieving Data from APIs using Mustache Templates

## Overview

- This is an **optional** step where you filter the JSON response in the Particle cloud before sending the JSON resposne to the Photon 2
- This saves processing and bandwidth because you are only sending the Photon 2 the exact JSON data you want, not the whole JSON response
- This is a good practice, but not explicitly required in our class.



## Part 3: Subscribe to JSON response from Weather Stack

**Photon 2 firmware**

```c++
void setup() {
  // Subscribe to the integration response event
  Particle.subscribe("hook-response/JSONWeatherStack",
                      jsonSubscriptionHandler, MY_DEVICES);
}
```

## 

<img src="lecture_retrieving_data_from_api.assets/Screenshot 2024-07-01 at 10.11.13 PM.png" alt="Screenshot 2024-07-01 at 10.11.13 PM" style="width:1000px;" />

## 

<img src="lecture_retrieving_data_from_api.assets/Screenshot 2024-07-01 at 10.15.08 PM.png" alt="Screenshot 2024-07-01 at 10.15.08 PM" style="width:1000px;" />

## 

<img src="lecture_retrieving_data_from_api.assets/Screenshot 2024-07-01 at 10.16.55 PM.png" alt="Screenshot 2024-07-01 at 10.16.55 PM" style="width:1000px;" />

## 

<img src="lecture_retrieving_data_from_api.assets/Screenshot 2024-07-01 at 10.19.36 PM.png" alt="Screenshot 2024-07-01 at 10.19.36 PM" style="width:1000px;" />

## 

<img src="lecture_retrieving_data_from_api.assets/Screenshot 2024-07-01 at 10.22.14 PM.png" alt="Screenshot 2024-07-01 at 10.22.14 PM" style="width:1000px;" />



## Part 4 : Create Mustache template

- Often we might only want a few items from the JSON, but the webserver sends the entire message
- This extra data can waste time, bandwidth, power, and the response size can create errors
- Instead, we can have Particle webserver send us only the data we actually want by creating **Mustache templates**

<!-- Inserting a variable with double braces {{a}} will do HTML escaping of the characters &<>"'. To avoid this, use triple braces {{{a}}} -->

## Example: Entire Weather Stack JSON Response

![image-20200405005641533](lecture_retrieving_data_from_api.assets/image-20200405005641533.png)

## Example: What if we only want the temperature?

![right:50%](lecture_retrieving_data_from_api.assets/image-20200405005641533_temperature.png)



### Creating Mustache Webhook Response Templates

**Particle Console Webhook**

![image-20231012134414124](lecture_retrieving_data_from_api.assets/image-20231012134414124.png)

## Example: Mustache Format

![right:50%](lecture_retrieving_data_from_api.assets/image-20200405005641533_temperature.png)

- If we are only interested in the `temperature` value which is nested in the `current` object, we could create a template like the following

```json
  {"temp":"{{{current.temperature}}}"}
```

- Now instead of the server sending entire JSON response, it will only send the following
```json
  {"temp":"61"}
```

- For webhook response templates, make sure the template will always result in valid JSON (i.e. `{"name":"value"}`)

## Part 5: Creating the function handler to receive and parse the JSON

* The last step is to create Photon 2 code to handle / parse the JSON response
* While it is possible to manually parse JSON in C++, it is considered unsafe due to potential for security vulnerabilities
* **Instead, use a library**
* [Instruction and examples for parsing JSON with `ArduinoJson`](lecture_json_parsing_with_arduinojson)



<!--Since JSON is `String` data, it is possible to parse it using C-language techniques like `strtok`, `strcpy`, `atoi` 
However Buffer overrun if the response from the webserver was larger than expected or malformed-->



## Resources

* [Mustache Tester](https://rickkas7.github.io/mustache/)
* [Mustache Variable Reference](https://docs.particle.io/firmware/best-practices/json/#mustache-variables)
* [JSON Validator and formatter](https://jsonformatter.org/) 
* [Weatherstack documentation](https://weatherstack.com/documentation)

## Credits

* Photo by [Inset Agency](https://unsplash.com/@inset_agency?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText) on [Unsplash](https://unsplash.com/s/photos/rain-umbrella?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText)



<!--Alternate weather integration service
http://303.itpwebdev.com/~molld/assignment6/list.html
http://303.itpwebdev.com/~molld/assignment6/main.js
 -->