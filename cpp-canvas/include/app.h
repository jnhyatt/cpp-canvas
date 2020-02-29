#pragma once

#include "export.h"

#include <Windows.h>

#include <glm/glm.hpp>
#include <string>
#include <vector>

class EventListener
{
public:
  virtual void onDraw() {}
  virtual void onResize(size_t width, size_t height) {}
  virtual void onKeyPress() {}
  virtual void onMouseMove(int x, int y) {}
  virtual void onMouseClick(int x, int y, int button) {}
};

class Window
{
public:
  Window(const std::string& title);
  ~Window();

  void addEventListener(EventListener& l);
  void setDimensions(const unsigned int width, const unsigned int height) const;
  void setPosition(const int x, const int y) const;
  void show() const;
  void startEventLoop();

  static LRESULT CALLBACK eventCallback(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

private:
  HDC m_hDeviceContext;
  HGLRC m_hRenderingContext;
  HINSTANCE m_hInstance;
  HWND m_hWindow;
  const std::string m_className;
  std::vector<EventListener*> m_eventListeners;
};
