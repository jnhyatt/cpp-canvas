#pragma once

#include "cpp-canvas/export.h"
#include "cpp-canvas/field.h"
#include "cpp-canvas/geometry.h"
#include "cpp-canvas/style.h"

#include <stack>

namespace canvas {
    class Canvas;

    class CPP_CANVAS_API Context2D {
    public:
        Context2D(Canvas& canvas);

        void save();
        void restore();
        void rotate(const float angle);
        void translate(const float x, const float y);

        void fillText(const std::string& text, const float x, const float y);
        void fillRect(const float x, const float y, const float w,
                      const float h);
        void clearRect(const float x, const float y, const float w,
                       const float h);

        void beginPath();
        void moveTo(const float x, const float y);
        void lineTo(const float x, const float y);
        void closePath();

        void stroke();
        void fill();

        Gradient createLinearGradient(float x, float y, float dx, float dy);

    private:
        void setFillStyle(const DrawStyle& style);
        void setStrokeStyle(const DrawStyle& style);

    public:
        Setter<DrawStyle, Context2D, &setFillStyle> fillStyle;
        Setter<DrawStyle, Context2D, &setStrokeStyle> strokeStyle;
        float lineWidth;
        float fontSize;

    private:
        void vertex(vec2 v);
        void setColor(Color c);
        void targetStencil();
        void targetColor();

        // Draw shapes to stencil buffer
        void drawRect(vec2 a, vec2 b);
        void drawTriangle(const Triangle& triangle);
        void drawPath(const Path& path);
        void drawText(const std::string& text);

        // Draw styles to color buffer
        void drawFill(const DrawStyle& style);
        void fillWithColor(const Color& color);
        void fillWithGradient(const Gradient& gradient);
        // void drawPattern(const Pattern& pattern);

        mat4& transform();
        const mat4& transform() const;

    private:
        DrawStyle m_fillStyle;
        DrawStyle m_strokeStyle;
        Path m_path;
        vec2 m_pathOrigin;
        bool m_penValid;
        vec2 m_pen;
        Canvas& m_canvas;
        std::stack<mat4> m_transformStack;
        uint8_t m_vertexBuffer[131072];
    };
} // namespace canvas
