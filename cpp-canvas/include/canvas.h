#pragma once

#include "export.h"
#include "field.h"
#include "style.h"

#include <glm/glm.hpp>
#include <stack>
#include <string>

using namespace glm;

class Canvas;

class CPP_CANVAS_API Context2D {
public:
    Context2D(Canvas& canvas);

    void save();
    void restore();
    void rotate(float angle);
    void translate(float x, float y);

    void fillRect(float x, float y, float w, float h);
    void clearRect(float x, float y, float w, float h);

private:
    void setFillStyle(const DrawStyle& style);
    void setStrokeStyle(const DrawStyle& style);

public:
    Setter<DrawStyle, Context2D, &setFillStyle> fillStyle;
    Setter<DrawStyle, Context2D, &setStrokeStyle> strokeStyle;

private:
    template <typename T> T toDegrees(const T& t) {
        return t * static_cast<T>(3.141592653589793238) / static_cast<T>(180.0);
    }
    void vertex(vec2 v);
    void color(vec4 c);
    void applyStyle();

    mat4& transform();
    const mat4& transform() const;

private:
    DrawStyle m_drawStyle;
    DrawStyle m_strokeStyle;
    Canvas& m_canvas;
    std::stack<mat4> m_transformStack;
};

class CPP_CANVAS_API Canvas {
public:
    Canvas();

    void initialize();

    Context2D& getContext2D();
    const Context2D& getContext2D() const;

    vec2 scaleCanvasToNdc(float x, float y) const;
    vec2 scaleNdcToCanas(float x, float y) const;
    vec2 canvasToNdc(float x, float y) const;
    vec2 ndcToCanvas(float x, float y) const;

    void onResize(ivec2 dimensions);

    vec4 backgroundColor;

private:
    Context2D m_context;
    ivec2 m_dimensions;
};
