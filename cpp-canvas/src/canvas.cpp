#include "canvas.h"

#include <glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include <gl/GL.h>

Context2D::Context2D(Canvas& canvas) : m_canvas(canvas), fillStyle(*this), m_drawStyle("#fff") {
  m_transformStack.emplace(1.0f);
}

void Context2D::save()
{
  m_transformStack.push(m_transformStack.top());
}

void Context2D::restore()
{
  m_transformStack.pop();
}

void Context2D::rotate(float angle)
{
  glRotatef(toDegrees(angle), 0.0f, 0.0f, 1.0f);
}

void Context2D::translate(int x, int y)
{
  glm::translate(transform(), vec3(x, y, 0.0f));
  //translate(m_canvas.scaleCanvasToNdc(ivec2(x, y)));
}

void Context2D::fillRect(int x, int y, int w, int h)
{
  applyStyle();
  glBegin(GL_TRIANGLE_STRIP);

  vertex(m_canvas.scaleCanvasToNdc(ivec2(x, y)));
  vertex(m_canvas.scaleCanvasToNdc(ivec2(x, y + h)));
  vertex(m_canvas.scaleCanvasToNdc(ivec2(x + w, y)));
  vertex(m_canvas.scaleCanvasToNdc(ivec2(x + w, y + h)));

  glEnd();
}

void Context2D::clearRect(int x, int y, int w, int h)
{
  color(m_canvas.backgroundColor);
  glBegin(GL_TRIANGLE_STRIP);

  vertex(m_canvas.canvasToNdc(ivec2(x, y)));
  vertex(m_canvas.canvasToNdc(ivec2(x, y + h)));
  vertex(m_canvas.canvasToNdc(ivec2(x + w, y)));
  vertex(m_canvas.canvasToNdc(ivec2(x + w, y + h)));

  glEnd();
}

void Context2D::setFillStyle(const FillStyle& style)
{
  switch (style.type)
  {
  case FillStyle::Type::Color:
    color(style.color);
    break;
  }
}

void Context2D::vertex(vec2 v)
{
  glVertex2f(v.x, v.y);
}

void Context2D::color(vec4 c)
{
  glColor4f(c.r, c.g, c.b, c.a);
}

void Context2D::translate(vec2 off)
{
  glTranslatef(off.x, off.y, 0.0f);
}

void Context2D::applyStyle()
{
  switch (m_drawStyle.type)
  {
  case FillStyle::Type::Color:
    color(m_drawStyle.color);
    break;
  }
}

mat2& Context2D::transform()
{
  return m_transformStack.top();
}

const mat2& Context2D::transform() const
{
  return m_transformStack.top();
}

Canvas::Canvas() : m_context(*this) {}

Context2D& Canvas::getContext2D()
{
  return m_context;
}

const Context2D& Canvas::getContext2D() const
{
  return m_context;
}

vec2 Canvas::scaleCanvasToNdc(ivec2 canvas) const
{
  return vec2((2.0f / m_dimensions.x) * canvas.x, -(2.0f / m_dimensions.y) * canvas.y);
}

ivec2 Canvas::scaleNdcToCanas(vec2 ndc) const
{
  return ivec2((m_dimensions.x / 2.0f) * ndc.x, -(m_dimensions.y / 2.0f) * ndc.y);
}

vec2 Canvas::canvasToNdc(ivec2 canvas) const
{
  return scaleCanvasToNdc(canvas) + vec2(-1.0f, 1.0f);
  //return vec2((2.0f / static_cast<float>(m_dimensions.x)) * static_cast<float>(canvas.x) - 1.0f,
  //  -(2.0f / static_cast<float>(m_dimensions.y)) * static_cast<float>(canvas.y) + 1.0f);
}

ivec2 Canvas::ndcToCanvas(vec2 ndc) const
{
  return scaleNdcToCanas(ndc + vec2(1.0f, -1.0f));
  //return ivec2(0.5f * static_cast<float>(m_dimensions.x) * (ndc.x + 1),
  //  -0.5f * static_cast<float>(m_dimensions.y) * (ndc.y - 1));
}

void Canvas::onResize(ivec2 dimensions)
{
  m_dimensions = dimensions;
  glViewport(0, 0, dimensions.x, dimensions.y);
}
