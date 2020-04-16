#include "app.h"
#include "canvas.h"

#include <iostream>

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

std::ostream& operator<<(std::ostream& lhs, const Color& rhs) {
    vec4 rgba = rhs.asVec4();
    return lhs << "<" << rgba.r << ", " << rgba.g << ", " << rgba.b << ", "
               << rgba.a << ">";
}

int main(int argc, char** argv) {
    // app.setCanvasSize(400, 400);
    // app.setBackgroundColor("#333");

    // ctx.fillStyle = "red";
    // app.requestAnimationFrame(draw);

    Gradient gradient(vec2(0, 0), vec2(100, 0));
    gradient.addColorStop(0.0f, Color("red"));
    gradient.addColorStop(1.0f, Color("green"));

    for (float i = -0.2; i < 1.3f; i += 0.1f) {
        std::cout << i << ": " << gradient.evaluate(i) << std::endl;
    }

    return 0;
}
