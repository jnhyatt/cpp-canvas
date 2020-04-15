#include "util.h"

vec4 parseHexColor(const std::string& color) {
    vec4 rgba(1.0f, 1.0f, 1.0f, 1.0f);
    switch (color.length()) {
    case 4: // #rgb
        rgba.r = std::strtol(color.substr(1, 1).c_str(), nullptr, 16) / 15.0f;
        rgba.g = std::strtol(color.substr(2, 1).c_str(), nullptr, 16) / 15.0f;
        rgba.b = std::strtol(color.substr(3, 1).c_str(), nullptr, 16) / 15.0f;
        break;
    case 5: // #rgba
        rgba.r = std::strtol(color.substr(1, 1).c_str(), nullptr, 16) / 15.0f;
        rgba.g = std::strtol(color.substr(2, 1).c_str(), nullptr, 16) / 15.0f;
        rgba.b = std::strtol(color.substr(3, 1).c_str(), nullptr, 16) / 15.0f;
        rgba.a = std::strtol(color.substr(4, 1).c_str(), nullptr, 16) / 15.0f;
        break;
    case 7: // #rrggbb
        rgba.r = std::strtol(color.substr(1, 2).c_str(), nullptr, 16) / 255.0f;
        rgba.g = std::strtol(color.substr(3, 2).c_str(), nullptr, 16) / 255.0f;
        rgba.b = std::strtol(color.substr(5, 2).c_str(), nullptr, 16) / 255.0f;
        break;
    case 9: // #rrggbbaa
        rgba.r = std::strtol(color.substr(1, 2).c_str(), nullptr, 16) / 255.0f;
        rgba.g = std::strtol(color.substr(3, 2).c_str(), nullptr, 16) / 255.0f;
        rgba.b = std::strtol(color.substr(5, 2).c_str(), nullptr, 16) / 255.0f;
        rgba.a = std::strtol(color.substr(7, 2).c_str(), nullptr, 16) / 255.0f;
        break;
    }
    return rgba;
}

FillStyle::FillStyle(const char* cStr) {
    type = Type::Color;
    color = parseHexColor(cStr);
}

FillStyle::FillStyle(const std::string& str) {
    type = Type::Color;
    color = parseHexColor(str);
}
