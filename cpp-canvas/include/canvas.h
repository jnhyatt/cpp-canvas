#pragma once

#include "export.h"
#include "field.h"
#include "path.h"
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

    Gradient createLinearGradient(float x, float y, float dx, float dy);

private:
    void setFillStyle(const FillStyle& style);
    void setStrokeStyle(const StrokeStyle& style);

public:
    Setter<FillStyle, Context2D, &setFillStyle> fillStyle;
    Setter<StrokeStyle, Context2D, &setStrokeStyle> strokeStyle;
    float lineWidth;

private:
    void vertex(vec2 v);
    void setColor(Color c);
    void applyStyle();
    void targetStencil();
    void targetColor();

    // Draw shapes to stencil buffer
    void drawRect(vec2 a, vec2 b);
    void drawPath(const Path& path);

    // Draw styles to color buffer
    void drawFill(const FillStyle& style);
    void fillWithColor(const Color& color);
    void fillWithGradient(const Gradient& gradient);
    // void drawPattern(const Pattern& pattern);

    mat4& transform();
    const mat4& transform() const;

private:
    FillStyle m_fillStyle;
    StrokeStyle m_strokeStyle;
    Path m_path;
    Canvas& m_canvas;
    std::stack<mat4> m_transformStack;
};

class CPP_CANVAS_API Canvas {
public:
    Canvas();

    void initialize();

    Context2D& getContext2D();
    const Context2D& getContext2D() const;

    ivec2 getDimensions() const;

    void onResize(ivec2 dimensions);

    Color backgroundColor;

private:
    Context2D m_context;
    ivec2 m_dimensions;
};
