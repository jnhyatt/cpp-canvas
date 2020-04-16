#pragma once

#include "export.h"

#include <glm/glm.hpp>
#include <string>

using namespace glm;

vec4 parseHexColor(const std::string& color);

class CPP_CANVAS_API DrawStyle {
public:
    DrawStyle(const char* cStr);
    DrawStyle(const std::string& str);

    enum class Type {
        Color,
        Gradient,
        Pattern,
    };

    vec4 color;
    Type type;
};
