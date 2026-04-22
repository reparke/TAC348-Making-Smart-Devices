---
marp: true
theme: itp

week: 16
category: lectures
title: Particle + Gemini Integration
---

## Create Google Cloud Project

* Visit [Google Cloud Console](https://console.cloud.google.com/)
* Create new project

![image-20251118221334538](lecture_particle_gemini_integration.assets/image-20251118221334538.png)

## Activate Generate Language API / Gemini API

* In the search box, type **Gemini API** and select the name in the dropdown

![image-20251118221648990](lecture_particle_gemini_integration.assets/image-20251118221648990.png)

* Click **Enable**

![image-20251118221732265](lecture_particle_gemini_integration.assets/image-20251118221732265.png)

## Create API key for Generate Language API / Gemini

* On the left, click **Credentials** and then click **+ Create credentials**

![image-20251118222003205](lecture_particle_gemini_integration.assets/image-20251118222003205.png)

* Copy API key

![image-20251118222330583](lecture_particle_gemini_integration.assets/image-20251118222330583.png)

* Click **Edit API key**
* On the next page, do the following
  * Give the key a meaningful name
  * Under **API restrictions** click **Restrict key**
  * Click the dropdown box and type **Generate Language API**
* It may take 5-10 for key to be active



## Create Particle Webhook

* Go to [Particle console](https://console.particle.io/)
* Go to Cloud Services > Integration > Create custom webhook
* Use the following settings
  * **Name**: a meaningful description (for you) 
  * **Event name**: the specific event you want to publish to in your code
  * **URL**: `https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent`
  * Request type: `POST`
  * Request body: `JSON`
* Go to **Extra Settings**, and under **JSON Body** add

```json
{
  "contents": [
    {
      "parts": [
        {
          "text": "You are a concise, witty weather assistant. Based on a weather code of {{code}}, a humidity percentage of {{humidity}}, and a temperature of {{temp}} degrees Fahrenheit, provide a single, short, descriptive phrase (max 10 words). Do not include the code or temperature in your final phrase. For example, 'A beautiful 76 degrees for a Sunday stroll.'"
        }
      ]
    }
  ]
}   ]
    }
  ]
}
```

* Under **Query Parameters**, add
  * **Key: ** `key`
  * **Value:** `YOUR_API_KEY_FROM_GOOGLE_CLOUD_CONSOLE"



* Send JSON

```json
{"temp":49.900002, "code":0, "humidity":84}
```



* Sample response

```json
Clear, cool, and surprisingly sticky.
```



* Notes
  * There seem to be quota issues about too many messages per second