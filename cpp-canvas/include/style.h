#pragma once

#include "color.h"
#include "export.h"

#include <glm/glm.hpp>
#include <map>
#include <string>
#include <vector>

using namespace glm;

template <typename T>
T lerp(const T& left, const T& right, const float factor) {
    const T diff = right - left;
    return left + (factor * diff);
}

class CPP_CANVAS_API Gradient {
public:
    Gradient();
    Gradient(vec2 origin, vec2 direction);
    void addColorStop(float position, Color color);
    void addColorStop(float position, const std::string& color);
    Color evaluate(float position);
    Color evaluate(vec2 position);

private:
    vec2 m_origin;
    vec2 m_direction;
    std::map<float, Color> m_stops;
};

enum class LineCap {
    Butt,
    Round,
    Square,
};

class CPP_CANVAS_API FillStyle {
public:
    FillStyle();
    FillStyle(const char* cStr);
    FillStyle(const std::string& str);
    FillStyle(const Gradient& gradient);

    enum class Type {
        Color,
        Gradient,
        Pattern,
    };

    Type type;
    Color color;
    Gradient gradient;
    // Pattern pattern;
};

class CPP_CANVAS_API StrokeStyle {};
