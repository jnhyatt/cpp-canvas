#include "canvas.h"

#include <Windows.h>
#include <gl/GL.h>

Canvas::Canvas() : m_stackSize(0) {}

void Canvas::reset()
{
  while (m_stackSize > 0)
  {
    restore();
  }
}

void Canvas::save()
{
  glPushMatrix();
  m_stackSize++;
}

void Canvas::restore()
{
  if (m_stackSize == 0)
  {
    // warning
    return;
  }
  glPopMatrix();
  m_stackSize--;
}

void Canvas::drawRect(int x, int y, int w, int h)
{
  vec2 bottomLeft = canvasToNdc(ivec2(x, y));
  vec2 dim = canvasToNdc(ivec2(w, h));
  vec2 upOffset(0, dim.y);
  vec2 rightOffset(dim.x, 0);

  glBegin(GL_TRIANGLE_STRIP);

  vertex(bottomLeft);
  vertex(bottomLeft + rightOffset);
  vertex(bottomLeft + upOffset);
  vertex(bottomLeft + dim);

  glEnd();
}

vec2 Canvas::canvasToNdc(ivec2 canvas) const
{
  return vec2((2.0f / static_cast<float>(m_dimensions.x)) * static_cast<float>(canvas.x) - 1.0f,
    -(2.0f / static_cast<float>(m_dimensions.y)) * static_cast<float>(canvas.y) + 1.0f);
}

ivec2 Canvas::ndcToCanvas(vec2 canvas) const
{
  return ivec2(0.5f * static_cast<float>(m_dimensions.x) * (canvas.x + 1),
    -0.5f * static_cast<float>(m_dimensions.y) * (canvas.y - 1));
}

void Canvas::onResize(ivec2 dimensions)
{
  m_dimensions = dimensions;
}

void Canvas::vertex(vec2 v)
{
  glVertex2f(v.x, v.y);
}

CanvasApp::CanvasApp() : m_drawListener(nullptr), m_window("Canvas") {
  m_window.show();
  glClearColor(0.4f, 0.0f, 0.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  m_window.addEventListener(*this);
  m_canvas.onResize(ivec2(640, 480));
}

void CanvasApp::setDrawListener(DrawListener& l) {
  m_drawListener = &l;
}

void CanvasApp::removeDrawListener()
{
  m_drawListener = nullptr;
}

void CanvasApp::onDraw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  m_canvas.reset();
  glLoadIdentity();
  if (m_drawListener) m_drawListener->onDraw(m_canvas);
}

int CanvasApp::run()
{
  m_window.startEventLoop();

  return 0;
}
