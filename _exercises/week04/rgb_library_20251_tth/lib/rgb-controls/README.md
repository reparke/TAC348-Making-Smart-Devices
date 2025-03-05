# RGB Controls for Particle.io
Particle.io library for controlling RGB LEDs


## Quick Start

1. [Add the library to your project](https://docs.particle.io/photon/build/#flash-apps-with-particle-build-using-libraries)

2. Connect your RGB led to pins D0, D1, and D2 (Assuming Photon board)
3. Copy the code below into a new project and flash it to your board
  ```c++
  #include "rgb-controls/rgb-controls.h"
  using namespace RGBControls;

  // RGB led on PWN pins
  Led led(D0, D1, D2); // red_pin = D0, green_pin = D1, blue_pin = D2

  Color red(255, 0, 0);
  Color blue(0, 0, 255);

  void setup() { }

  void loop() {
    // Fade the led light between red and blue every 5 seconds
    led.fade(red, blue, 5000);
  }
  ```

4. Your RGB led will now fade from red to blue!

## Led Methods

#### constructor(int rPin, int gPin, int bPin [, bool isCathode])
Initalize an `Led` with 3 PWM pins

Parameter | Description | Example
--- | --- | ---
rPin | The pin number attached to the red leg of the led | `D0`
gPin | The pin number attached to the green leg of the led | `D1`
bPin | The pin number attached to the blue leg of the led | `D2`
isCathode | Boolean whether the rgb led is common cathode `optional` | `true` (default)

```c++
// Create a common cathode led
Led led(D0, D1, D2);

// Create a common anode led
Led led(D0, D1, D2, false);
```

#### setColor(Color color)
Set the led to `color`

```c++
// Make the led light magenta
led.setColor(Color(255, 0, 255))
```

#### fade(Color c1, Color c2, int duration)

Fade from `c1` to `c2` in `duration` milliseconds. **Must be called in a `void loop()`.**

Parameter | Description | Example
--- | --- | ---
c1 | The color to fade from | `Color(255, 0, 0)`
c2 | The color to fade to | `Color(0, 0, 255`
duration | The duration of the fade in ms | `3000`

```c++
Color red(255, 0, 0);
Color blue(0, 0, 255);

// Fade the led back and forth between red to blue every 3 seconds
void loop() {
  led.fade(red, blue, 3000);
}
```


#### fade(Color* colors, int length, int duration)

Fade between each color in  in `duration` milliseconds. **Must be called in a `void loop()`.**

Parameter | Description | Example
--- | --- | ---
colors | An array of colors | See below
length | The length of the colors array | `3`
duration | The duration of the fade in ms | `3000`

```c++
Color red(255, 0, 0);
Color green(0, 255, 0);
Color blue(0, 0, 255);

Color colors[3] = { red, green, blue };

// Fade the led back and forth between colors in the array every 3 seconds
void loop() {
  led.fade(colors, 3, 3000);
}
```

#### fadeOnce(Color c1, Color c2, int duration)

Fade from `c1` to `c2` in `duration` milliseconds

Parameter | Description | Example
--- | --- | ---
c1 | The color to fade from | `Color(255, 0, 0)`
c2 | The color to fade to | `Color(0, 0, 255`
duration | The duration of the fade in ms | `3000`

```c++
Color red(255, 0, 0);
Color blue(0, 0, 255);

// Fade the led from red to blue in 3 seconds
led.fadeOnce(red, blue, 3000);
```

#### flash(Color color [, int onTime, int offTime])

Flash `color` on for `onTime` ms and off for `offTime` ms

Parameter | Description | Example
--- | --- | ---
color | The color to flash | `Color(255, 0, 0)`
onTime | The time in ms that the light is on `optional` | `200` (default)
offTime | The time in ms that the light is off `optional`| `200` (default)

```c++
// Flash red using the default on and off times
led.flash(Color(255, 0, 0));

// Flash blue on for 1 second and off for 100 ms
led.flash(Color(0, 255, 0), 1000, 100);
```

#### flash(Color* colors, int length [, int onTime, int offTime])

Flash an array of `colors` on for `onTime` ms and off for `offTime` ms

Parameter | Description | Example
--- | --- | ---
colors | The array of color to pulse | See below
length | The length of the color array | `3`
onTime | The time in ms that the light is on `optional` | `200` (default)
offTime | The time in ms that the light is off `optional`| `200` (default)

```c++
Color red(255, 0, 0);
Color green(0, 255, 0);
Color blue(0, 0, 255);

Color colors[3] = {red, green, blue};

// Flash the colors one after another using default on and off times
led.flash(colors, 3);

// Flash the colors one after another on for 500 ms and off for 1000 ms
led.flash(colors, 3, 500, 1000);
```


#### off()

Shut off the led

```c++
// Turn off the led
led.off();
```

## Color Methods

#### constructor(int red, int green, int blue)

Initialize a `Color` with 3 RGB color values

Parameter | Description | Example
--- | --- | ---
red | The RGB red value `0 to 255` | `0`
green | The RGB green value `0 to 255` | `255`
blue | The RGB blue value `0 to 255` | `120`

```c++
Color red(255, 0, 0);
Color orange(255, 165, 0);
Color white(255, 255, 255);
```

#### withBrightness(int brightness)
Returns a new color with desired brightness percentage

Parameter | Description | Example
--- | --- | ---
brightness | The desired brightness percentage of the color | `20`

```c++
Color orange(255, 165, 0);

orange.withBrightness(20); // returns Color(51, 33, 0)
```


#### lerp(Color to, float t)

Linearly interpolates between two colors

Parameter | Description | Example
--- | --- | ---
to | The Color to lerp to | `Color(0, 0, 255)`
t | The fraction clamped to range `[0...1]` | `0.5`

```c++
Color red(200, 0, 0);
Color blue(0, 0, 200);

red.lerp(blue, 0.5); // returns Color(100, 0, 100)
```
