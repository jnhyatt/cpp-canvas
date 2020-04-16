#include "app.h"
#include "canvas.h"

App app;
Context2D& ctx = app.canvas().getContext2D();

float angle = 0.0f;

void draw() {
    angle += 0.01f;
    ctx.clearRect(0, 0, 400, 400);
    ctx.save();
    ctx.translate(200, 200);
    ctx.rotate(angle);
    ctx.fillRect(0, 0, 100, 100);
    ctx.restore();

    app.requestAnimationFrame(draw);
}

int main(int argc, char** argv) {
    app.setCanvasSize(400, 400);
    app.setBackgroundColor("#333");

    ctx.fillStyle = "#f00";
    app.requestAnimationFrame(draw);

    return 0;
}
