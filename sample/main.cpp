#include "app.h"
#include "canvas.h"

#include <iostream>

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

    app.requestAnimationFrame(draw);
}

std::ostream& operator<<(std::ostream& lhs, const Color& rhs) {
    vec4 rgba = rhs.asVec4();
    return lhs << "<" << rgba.r << ", " << rgba.g << ", " << rgba.b << ", "
               << rgba.a << ">";
}

int main(int argc, char** argv) {
    app.setCanvasSize(1280, 720);
    app.setBackgroundColor("#333");

    auto grd = ctx.createLinearGradient(0, 0, 400, 0);
    grd.addColorStop(0, "red");
    grd.addColorStop(1, "green");
    ctx.fillStyle = "blue";

    app.requestAnimationFrame(draw);

    return 0;
}
