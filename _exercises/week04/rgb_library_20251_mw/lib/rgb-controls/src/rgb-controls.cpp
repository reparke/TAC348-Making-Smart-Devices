#include "application.h"
#include "rgb-controls.h"


namespace RGBControls {
  Color::Color(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;
  }

  Color Color::withBrightness(int brightness) {
    int r = red   * brightness / 100;
    int g = green * brightness / 100;
    int b = blue  * brightness / 100;
    return Color(r, g, b);
  }

  Color Color::lerp(Color to, float t) {
    int dR = (to.red - red) * t;
    int dG = (to.green - green) * t;
    int dB = (to.blue - blue) * t;
    return Color(red + dR, green + dG, blue + dB);
  }

  Led::Led(int rPin, int gPin, int bPin, bool isCathode) {
    _rPin = rPin;
    _gPin = gPin;
    _bPin = bPin;
    _step = 1;
    _isCathode = isCathode;
    pinMode(_rPin, OUTPUT);
    pinMode(_gPin, OUTPUT);
    pinMode(_bPin, OUTPUT);
  }

  void Led::setColor(Color c) {
    if (_isCathode) {
      analogWrite(_rPin, c.red);
      analogWrite(_gPin, c.green);
      analogWrite(_bPin, c.blue);
    } else {
      analogWrite(_rPin, 255 - c.red);
      analogWrite(_gPin, 255 - c.green);
      analogWrite(_bPin, 255 - c.blue);
    }
  }

  void Led::off() {
    Color black(0, 0, 0);
    setColor(black);
  }

  void Led::flash(Color c, int onTime, int offTime) {
    setColor(c);
    delay(onTime);
    off();
    delay(offTime);
  }

  void Led::flash(Color* colors, int length, int onTime, int offTime) {
    for (int n = 0; n < length; n++) {
      flash(colors[n], onTime, offTime);
    }
  }

  int n = 0;
  bool up = false;
  void Led::fade(Color* colors, int length, int duration) {
    float steps = duration / 25;
    if (_step == 0 || _step == steps) {
      n++;
      if (n >= length) {
        n = 0;
        up = !up && (length % 2 != 0);
      }
    }
    Color a = colors[n];
    Color b = colors[(n + 1 == length) ? 0 : n + 1];
    if ((n % 2 == 0) ^ up)
      fade(a, b, duration);
    else
      fade(b, a, duration);
  }

  void Led::fade(Color c1, Color c2, int duration) {
    float steps = duration / 25;
    Color nextColor = c1.lerp(c2, _step / steps);
    setColor(nextColor);
    delay(25);
    step(0, steps);
  }

  void Led::fadeOnce(Color c1, Color c2, int duration) {
    float steps = duration / 25;
    for (int i = 1; i <= steps; i++) {
      Color nextColor = c1.lerp(c2, i / steps);
      setColor(nextColor);
      delay(25);
    }
  }

  bool isIncreasing = true;
  void Led::step(int min, int max) {
    _step = _step + (isIncreasing ? 1 : -1);
    if (_step >= max || _step <= min) isIncreasing = !isIncreasing;
  }
}
