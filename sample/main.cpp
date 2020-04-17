#include "app.h"
#include "canvas.h"

#include <iostream>

std::ostream& operator<<(std::ostream& lhs, const Color& rhs) {
    vec4 rgba = rhs.asVec4();
    return lhs << "<" << rgba.r << ", " << rgba.g << ", " << rgba.b << ", "
               << rgba.a << ">";
}

App app;
Context2D& ctx = app.canvas().getContext2D();

float angle = 0.0f;

void draw() {
    ctx.clearRect(0, 0, 1280, 720);
    ctx.save();
    ctx.translate(640, 360);
    ctx.rotate(angle);
    ctx.fillRect(-180, -180, 360, 360);
    ctx.restore();
    angle += 0.05f;

    ctx.beginPath();
    ctx.moveTo(50, 50);
    ctx.lineTo(150, 150);
    ctx.lineTo(250, 50);
    ctx.stroke();

    app.requestAnimationFrame(draw);
}

int main(int argc, char** argv) {
    app.setCanvasSize(400, 400);
    app.setBackgroundColor("#333");

    ctx.fillStyle = "blue";
    ctx.strokeStyle = "red";
    ctx.lineWidth = 40;

    app.requestAnimationFrame(draw);

    return 0;
}
