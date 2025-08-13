---
marp: true
theme: itp

week: 16
category: lectures
title: Losant Cloud Platform and Interface
---

<!-- headingDivider: 2 -->

# Losant Cloud Platform and Interface

## Losant IoT Platform

* What is it? 
* Overview of component parts
* Integrate MCU with virtual device
* Build a workflow for storing data
* Build a dashboard
* Deploy a web app
* Control device from platform



## Key Terms

## Applications

* Includes all your IoT devices and workflow related to a project
* Ex: All the connected devices in your home such as temperature sensors, garage door openers, pet feeder

## Devices

* Device or sensor that communicates with Losant
* Ex: One Photon 2 that monitors the temperature and humidity in your living room

### Device attribute

* A piece of data associated with a device
* Ex: The temperature in your living room

## Integration

* Connection between Losant and external data source that allows data to securely from a web service to Losant
* Ex. Connect Particle Cloud to Losant. Data will flow from Photon 2 --> Particle Cloud --> Losant

### Integration Events

* Events that trigger Losant
* Ex. Particle.publish() events

## Workflows

* The "brains" of your app
* Allow you to specify where data (device attributes) go and are used
* Ex: Store temperature data

## Workflow Elements

* Trigger: event that causes an action
* Logic: code elements (e.g. conditions, functions)
* Data
* Outputs

## Dashboards

* Allow you to view stats, graphs, events and devices across multiple applications
* Ex. Visualize the temperature and light level in your home 

## Lab

* [Download project: Go to [https://bit.ly/ProjectZip](https://bit.ly/ProjectZip)

* Paste the following link into the top right
  https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_exercises/week11/losant_temperature_start) 

* Create account at [Losant](https://accounts.losant.com/signin) (we will go through the steps together)

* Create application 
  <!-- up to 20 in free version-->

* Create device for each Photon 2
  <!-- 
  Go to Particle console > select device > copy device id (if multiple devices) -->
  
  * Go to Losant and create standalone device 
    <!-- For tag: particle_device_id = <<ID>> (if multiple devices) -->
  * Attributes
    * define **temperature_fahr** as **number**
    * define **lightLevel** as **string**
  
* Create integration

  * Go to [particle web console](https://build.particle.io/build/new) > settings > personal access token
  * Go to Losant and create new integration
    * Integration type: **particle**
    * Paste access token
    * Leave configuration blank
    * Event name: **temperature** and **light** (must be same name as Particle.publish())

* Create publish event in firmware code

  <!-- Particle.publish("readings", String(f, 1) + ":" + lightLevel); -->

* Create workflow

  * Add trigger: **Particle**
    
    * set integration to Particle integration you made
      <!--Need to extract data from payload  so connect debug node and demonstrate-->
    
  * Create **function** to split data
  
    <!--var elements = payload.data.data.split(":");
    payload.data.tempF = elements[0];
    payload.data.light = elements[1]; -->
  
  * Add output: **device state**
    
    * individual fields: {{data.lightLevel}} and {{data.tempF}}
  
* Create dashboard

  * Add gauge for temperature
    <!--Live stream; 
    Gauge: Thermometer range 60-100; 
    Precision: Floating point 1 digit-->

  * Add conditions to temperature

    <!-- set color to green; set condition {{value}} > 76 is red; set condition {{value}} > 74 is yellow -->

  * Add historical chart of temperature

  * Add light level indicator

* Create experience (web app)

  * Go to overview --> Accept defaults (save URL, password, and login)
  * Create page
    * Edit > add page
    * Page type: dashboard
  * Create endpoint
    * Edit > add endpoint
    * Method: get
    * Route: /environment (*this is the URL for the dashboard*)
    * Access control: any authenticated users
    * Unauthorized reply: no static reply
    * Reply type: Experience page
      * Status code: 200
      * Select: Dashboard
    * Now log into website and visit 
      **https://<<YOUR_URL>>/environment**
  * Control device from dashboard
    
    * Create particle function in firmware
      <!--int ledChange(String cmd)  -->
    
    * Create Workflow
    
      * Virtual button
      * Particle function
        * function name **ledChange**
        * device id: <<COPY FROM PARTICLE CONSOLE>>
        * Function argument: String template -> argument template = "**blink**"
    
    * Create input control in Dashboard
    
      * Add input control
    
      * Virtual button
    
      * on Click: trigger workflow -> select correct workflow and virtual button
    
        <!-- dropdown and text input is possible, but more complicated -->
    
    * Events
    
      * Workflow: Connect **create event** to end of virtual button chain
        * Subject: LED off
        * Level: error
        * Message: Light is off
        * ID template
      * Create new chain: **Event**
        * Level: Error
        * Subject: LED off
      * Connect SMS 
        * Note that max of 5 messages per minute
      * Trigger workflow
    
