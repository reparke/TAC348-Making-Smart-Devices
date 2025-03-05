#include "rgb-controls.h"
using namespace RGBControls;

Led led(D0, D1, D2);
Color red(255, 0, 0);
Color green(0, 255, 0);
Color blue(0, 0, 255);

Color colors[3] = { red, green, blue };


void setup() { }

void loop() {
  // Fade between each color in the array every 3 seconds
  led.fade(colors, 3, 3000);
}
