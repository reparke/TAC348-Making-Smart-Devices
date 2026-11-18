#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <cassert>
#include <climits>
#include <iostream>
#include "json_webhook_response_helper.h"
unsigned long testMillis = 0;

void expect(const char* event, const char* data, const char* wanted) {
    String actual = json_webhook_response_helper(event, data);
    if (std::string(actual.c_str()) != wanted) {
        std::cerr << "Event " << (event ? event : "null") << ": got " << actual.c_str()
                  << ", expected " << wanted << '\n';
        std::abort();
    }
}
void fresh() { testMillis += 21001; }
int main() {
    expect("hook-response/weather/0", "{\"temperature\":72}", "{\"temperature\":72}");
    expect("hook-response/weather/0", "{\"temperature\":73}", "{\"temperature\":73}");

    // The regression: two interleaved webhook responses must stay separate.
    fresh();
    expect("hook-response/weather/0", "{\"temperature\":", "");
    expect("hook-response/gemini/0", "{\"description\":", "");
    expect("hook-response/weather/1", "72}", "{\"temperature\":72}");
    expect("hook-response/gemini/1", "\"sunny\"}", "{\"description\":\"sunny\"}");

    fresh();
    expect("hook-response/weather/2", "3]}", "");
    expect("hook-response/weather/0", "{\"values\":[", "");
    expect("hook-response/weather/0", "{\"values\":[", "");
    expect("hook-response/weather/1", "1,2,", "{\"values\":[1,2,3]}");

    // Four pending responses; a fifth cannot evict the first four.
    fresh();
    for (const char* event : {"a/0", "b/0", "c/0", "d/0"}) expect(event, "{\"n\":", "");
    expect("e/0", "{\"n\":5}", "");
    expect("c/1", "3}", "{\"n\":3}");
    expect("e/0", "{\"n\":5}", "{\"n\":5}");
    expect("a/1", "1}", "{\"n\":1}");
    expect("d/1", "4}", "{\"n\":4}");
    expect("b/1", "2}", "{\"n\":2}");

    // Activity on another webhook must not extend a stale webhook's timeout.
    fresh();
    expect("a/0", "{\"old\":", "");
    testMillis += 19000;
    expect("b/0", "{\"n\":", "");
    testMillis += 2001;
    expect("b/1", "2}", "{\"n\":2}");
    expect("a/1", "1}", "");
    expect("a/0", "{\"new\":", "{\"new\":1}");

    fresh();
    expect(nullptr, "{}", "");
    expect("a/0", nullptr, "");
    expect("", "{}", "");
    expect("a/10", "{}", "");
    expect("a/9999999999999999999999999", "{}", "");
    expect("a/1x", "{}", "");
    expect("/0", "{}", "");
    expect("a/0", "invalid JSON", "");
    expect("a/0", "{}", "{}");
    expect("hook-response/sunrise_sunset", "{\"rise\":\"06:00\"}", "{\"rise\":\"06:00\"}");
    expect("single_event", "{}", "{}");

    fresh();
    expect("ten/9", "8]}", "");
    expect("ten/0", "{\"n\":[", "");
    for (int i=1; i<9; ++i) {
        std::string event = "ten/" + std::to_string(i);
        std::string part = std::to_string(i-1) + ",";
        expect(event.c_str(), part.c_str(), i==8 ? "{\"n\":[0,1,2,3,4,5,6,7,8]}" : "");
    }

    // Unsigned clock arithmetic also works across millis() rollover.
    testMillis = ULONG_MAX - 1000;
    expect("wrap/0", "{\"n\":", "");
    testMillis = 1000;
    expect("wrap/1", "1}", "{\"n\":1}");
    std::cout << "PASS: single/multipart, interleaved webhooks, out-of-order/duplicate chunks, "
                 "four-stream capacity, independent timeouts, invalid input, unnumbered events, "
                 "ten chunks, buffer reuse, and clock rollover (ArduinoJson "
              << ARDUINOJSON_VERSION << ")\n";
}
