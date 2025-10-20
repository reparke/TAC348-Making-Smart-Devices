---
marp: true
theme: itp

week: 11
category: lectures
title: Sending Multiple Values to Initial State using JSON
---

<!-- headingDivider: 2 -->

# Sending Multiple Values to Initial State using JSON

![bg opacity:.75](lecture_sending_initial_state_json.assets/Infruid's_Self-Service_BI_Tool_Dashboard.jpg)

## Review

<img src="lecture_sending_initial_state_json.assets/Screenshot 2024-06-22 at 1.00.51 AM.png" alt="Screenshot 2024-06-22 at 1.00.51 AM" style="width:1100px" />



## Review

<img src="lecture_sending_initial_state_json.assets/Screenshot 2024-06-22 at 1.02.00 AM.png" alt="Screenshot 2024-06-22 at 1.02.00 AM" style="width:1100px" />



## Goal: Use JSON to send Multiple Values to Initial State at Once 

* It is faster and uses less bandwidth to send multiple sensor in a single package
* We will use JSON to package all the data and send to Initial State
* The following examples are provided as a quick reference
* More detailed steps are described in the lecture 

## Reminder: Steps to Connect Photon 2 and Initial State 

1. Create account at  [https://initialstate.com](https://initialstate.com) 
2. Create **stream bucket** at [https://initialstate.com](https://initialstate.com)  
3. Create an integration -> webhook on [Particle console](https://console.particle.io/integrations) 
4. Write firmware sketch and flash Photon 2

## Configure Initial State to Receive JSON 

**Initial State Settings**

<img src="lecture_sending_initial_state_json.assets/image-20200703180348874.png" alt="image-20200703180348874" style="width:500px;" />

## Configure Particle Cloud to Pass JSON

**Particle integration settings**

<img src="lecture_sending_initial_state_json.assets/image-20200703160032339.png" alt="image-20200703160032339" style="width:600px;" />

## Configure Particle Cloud to Pass JSON  

**Particle integration settings**

{% comment %} This code below is because Liquid breaks with the triple brackets {% endcomment %}
{% assign liquid_code_block = '{{{PARTICLE_EVENT_VALUE}}}' %}

JSON Data: `{{ liquid_code_block }}`

URL: `https://groker.init.st/api/events`

<img src="lecture_sending_initial_state_json.assets/image-20200703180944077.png" alt="image-20200703180944077" style="width:500px;" />

## Configure Particle Cloud to Pass JSON

**Particle integration settings**

<img src="lecture_sending_initial_state_json.assets/SNAGHTML22743719.PNG" alt="img" style="width:500px;" />



## Configure Particle Cloud to Pass JSON

**Particle integration setting: HTTP Headers**

`X-IS-AccessKey`	>	*<<USE YOUR OWN API KEY>>>*

`X-IS-BucketKey`	>	*<<USE YOUR OWN BUCKET KEY>>>*

<!--`Accept-Version`	>	`~0`      ***note: this is a tilde ~, NOT a hyphen -*** -->





## Creating JSON

- To create JSON data, it is recommended to use a library such as `ArduinoJson` or `JsonParserGeneratorRK`
- You can also use `String` variables to manually build the JSON data, but this can be tedious and error-prone so it is not recommended
- [Instruction and examples for creating JSON with ArduinoJson](lecture_json_creation_with_arduinojson)

## Exercise - Send Multiple Values to Initial State

* Generate random temperature and humidity
* Send to Initial State with one JSON value



## Credits

* [Growthlakes](https://commons.wikimedia.org/wiki/File:Infruid%27s_Self-Service_BI_Tool_Dashboard.jpg)  [CC BY-SA](https://creativecommons.org/licenses/by-sa/4.0)
* Image created with [Fritzing](https://fritzing.org)