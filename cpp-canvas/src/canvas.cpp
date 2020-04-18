#include "canvas.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Windows.h>
#include <gl/GL.h>

Context2D::Context2D(Canvas& canvas)
    : m_canvas(canvas), fillStyle(*this), strokeStyle(*this),
      m_penValid(false) {
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
    targetStencil();
    drawRect(vec2(x, y), vec2(x + w, y + h));
    targetColor();
    drawFill(m_fillStyle);
}

void Context2D::clearRect(float x, float y, float w, float h) {
    glDisable(GL_STENCIL_TEST);
    setColor(m_canvas.backgroundColor);
    drawRect(vec2(x, y), vec2(x + w, y + h));
}

void Context2D::beginPath() {
    m_penValid = false;
    m_path.reset();
}

void Context2D::moveTo(float x, float y) {
    m_pen = vec2(x, y);
    if (!m_penValid) {
        m_pathOrigin = m_pen;
    }
    m_penValid = true;
}

void Context2D::lineTo(float x, float y) {
    if (!m_penValid) {
        m_path.addSegment<PathLine>(vec2(m_pen.x, m_pen.y), vec2(x, y));
    }
    moveTo(x, y);
}

void Context2D::stroke() {
    targetStencil();
    drawPath(m_path);
    targetColor();
    drawFill(m_strokeStyle);
}

void Context2D::fill() {
    targetStencil();
    // TODO Avoid hardcoding resolution
    std::vector<Triangle> triangles = triangulate(m_path.toMesh(10.0f));
    for (const Triangle& triangle: triangles) {
        drawTriangle(triangle);
    }
    targetColor();
    drawFill(m_fillStyle);
}

Gradient Context2D::createLinearGradient(float x, float y, float dx, float dy) {
    return Gradient(vec2(x, y), vec2(dx, dy));
}

void Context2D::setFillStyle(const DrawStyle& style) { m_fillStyle = style; }

void Context2D::setStrokeStyle(const DrawStyle& style) {
    m_strokeStyle = style;
}

void Context2D::vertex(vec2 v) { glVertex2f(v.x, v.y); }

void Context2D::setColor(Color c) {
    vec4 rgba = c.asVec4();
    glColor4f(rgba.r, rgba.g, rgba.b, rgba.a);
}

void Context2D::targetStencil() {
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}

void Context2D::targetColor() {
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
}

void Context2D::drawRect(vec2 a, vec2 b) {
    glBegin(GL_TRIANGLE_STRIP);

    glVertex2f(a.x, a.y);
    glVertex2f(a.x, b.y);
    glVertex2f(b.x, a.y);
    glVertex2f(b.x, b.y);

    glEnd();
}

void Context2D::drawTriangle(const Triangle& triangle) {
    glBegin(GL_TRIANGLES);

    vertex(triangle.a);
    vertex(triangle.b);
    vertex(triangle.c);

    glEnd();
}

void Context2D::drawPath(const Path& path) {
    // TODO Deal with line caps
    // TODO Avoid hardcoding resolution
    Mesh mesh = path.toMesh(10.0f);
}

void Context2D::drawFill(const DrawStyle& style) {
    switch (style.type) {
    case DrawStyle::Type::Color:
        fillWithColor(style.color);
        break;
    case DrawStyle::Type::Gradient:
        fillWithGradient(style.gradient);
        break;
    case DrawStyle::Type::Pattern:
        // fillWithPattern(m_drawStyle.pattern);
        break;
    }
}

void Context2D::fillWithColor(const Color& color) {
    vec2 dim = m_canvas.getDimensions();
    setColor(color);
    glPushMatrix();
    glLoadIdentity();
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(0, 0);
    glVertex2f(0, dim.y);
    glVertex2f(dim.x, 0);
    glVertex2f(dim.x, dim.y);
    glEnd();
    glPopMatrix();
}

void Context2D::fillWithGradient(const Gradient& gradient) {}

mat4& Context2D::transform() { return m_transformStack.top(); }

const mat4& Context2D::transform() const { return m_transformStack.top(); }

Canvas::Canvas() : m_context(*this), backgroundColor(0.0f, 0.0f, 0.0f, 1.0f) {}

void Canvas::initialize() {
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_STENCIL_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

Context2D& Canvas::getContext2D() { return m_context; }

const Context2D& Canvas::getContext2D() const { return m_context; }

ivec2 Canvas::getDimensions() const { return m_dimensions; }

// vec2 Canvas::scaleCanvasToNdc(float x, float y) const {
//    return vec2((2.0f / m_dimensions.x) * x, -(2.0f / m_dimensions.y) * y);
//}
//
// vec2 Canvas::scaleNdcToCanas(float x, float y) const {
//    return ivec2((m_dimensions.x / 2.0f) * x, -(m_dimensions.y / 2.0f) * y);
//}
//
// vec2 Canvas::canvasToNdc(float x, float y) const {
//    return scaleCanvasToNdc(x, y) + vec2(-1.0f, 1.0f);
//}
//
// vec2 Canvas::ndcToCanvas(float x, float y) const {
//    return scaleNdcToCanas(x + 1.0f, y - 1.0f);
//}

void Canvas::onResize(ivec2 dimensions) {
    m_dimensions = dimensions;
    glViewport(0, 0, dimensions.x, dimensions.y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, dimensions.x, dimensions.y, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
