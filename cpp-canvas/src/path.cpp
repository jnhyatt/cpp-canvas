#include "path.h"

PathLine::PathLine(const vec2 start, const vec2 end)
    : m_start(start), m_end(end) {}

vec2 PathLine::f(const float x) const { return m_start + (x * m_end); }

vec2 PathLine::slope(const float x) const { return normalize(m_end - m_start); }

float PathLine::length() const {
    return static_cast<float>((m_end - m_start).length());
}
