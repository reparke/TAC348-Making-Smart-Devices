#include "rgb-controls.h"
using namespace RGBControls;

Led led(D0, D1, D2);
Color purple(150, 0, 150);


void setup() {
  // Flash the led purple 3 times with the default on / off times
  for (int i = 0; i < 3; i++) {
    led.flash(purple);
  }
}

void loop() { }
