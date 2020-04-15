#pragma once

#include "export.h"

#include <glm/glm.hpp>
#include <string>

using namespace glm;

template <typename T, typename U, void (U::*setter)(const T&), T (U::*getter)()>
class Field {
public:
    Field(U& parent) : m_parent(parent) {}
    Field& operator=(const T& value) {
        setter(value);
        return *this;
    }
    operator T() const { return (m_parent.*getter)(); }

private:
    U& m_parent;
};

template <typename T, typename U, T (U::*getter)()> class Getter {
public:
    Getter(U& parent) : m_parent(parent) {}
    operator T() const { return (m_parent.*getter)(); }

private:
    U& m_parent;
};

class FillStyle;

template <typename T, typename U, void (U::*setter)(const T&)> class Setter {
public:
    Setter(U& parent) : m_parent(parent) {}
    template <typename V> Setter& operator=(const V& value) {
        (m_parent.*setter)(value);
        return *this;
    }

private:
    U& m_parent;
};

vec4 parseHexColor(const std::string& color);

class CPP_CANVAS_API FillStyle {
public:
    FillStyle(const char* cStr);
    FillStyle(const std::string& str);

    enum class Type {
        Color,
    };

    vec4 color;
    Type type;
};

class CPP_CANVAS_API AffineTransform {
public:
    AffineTransform();

    void translate(vec2 offset);
    void rotate(float offset);

    vec2 transform(vec2 in) const;

private:
    mat2 m_transform;
};
