#include "rgb-controls.h"
using namespace RGBControls;

Led led(D0, D1, D2);
Color red(255, 0, 0);
Color green(0, 255, 0);
Color blue(0, 0, 255);

Color yellow(255, 255, 0);
Color magenta(255, 0, 255);
Color cyan(0, 255, 255);

Color colors[6] = {red, green, blue, yellow, magenta, cyan};


void setup() { }

void loop() {
  // Flash all lights in the array for 1 second with 0 ms off time
  led.flash(colors, 6, 500, 0);
}
