#include "style.h"

#include <algorithm>
#include <unordered_map>

FillStyle::FillStyle() : type(Type::Color) {}

FillStyle::FillStyle(const char* cStr) : color(cStr), type(Type::Color) {}

FillStyle::FillStyle(const std::string& str) : color(str), type(Type::Color) {}

Gradient::Gradient() {}

Gradient::Gradient(vec2 origin, vec2 direction)
    : m_origin(origin), m_direction(direction) {}

void Gradient::addColorStop(float position, Color color) {
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
    return Color(lerp(left->second.asVec4(), right->second.asVec4(), factor));
}

Color Gradient::evaluate(vec2 position) {
    vec2 intermediate = position - m_origin;
    return Color();
}
