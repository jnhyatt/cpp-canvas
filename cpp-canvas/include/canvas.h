#pragma once

#include "app.h"
#include "export.h"

#include <glm/glm.hpp>

using namespace glm;

class Canvas
{
public:
  Canvas();

  void reset();
  void save();
  void restore();
  void rotate(float angle);
  void translate(float x, float y);

  void drawRect(int x, int y, int w, int h);

  vec2 canvasToNdc(ivec2 canvas) const;
  ivec2 ndcToCanvas(vec2 ndc) const;

  void onResize(ivec2 dimensions);

private:
  void vertex(vec2 v);

  ivec2 m_dimensions;
  size_t m_stackSize;
};

class DrawListener
{
public:
  virtual void onDraw(Canvas& canvas) = 0;
};

class CanvasApp: public EventListener
{
public:
  CanvasApp();

  void setDrawListener(DrawListener& l);
  void removeDrawListener();
  virtual void onDraw() override;
  int run();

private:
  Canvas m_canvas;
  DrawListener* m_drawListener;
  Window m_window;
};
