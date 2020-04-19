#include "cpp-canvas/style.h"

#include "cpp-canvas/geometry.h"

#include <algorithm>
#include <unordered_map>

namespace canvas {
    DrawStyle::DrawStyle() : type(Type::Color) {}

    DrawStyle::DrawStyle(const char* cStr) : color(cStr), type(Type::Color) {}

    DrawStyle::DrawStyle(const std::string& str)
        : color(str), type(Type::Color) {}

    DrawStyle::DrawStyle(const Gradient& gradient)
        : gradient(gradient), type(Type::Gradient) {}

    Gradient::Gradient() {}

    Gradient::Gradient(vec2 origin, vec2 direction)
        : m_origin(origin), m_direction(direction) {}

    void Gradient::addColorStop(float position, Color color) {
        m_stops.emplace(position, color);
    }

    void Gradient::addColorStop(float position, const std::string& color) {
        m_stops.emplace(position, color);
    }

    Color Gradient::evaluate(float stopPosition) {
        auto left = m_stops.upper_bound(stopPosition);
        if (left == m_stops.begin()) {
            return left->second;
        }
        auto right = left--;
        if (right == m_stops.end()) {
            return left->second;
        }
        float width = right->first - left->first;
        float factor = (stopPosition - left->first) / width;
        if (factor > 1.0f) {
            return right->second;
        }
        return Color(
            lerp(left->second.asVec4(), right->second.asVec4(), factor));
    }

    Color Gradient::evaluate(vec2 position) {
        vec2 intermediate = position - m_origin;
        return evaluate(dot(intermediate, normalize(m_direction)) /
                        m_direction.length());
    }
} // namespace canvas
