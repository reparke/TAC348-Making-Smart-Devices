#ifndef rgb_controls_h
#define rgb_controls_h

#include "application.h"


namespace RGBControls {
    class Color {
      public:
        Color(int r, int g, int b);
        Color withBrightness(int brightness);
        Color lerp(Color to, float t);
        int red;
        int green;
        int blue;
    };

    class Led {
      public:
        Led(int rPin, int gPin, int bPin, bool isCathode = true);
        void setColor(Color c);
        void fade(Color c1, Color c2, int duration);
        void fade(Color* colors, int length, int duration);
        void fadeOnce(Color c1, Color c2, int duration);
        void flash(Color c, int onTime = 200, int offTime = 200);
        void flash(Color* colors, int length, int onTime = 200, int offTime = 200);
        void off();
        void step(int min, int max);
      private:
        int _rPin;
        int _gPin;
        int _bPin;
        bool _isCathode;

        int _step;
        int _dir;
    };
}

#endif
