
<!-- headingDivider: 2 -->

Note: This specifically references using the MAX30101 sensor

# Smart Watch

<img src="lecture_smart_watch.assets/smart_watch.gif" alt="smart_watch" style="width:500px;" />

## Starting Project

  * For assembly and wiring, refer to [these instructions](guide_build_watch.md)
  * Download starting code: Go to [https://bit.ly/ProjectZip](https://bit.ly/ProjectZip)
    * Paste the following link into the top right
      https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_exercises/week12/smart_watch_30101_i2c_start

  ## What's Included

  * Libraries
    * Micro OLED
    * MAX30101 heart rate sensor
  * Bitmaps byte arrays for heart rate, clock, and weather (`.h` files)
  * Heart rate BPM calculation

## Detecting Heart Rate with MAX30101 Heart Rate / SpO2 Sensor

* Uses built-in LEDs to pulse light onto skin
* Measures light reflecting back
* Operates at 3.3v
* Uses I2C communication

##  States

* Three states: `TIME`, `WEATHER`, `HEART`
* Need to design `getNextState()` function
* Need to design `loadNextState()` function
* Need to support state transitions in `loop()`

## Heart Rate Screen

<img src="lecture_smart_watch.assets/screen.png" style="width:500px;" />



## Heart Rate Design Goals

* We want to always track heart beat so displayed as soon as heart screen loads (note: this is not power efficient)
* We want to eliminate "noisy-ness" (flucutations) in heart rate so we will average the last for approximation of the heart rate (**smoothing**)



## Heart Rate Algorithm

1. Calculate most recent heart BPM (`updateBPM()`)
2. Update OLED screen using `millis()` timer based on `HEART_SCREEN_UPDATE_MS`
   * If `beatAvg`is above threshold and `irValue` is above threshold 
     * Display BPM
   * Else display `---`
3. Display body temperature
4. Display battery voltage (we'll discuss this part later)

*If you want to display an image, you can use bitmap `heart16x12`*

## Time Screen

<img src="lecture_smart_watch.assets/time.jpg" style="width:500px;" />

## Time

1. `setup()`

  * Set current timezone `Time.zone(<<TIMEZONE>>);` ([timezone guide](https://greenwichmeantime.com/time-zone/definition/))
  * Enable DST `Time.beginDST();`

2. Draw clock bitmap `clock_16x12`

3. Display date format  ([formatting guide](http://www.cplusplus.com/reference/ctime/strftime/))
    <!-- String dateFormat = "%a %d";-->
  ```c++
  oled.println(Time.format(<<DATE_FORMAT_STRING>>));
  ```

4. Display time format ([formatting guide](http://www.cplusplus.com/reference/ctime/strftime/))
    <!-- String timeFormat = "%I:%M%p"; -->

    ```c++
    oled.println(Time.format(<<TIME_FORMAT_STRING>>));
    ```

*If you want to display an image, you can use bitmap `clock_16x12`*

## Weather Screen

<img src="lecture_smart_watch.assets/weather.jpg" style="width:500px;" />



## GPS Coordinates for Precise Weather Data

- You can get weather data based on GPS coordinates
- You can use a [Google Maps + Particle web hook integration](https://docs.particle.io/tutorials/integrations/google-maps/) to get approximate GPS coordinates
- For now, you can use USC's zip code `90089`

## Weather Display

1. Create Particle webhook
2. Connect to weather API
3. Parse JSON
4. Display data
5. Use bitmaps byte array in `bitmaps_weather.h`

## Note on Weather Codes

- Weatherstack reports the weather conditions with a 3 digit code, which we can use to determine with image to display
- The full list can be found in the [API documentation](https://weatherstack.com/site_resources/weatherstack-weather-condition-codes.zip)
- For simplicity, you can use the follow abridged logic
  - Rainy weather codes: 296, 302, or 308
  - Cloudy weather codes: 116, 119, or 122
  - Snowing weather code: 227
  - Any other code can default to sunny 

## Important Reading

- [Racial Bias in Pulse Oximetry Measurement](https://www.nejm.org/doi/10.1056/NEJMc2029240)

## References

* [MAX30101 datasheet](https://cdn.sparkfun.com/assets/8/1/c/9/0/MAX30101_Datasheet.pdf)
* [Particle Argon reference - software timers](https://docs.particle.io/reference/device-os/firmware/argon/#software-timers)

## Credit

- [Measure Heart Rate Project](https://create.arduino.cc/projecthub/SurtrTech/measure-heart-rate-and-spo2-with-max30102-c2b4d8) 
