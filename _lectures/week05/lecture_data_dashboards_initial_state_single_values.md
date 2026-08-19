---
marp: true
theme: itp

week: 5
category: lectures
title: Data Visualization and Dashboard with Initial State (Single Values)
---

<!-- headingDivider: 2 -->

# Data Visualization and Dashboards with Initial State 

![bg opacity:.75](lecture_data_dashboards_initial_state_single_values.assets/Infruid's_Self-Service_BI_Tool_Dashboard.jpg)

## What do we do with all this data?

* A single IoT device can generate significant of sensor data
* A fleet of thousands of devices compounds this
* A **dashboard** can help provide visual feedback and control over our IoT devices and data

## Example Environmental Dashboard

<img src="lecture_data_dashboards_initial_state_single_values.assets/image-20200724004339825.png" alt="image-20200724004339825" style="width:500px;" /><img src="lecture_data_dashboards_initial_state_single_values.assets/image-20200724005050658.png" alt="image-20200724005050658" style="width:600px;" />

## Uses of Dashboards

* View real-time sensor data
* Compare data to historical trends
* Monitor IoT devices for errors or network issues
* Map devices GPS location
* Remote control (execute functions) on devices

## Dashboard Platforms

* [Google Cloud IoT](https://cloud.google.com/solutions/iot) (many IoT services)
* [Microsoft Azure IoT](https://azure.microsoft.com/en-us/overview/iot/) (many IoT services)
*  [Amazon Web Services](https://aws.amazon.com/iot/) (many IoT services)
* [Losant](https://www.losant.com/) (many IoT services)
* [Ubidots](https://ubidots.com/)
* [Tinamous](https://www.tinamous.com/)
* [Initial State](https://www.initialstate.com/)

## Initial State ([https://initialstate.com](https://initialstate.com))

* Initial State is a data visualization service for IoT
* Send data from Photon 2 to be stored at Initial State 
* Create complex graphs and dashboards with the values from your Photon 2
* Initial State can also send SMS and email alerts based on the data (though this requires a paid plan)

## Initial State

* **Important:** Initial State used to be free for students
  * Now it only offers a 30 free trial 🥺
* **How does this affect us?**
  * Make an account, use it for 30 days for an assignment
  * When you need to use it again, make another free account with a different email
* **Is this annoying?**
  * Yes. But there isn't a replacement that is both free and as-easy to use as Initial State

## Configuring Photon 2 and Initial State 

* The following examples are provided as a quick reference
* More detailed steps are described in the lecture 

## Steps to Connect Photon 2 and Initial State 

1. Create account at  [https://initialstate.com](https://initialstate.com) (make sure to use your student email and change ) 
2. Create **stream bucket** at [https://initialstate.com](https://initialstate.com)  
3. Create an integration -> webhook on [Particle console](https://console.particle.io/integrations) 
4. Write firmware sketch and flash Photon 2

## Aside: Access Key (or API key)

* Many webservices require you to register and then they provide you with an API key (ex: `zaCELgL. 0imfnc8mVLWwsAawjYr4Rx-Af50DDqtlx`)
* This randomly-generated string serves as the login and password (credentials) to your account
* Purposes
  * Account security (no one but you can read / write data)
  * Prevent abuse / hacking
  * Throttling / account limits (enforce limits on read/write frequency)

## Example 1: Send Single Data Point from Photon 2 to Initial State

**Initial State Settings**

![img](lecture_data_dashboards_initial_state_single_values.assets/SNAGHTMLf87d3e3.PNG)



## Example 1: Send Single Data Point from Photon 2 to Initial State

**Particle integration settings**

![image-20210201152825606](lecture_data_dashboards_initial_state_single_values.assets/image-20210201152825606.png)

## Example 1: Send Single Data Point from Photon 2 to Initial State

**Particle integration settings**

{% comment %} This code below is because Liquid breaks with the triple brackets {% endcomment %}
{% assign liquid_code_block = '{{{PARTICLE_EVENT_VALUE}}}' %}
`YOUR_CUSTOM_DATA_LABEL `     >      `{{ liquid_code_block }}`


![img](lecture_data_dashboards_initial_state_single_values.assets/SNAGHTMLf92f8fa.PNG)





## Example 1: Send Single Data Point from Photon 2 to Initial State

**Photon 2 code**

```c++
double temp;

void loop() {
  temp = 89;		//just example; temp should come from sensor
    
  // Trigger the integration
  Particle.publish("inital_state_single", String(temp), PRIVATE);
  delay(60000);	//use delay or millis to avoid publishing too frequently
}
```



## Exercise - Send Temperature Value to Initial State

* Connect TMP 36 to Photon 2
* Read temperature value and send to Initial State

## Exercise  - Send Temperature Value to Initial State

<img src="lecture_data_dashboards_initial_state_single_values.assets/Screenshot 2024-06-03 at 2.28.35 PM.png" alt="Screenshot 2024-06-03 at 2.28.35 PM" style="width:500px;" />

## Credits

* [Growthlakes](https://commons.wikimedia.org/wiki/File:Infruid%27s_Self-Service_BI_Tool_Dashboard.jpg)  [CC BY-SA](https://creativecommons.org/licenses/by-sa/4.0)
* Image created with [Fritzing](https://fritzing.org)