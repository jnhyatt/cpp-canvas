#include "app.h"

#include <glm/glm.hpp>

Window::Window(const std::string& title) : m_hDeviceContext(NULL), m_hRenderingContext(NULL), m_hInstance(GetModuleHandle(NULL)), m_hWindow(NULL), m_className("joshroxx")
{
  WNDCLASS wc;

  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = Window::eventCallback;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = m_hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = m_className.c_str();

  RegisterClass(&wc);

  m_hWindow = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
    m_className.c_str(),
    title.c_str(),
    WS_CLIPSIBLINGS |
    WS_CLIPCHILDREN |
    WS_OVERLAPPEDWINDOW,
    0, 0,
    640,
    480,
    NULL,
    NULL,
    m_hInstance,
    NULL);

  m_hDeviceContext = GetDC(m_hWindow);

  PIXELFORMATDESCRIPTOR pfd =
  {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
    PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
    32,                   // Colordepth of the framebuffer.
    0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    0, 0, 0, 0,
    24,                   // Number of bits for the depthbuffer
    8,                    // Number of bits for the stencilbuffer
    0,                    // Number of Aux buffers in the framebuffer.
    PFD_MAIN_PLANE,
    0,
    0, 0, 0
  };

  int pixelFormat = ChoosePixelFormat(m_hDeviceContext, &pfd);

  SetPixelFormat(m_hDeviceContext, pixelFormat, &pfd);

  m_hRenderingContext = wglCreateContext(m_hDeviceContext);
  wglMakeCurrent(m_hDeviceContext, m_hRenderingContext);
}

Window::~Window()
{
  // TODO: release rc, dc, window in that order
}

void Window::show() const
{
  ShowWindow(m_hWindow, SW_SHOWDEFAULT);
}

LRESULT CALLBACK Window::eventCallback(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_CLOSE:
    PostQuitMessage(0);
    return 0;
  }

  return DefWindowProc(hWindow, message, wParam, lParam);
}

void Window::addEventListener(EventListener& l)
{
  m_eventListeners.push_back(&l);
}

void Window::startEventLoop()
{
  bool done = false;
  while (!done)
  {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
      {
        done = true;
      }
      else
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }

    for (EventListener* l : m_eventListeners)
    {
      l->onDraw();
    }

    SwapBuffers(m_hDeviceContext);
  }
}
