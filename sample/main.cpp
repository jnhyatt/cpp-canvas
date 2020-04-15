#include "app.h"
#include "canvas.h"

App app;

float angle = 0.0f;

void draw()
{
  auto ctx = app.canvas().getContext2D();
  angle += 0.01f;
  ctx.clearRect(0, 0, 400, 400);
  ctx.save();
  ctx.translate(200, 200);
  ctx.rotate(angle);
  ctx.fillStyle = "#f33";
  ctx.fillRect(0, 0, 100, 100);
  ctx.restore();

  app.requestAnimationFrame(draw);
}

int main(int argc, char** argv)
{
  app.setCanvasSize(400, 400);
  app.setBackgroundColor("#333");
  app.requestAnimationFrame(draw);

  return 0;
}
