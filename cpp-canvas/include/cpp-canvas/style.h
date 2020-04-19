#pragma once

#include "cpp-canvas/color.h"
#include "cpp-canvas/export.h"

#include <glm/glm.hpp>
#include <map>
#include <string>
#include <vector>

using namespace glm;

namespace canvas {
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

    class CPP_CANVAS_API DrawStyle {
    public:
        DrawStyle();
        DrawStyle(const char* cStr);
        DrawStyle(const std::string& str);
        DrawStyle(const Gradient& gradient);

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
} // namespace canvas
