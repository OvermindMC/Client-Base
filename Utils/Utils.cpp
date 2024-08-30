#include "Utils.h"

void Utils::reachOffset(float* offset, float target, float modifier) {
    if (*offset < target) {
        *offset += modifier;
        if (*offset > target) {
            *offset = target;
        };
    } else if (*offset > target) {
        *offset -= modifier;
        if (*offset < target) {
            *offset = target;
        };
    };
};

std::string Utils::sanitize(std::string& input_text) {
    bool wasValid = true;
    auto invalidChar = [](char c) -> bool {
        return !(c >= 0 && *reinterpret_cast<unsigned char*>(&c) < 128);
    };

    size_t outIndex = 0;

    for (size_t i = 0; i < input_text.length(); ++i) {
        char c = input_text[i];
        bool isValid = !invalidChar(c);
        if (wasValid) {
            if (!isValid) {
                wasValid = false;
            } else {
                input_text[outIndex++] = c;
            }
        } else {
            wasValid = isValid;
        };
    };

    input_text.resize(outIndex);
    return input_text;
};