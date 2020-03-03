#include "canvas.h"

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
    canvas.fillRect(320, 240, 100, 100);
  }

private:
  float offset;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR commandLine, int showStyle)
{
  JoshApp app;

  return 0;
}
