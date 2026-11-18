#pragma once
// Host-only stand-in for the Particle String operations used by the helper.
#include <string>
#include <cstddef>
class String {
    std::string value;
public:
    String() = default;
    String(const char* text) : value(text ? text : "") {}
    String(const std::string& text) : value(text) {}
    bool concat(const char* text) { value += text; return true; }
    const char* c_str() const { return value.c_str(); }
    unsigned int length() const { return static_cast<unsigned int>(value.size()); }
    char operator[](unsigned int index) const { return value[index]; }
    int lastIndexOf(char c) const {
        auto pos = value.rfind(c);
        return pos == std::string::npos ? -1 : static_cast<int>(pos);
    }
    String substring(unsigned int start) const { return value.substr(start); }
    String substring(unsigned int start, unsigned int end) const { return value.substr(start, end - start); }
    String& operator+=(const String& other) { value += other.value; return *this; }
    bool operator==(const String& other) const { return value == other.value; }
};
extern unsigned long testMillis;
inline unsigned long millis() { return testMillis; }
