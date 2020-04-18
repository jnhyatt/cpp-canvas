#include "app.h"
#include "canvas.h"

#include <iostream>

App app;
Context2D& ctx = app.canvas().getContext2D();

float angle = 0.0f;

void draw() {
    ctx.clearRect(0, 0, 400, 400);

    ctx.beginPath();
    ctx.moveTo(200, 200);
    ctx.lineTo(200 + 100 * cos(angle), 200 + 100 * sin(angle));
    ctx.lineTo(200, 200 + 200 * sin(angle));
    ctx.stroke();

    ctx.save();
    ctx.translate(200 + 100 * cos(angle), 200 + 100 * sin(angle));
    ctx.fillRect(-2, -2, 4, 4);
    ctx.restore();

    angle += 0.01f;

    app.requestAnimationFrame(draw);
}

int main(int argc, char** argv) {
    app.setCanvasSize(400, 400);
    app.setBackgroundColor("#333");

    ctx.fillStyle = "#0f0";
    ctx.strokeStyle = "red";
    ctx.lineWidth = 8;

    app.requestAnimationFrame(draw);

    return 0;
}
