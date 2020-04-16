#pragma once

#include "export.h"

#include <glm/glm.hpp>
#include <string>

using namespace glm;

class CPP_CANVAS_API Color {
public:
    Color();
    Color(vec3 rgb);
    Color(vec4 rgba);
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);
    Color(const std::string& str);

    vec4 asVec4() const;

    static Color fromString(const std::string& str);
    static Color named(std::string name);
    static Color parseHex(const std::string& hex);

private:
    vec4 m_color;
};
