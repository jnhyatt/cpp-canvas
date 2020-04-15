#pragma once

#include "export.h"
#include "util.h"

#include <glm/glm.hpp>
#include <stack>
#include <string>

using namespace glm;

class Canvas;

class CPP_CANVAS_API Context2D
{
public:
  Context2D(Canvas& canvas);

  void save();
  void restore();
  void rotate(float angle);
  void translate(int x, int y);

  void fillRect(int x, int y, int w, int h);
  void clearRect(int x, int y, int w, int h);

private:
  void setFillStyle(const FillStyle& style);

public:
  Setter<FillStyle, Context2D, &setFillStyle> fillStyle;

private:
  template <typename T> T toDegrees(const T& t) { return t * static_cast<T>(3.141592653589793238) / static_cast<T>(180.0); }
  void vertex(vec2 v);
  void color(vec4 c);
  void translate(vec2 off);
  void applyStyle();

  mat4& transform();
  const mat4& transform() const;

private:
  FillStyle m_drawStyle;
  Canvas& m_canvas;
  std::stack<mat4> m_transformStack;
};

class CPP_CANVAS_API Canvas
{
public:
  Canvas();

  Context2D& getContext2D();
  const Context2D& getContext2D() const;

  vec2 scaleCanvasToNdc(ivec2 canvas) const;
  ivec2 scaleNdcToCanas(vec2 ndc) const;
  vec2 canvasToNdc(ivec2 canvas) const;
  ivec2 ndcToCanvas(vec2 ndc) const;

  void onResize(ivec2 dimensions);

  vec4 backgroundColor;

private:
  Context2D m_context;
  ivec2 m_dimensions;
};
