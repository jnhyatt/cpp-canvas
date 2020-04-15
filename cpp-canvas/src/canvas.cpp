#include "canvas.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Windows.h>
#include <gl/GL.h>

Context2D::Context2D(Canvas& canvas)
    : m_canvas(canvas), fillStyle(*this), m_drawStyle("#000") {
    m_transformStack.emplace(1.0f);
}

void Context2D::save() {
    m_transformStack.push(m_transformStack.top());
    glLoadMatrixf(glm::value_ptr(transform()));
}

void Context2D::restore() {
    m_transformStack.pop();
    glLoadMatrixf(glm::value_ptr(transform()));
}

void Context2D::rotate(float angle) {
    transform() = glm::rotate(transform(), angle, vec3(0.0f, 0.0f, 1.0f));
    glLoadMatrixf(glm::value_ptr(transform()));
}

void Context2D::translate(float x, float y) {
    transform() = glm::translate(transform(), vec3(x, y, 0.0f));
    glLoadMatrixf(glm::value_ptr(transform()));
}

void Context2D::fillRect(float x, float y, float w, float h) {
    applyStyle();
    glBegin(GL_TRIANGLE_STRIP);

    glVertex2f(x, y);
    glVertex2f(x, y + h);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);

    glEnd();
}

void Context2D::clearRect(float x, float y, float w, float h) {
    color(m_canvas.backgroundColor);
    glBegin(GL_TRIANGLE_STRIP);

    glVertex2f(x, y);
    glVertex2f(x, y + h);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);

    glEnd();
}

void Context2D::setFillStyle(const FillStyle& style) { m_drawStyle = style; }

void Context2D::vertex(vec2 v) { glVertex2f(v.x, v.y); }

void Context2D::color(vec4 c) { glColor4f(c.r, c.g, c.b, c.a); }

void Context2D::applyStyle() {
    switch (m_drawStyle.type) {
    case FillStyle::Type::Color:
        color(m_drawStyle.color);
        break;
    }
}

mat4& Context2D::transform() { return m_transformStack.top(); }

const mat4& Context2D::transform() const { return m_transformStack.top(); }

Canvas::Canvas() : m_context(*this), backgroundColor(0.0f, 0.0f, 0.0f, 1.0f) {}

void Canvas::initialize() {
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

Context2D& Canvas::getContext2D() { return m_context; }

const Context2D& Canvas::getContext2D() const { return m_context; }

vec2 Canvas::scaleCanvasToNdc(float x, float y) const {
    return vec2((2.0f / m_dimensions.x) * x, -(2.0f / m_dimensions.y) * y);
}

vec2 Canvas::scaleNdcToCanas(float x, float y) const {
    return ivec2((m_dimensions.x / 2.0f) * x, -(m_dimensions.y / 2.0f) * y);
}

vec2 Canvas::canvasToNdc(float x, float y) const {
    return scaleCanvasToNdc(x, y) + vec2(-1.0f, 1.0f);
}

vec2 Canvas::ndcToCanvas(float x, float y) const {
    return scaleNdcToCanas(x + 1.0f, y - 1.0f);
}

void Canvas::onResize(ivec2 dimensions) {
    m_dimensions = dimensions;
    glViewport(0, 0, dimensions.x, dimensions.y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, dimensions.x, dimensions.y, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
