---
marp: true
theme: tac

week: 11
category: lectures
title: Retrieving Data from APIs using Mustache Templates (optional)
---

<!-- headingDivider: 2 -->

# Retrieving Data from APIs using Mustache Templates

## Overview

- This is an **optional** step where you filter the JSON response in the Particle Cloud before sending it to the Photon 2
- This sends the Photon 2 only the data you want instead of the entire response
- Our class Open-Meteo webhook does not have a response template. This is an optional example.

##

<img src="lecture_retrieving_data_from_api.assets/Screenshot 2024-07-01 at 10.11.13 PM.png" alt="Focus on the JSON sent from the weather API to the Photon 2" style="width:1000px;" />

## Open-Meteo Response

* The [complete Open-Meteo response](lecture_retrieving_data_from_api.assets/open-meteo-los-angeles-response.json) contains location, units, and current weather data
* This is the `current` section of that real response, captured November 3, 2026 (Pacific time)

```json
{
  "current": {
    "time": "2026-11-03T22:45",
    "interval": 900,
    "temperature_2m": 59.9,
    "relative_humidity_2m": 74,
    "precipitation": 0.0,
    "weather_code": 0,
    "wind_speed_10m": 4.8
  }
}
```

## What if We Only Want the Temperature?

* The temperature is inside the `current` object
* Its path in the response is `current.temperature_2m`
* A webhook response template can send just that value

## Create a Mustache Response Template

* If you want to try this, create a separate test webhook in [Particle Console Integrations](https://console.particle.io/integrations)
* Find **Webhook Responses → Response Template**
* Put the template below in that field

<!-- {% raw %} -->
```json
{"temp":{{{current.temperature_2m}}}}
```
<!-- {% endraw %} -->

The triple braces insert the value without changing it to HTML text. For this example, `59.9` stays a JSON number.

## What the Photon 2 Receives

For the captured Open-Meteo response, the template produces:

```json
{"temp":59.9}
```

* The response is smaller, but the JSON shape has changed
* With this template, read the temperature using `doc["temp"]`
* Without the template, use `doc["current"]["temperature_2m"]` as shown in the [JSON parsing lecture](lecture_json_parsing_with_arduinojson)

## Subscribe to the Response

**Photon 2 firmware**

```c++
void setup() {
  Particle.subscribe("hook-response/open_meteo_json",
                     myHandler, MY_DEVICES);
}
```

The event name stays the same. The response template changes only the JSON sent back to the device.

## Resources

* [Particle webhook response templates](https://docs.particle.io/reference/cloud-apis/webhooks/#responsetemplate)
* [Particle Mustache variables](https://docs.particle.io/firmware/best-practices/json/#mustache-variables)
* [Open-Meteo documentation](https://open-meteo.com/en/docs)
