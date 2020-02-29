#include "canvas.h"

//#include <glm/glm.hpp>
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

//class Logger
//{
//public:
//  ~Logger()
//  {
//    m_buffer << std::endl;
//    OutputDebugString(m_buffer.str().c_str());
//  }
//
//  template <typename T> Logger& operator<<(T&& t)
//  {
//    m_buffer << std::forward<T>(t);
//    return *this;
//  }
//
//private:
//  std::ostringstream m_buffer;
//};
//
//class WindowsError
//{
//public:
//  WindowsError(DWORD code): code(code) {}
//  static WindowsError last() { return WindowsError(GetLastError()); }
//
//  const DWORD code;
//};
//
//std::ostream& operator<<(std::ostream& lhs, const WindowsError& rhs)
//{
//  LPSTR messageBuffer = nullptr;
//  size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//    NULL, rhs.code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
//  lhs << messageBuffer;
//  LocalFree(messageBuffer);
//  return lhs;
//}

class JoshApp: public DrawListener
{
public:
  JoshApp()
  {
    CanvasApp app;
    app.setDrawListener(*this);
    app.run();
  }

  virtual void onDraw(Canvas& canvas) override
  {
    canvas.save();
//    canvas.rotate(angle);
    canvas.drawRect(320, 240, 100, 100);
    canvas.restore();
  }

private:
  float angle;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR commandLine, int showStyle)
{
  //glEnable(GL_TEXTURE_2D);

  //GLuint texId;
  //glGenTextures(1, &texId);
  //glBindTexture(GL_TEXTURE_2D, texId);

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //int imageWidth, imageHeight, channels;
  //stbi_set_flip_vertically_on_load(TRUE);
  //for (size_t i = 0; i < 12; i++) {
  //  unsigned char* data = stbi_load((std::stringstream() << "space_mip" << i << ".jpg").str().c_str(), &imageWidth, &imageHeight, &channels, STBI_rgb_alpha);
  //  glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  //  stbi_image_free(data);
  //}

  JoshApp app;

  return 0;
}
