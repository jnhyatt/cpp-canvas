#pragma comment(lib, "opengl32.lib")

#include <Windows.h>
#include <gl/GL.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <chrono>
#include <sstream>
#include <thread>

class vec2
{
public:
  float x;
  float y;
};

class Canvas
{
public:
  void drawLine(float ax, float ay, float bx, float by)
  {

  }

  void drawLine(vec2 a, vec2 b)
  {

  }

  void beginPath();

  void endPath();
};

class Logger
{
public:
  ~Logger()
  {
    m_buffer << std::endl;
    OutputDebugString(m_buffer.str().c_str());
  }

  template <typename T> Logger& operator<<(T&& t)
  {
    m_buffer << std::forward<T>(t);
    return *this;
  }

private:
  std::ostringstream m_buffer;
};

LRESULT CALLBACK WndProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_CLOSE:
    PostQuitMessage(0);
    return 0;
  }

  return DefWindowProc(hWindow, message, wParam, lParam);
}

class WindowsError
{
public:
  WindowsError(DWORD code): code(code) {}
  static WindowsError last() { return WindowsError(GetLastError()); }

  const DWORD code;
};

std::ostream& operator<<(std::ostream& lhs, const WindowsError& rhs)
{
  LPSTR messageBuffer = nullptr;
  size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL, rhs.code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
  lhs << messageBuffer;
  LocalFree(messageBuffer);
  return lhs;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR commandLine, int showStyle)
{
  namespace ch = std::chrono;
  HWND hWindow;// = GetConsoleWindow();

  WNDCLASS wc;

  wc.style        = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;       // Redraw On Move, And Own DC For Window
  wc.lpfnWndProc      = (WNDPROC) WndProc;                // WndProc Handles Messages
  wc.cbClsExtra       = 0;                        // No Extra Window Data
  wc.cbWndExtra       = 0;                        // No Extra Window Data
  wc.hInstance        = hInstance;                    // Set The Instance
  wc.hIcon        = LoadIcon(NULL, IDI_WINLOGO);          // Load The Default Icon
  wc.hCursor      = LoadCursor(NULL, IDC_ARROW);          // Load The Arrow Pointer
  wc.hbrBackground    = NULL;                     // No Background Required For GL
  wc.lpszMenuName     = NULL;                     // We Don't Want A Menu
  wc.lpszClassName    = "joshroxx";

  ATOM success = RegisterClass(&wc);

  if (!success)
  {
    Logger() << WindowsError::last();
    return 1;
  }

  hWindow = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
    "joshroxx",               // Class Name
    "James' canvas",                  // Window Title
    WS_CLIPSIBLINGS |           // Required Window Style
    WS_CLIPCHILDREN |           // Required Window Style
    WS_OVERLAPPEDWINDOW,                // Selected Window Style
    0, 0,                   // Window Position
    1920,   // Calculate Adjusted Window Width
    1080,   // Calculate Adjusted Window Height
    NULL,                   // No Parent Window
    NULL,                   // No Menu
    hInstance,              // Instance
    NULL);

  Logger() << "Handle is " << hWindow;

  HDC hDeviceContext = GetDC(hWindow);
  Logger() << "Device context is " << hWindow;

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

  int pixelFormat = ChoosePixelFormat(hDeviceContext, &pfd);

  SetPixelFormat(hDeviceContext, pixelFormat, &pfd);

  HGLRC hRenderingContext = wglCreateContext(hDeviceContext);
  wglMakeCurrent(hDeviceContext, hRenderingContext);

  ShowWindow(hWindow, SW_SHOWDEFAULT);

  RECT windowDimensions;
  GetWindowRect(hWindow, &windowDimensions);
  long width = windowDimensions.right - windowDimensions.left;
  long height = windowDimensions.bottom - windowDimensions.top;

  Logger() << "Window is " << width << "x" << height << " pixels";

  glClearColor(0.4f, 0.0f, 0.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_TEXTURE_2D);

  GLuint texId;
  glGenTextures(1, &texId);
  glBindTexture(GL_TEXTURE_2D, texId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int imageWidth, imageHeight, channels;
  stbi_set_flip_vertically_on_load(TRUE);
  for (size_t i = 0; i < 12; i++) {
    unsigned char* data = stbi_load((std::stringstream() << "space_mip" << i << ".jpg").str().c_str(), &imageWidth, &imageHeight, &channels, STBI_rgb_alpha);
    glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
  }

  bool done = false;
  float angle = 0.0f;
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
    glClear(GL_COLOR_BUFFER_BIT);

    angle += 0.01f;

    glLoadIdentity();
    glTranslatef(0.4f * cosf(angle), 0.4f * sinf(angle), 0.0f);
    glRotatef(angle * -10.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLE_STRIP);

    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-0.4f, -0.4f);

    glColor3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(0.4f, -0.4f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-0.4f, 0.4f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(0.4f, 0.4f);

    glEnd();

    SwapBuffers(hDeviceContext);
  }

  return 0;
}
