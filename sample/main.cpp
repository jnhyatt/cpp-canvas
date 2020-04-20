#include "cpp-canvas/app.h"
#include "cpp-canvas/canvas.h"

#include <iostream>

using namespace canvas;

App app;
Canvas& c = app.canvas();
Context2D& ctx = c.getContext2D();

int x = 0;
int y = 0;

std::unordered_map<std::string, std::string> colors = {
    {"", "white"},   {"0", "red"},    {"1", "green"},
    {"2", "purple"}, {"3", "yellow"}, {"w", "aqua"}};

void draw() {
    ctx.clearRect(0, 0, 400, 400);

    ctx.save();
    ctx.fillRect(20, 20, 100, 100);
    ctx.fillRect(x - 20, y - 20, 40, 40);
    ctx.restore();

    app.requestAnimationFrame(draw);
}

int main(int argc, char** argv) {
    app.setCanvasSize(400, 400);
    app.setBackgroundColor("#333");

    ctx.fillStyle = "blue";
    c.addEventListener("keydown", [](const KeyboardEvent& ev) {
        // x = ev.offsetX;
        // y = ev.offsetY;
        // ctx.fillStyle = colors[ev.which];
        ctx.fillStyle = colors[ev.key];
    });
    c.addEventListener("keyup", [](const KeyboardEvent& ev) {
        // x = ev.offsetX;
        // y = ev.offsetY;
        // ctx.fillStyle = colors[ev.which];
        ctx.fillStyle = "blue";
    });

    app.requestAnimationFrame(draw);

    return 0;
}
