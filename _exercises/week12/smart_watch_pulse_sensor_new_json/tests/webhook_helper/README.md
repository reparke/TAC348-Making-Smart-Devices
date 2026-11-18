These host tests exercise the actual project helper and bundled ArduinoJson parser. `Particle.h` and `Arduino.h` here are small host-only shims; they are not firmware libraries and must not be copied into `src`.

From the project directory, with a C++ compiler installed:

```sh
g++ -std=c++11 -Wall -Wextra -pedantic -Itests/webhook_helper -Isrc -Ilib/ArduinoJson/src tests/webhook_helper/test.cpp -o /tmp/webhook-helper-tests
/tmp/webhook-helper-tests
```

To check ArduinoJson 7.4.3 as used by the other examples, replace the ArduinoJson include path with `-I../../week11/sunset_sunrise_final/lib/ArduinoJson/src`.

Tests cover single and multipart responses, interleaved webhook names, out-of-order and duplicate chunks, capacity and buffer reuse, independent timeouts, invalid inputs, unnumbered events, ten-part responses, and unsigned-clock rollover. These tests do not replace an on-device flash test.
