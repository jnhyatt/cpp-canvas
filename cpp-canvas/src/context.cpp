#include "cpp-canvas/context.h"

#include "cpp-canvas/canvas.h"

#include <Windows.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace canvas {
    Context2D::Context2D(Canvas& canvas)
        : m_canvas(canvas), fillStyle(*this), strokeStyle(*this),
          m_penValid(false) {
        m_transformStack.emplace(1.0f);
    }

    void Context2D::save() {
        m_transformStack.push(m_transformStack.top());
        glLoadMatrixf(glm::value_ptr(transform())); // TODO Remove
    }

    void Context2D::restore() {
        m_transformStack.pop();
        glLoadMatrixf(glm::value_ptr(transform()));
    }

    void Context2D::rotate(float angle) {
        transform() = glm::rotate(transform(), angle, vec3(0.0f, 0.0f, 1.0f));
        glLoadMatrixf(glm::value_ptr(transform()));
    }

    void Context2D::translate(float x, float y) {
        transform() = glm::translate(transform(), vec3(x, y, 0.0f));
        glLoadMatrixf(glm::value_ptr(transform()));
    }

    void Context2D::fillRect(float x, float y, float w, float h) {
        targetStencil();
        drawRect(vec2(x, y), vec2(x + w, y + h));
        targetColor();
        drawFill(m_fillStyle);
    }

    void Context2D::clearRect(float x, float y, float w, float h) {
        glDisable(GL_STENCIL_TEST);
        setColor(m_canvas.backgroundColor);
        drawRect(vec2(x, y), vec2(x + w, y + h));
        glEnable(GL_STENCIL_TEST);
    }

    void Context2D::beginPath() {
        m_penValid = false;
        m_path.reset();
    }

    void Context2D::moveTo(float x, float y) {
        m_pen = vec2(x, y);
        if (!m_penValid) {
            m_pathOrigin = m_pen;
        }
        m_penValid = true;
    }

    void Context2D::lineTo(float x, float y) {
        if (m_penValid) {
            m_path.addSegment<PathLine>(vec2(m_pen.x, m_pen.y), vec2(x, y));
        }
        moveTo(x, y);
    }

    void Context2D::stroke() {
        targetStencil();
        drawPath(m_path);
        targetColor();
        drawFill(m_strokeStyle);
    }

    void Context2D::fill() {
        targetStencil();
        // TODO Avoid hardcoding resolution
        std::vector<Triangle> triangles = triangulate(m_path.toMesh(10.0f));
        for (const Triangle& triangle: triangles) {
            drawTriangle(triangle);
        }
        targetColor();
        drawFill(m_fillStyle);
    }

    Gradient Context2D::createLinearGradient(float x, float y, float dx,
                                             float dy) {
        return Gradient(vec2(x, y), vec2(dx, dy));
    }

    void Context2D::setFillStyle(const DrawStyle& style) {
        m_fillStyle = style;
    }

    void Context2D::setStrokeStyle(const DrawStyle& style) {
        m_strokeStyle = style;
    }

    void Context2D::vertex(vec2 v) { glVertex2f(v.x, v.y); }

    void Context2D::setColor(Color c) {
        vec4 rgba = c.asVec4();
        glColor4f(rgba.r, rgba.g, rgba.b, rgba.a);
    }

    void Context2D::targetStencil() {
        glClear(GL_STENCIL_BUFFER_BIT);
        glStencilMask(0xFF);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    }

    void Context2D::targetColor() {
        glStencilMask(0xFF);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
    }

    void Context2D::drawRect(vec2 a, vec2 b) {
        glBegin(GL_TRIANGLE_STRIP);

        glVertex2f(a.x, a.y);
        glVertex2f(a.x, b.y);
        glVertex2f(b.x, a.y);
        glVertex2f(b.x, b.y);

        glEnd();
    }

    void Context2D::drawTriangle(const Triangle& triangle) {
        glBegin(GL_TRIANGLES);

        vertex(triangle.a);
        vertex(triangle.b);
        vertex(triangle.c);

        glEnd();
    }

    template <typename T>
    const T& access(const std::vector<T>& v, ptrdiff_t i) {
        while (i < 0) {
            i += v.size();
        }
        return v[i % v.size()];
    }

    vec2 perp(vec2 in) { return vec2(-in.y, in.x); }

    vec2 solve(mat2 a, vec2 b) {
        vec2 x((b.y - ((a[0].y * b.x) / a[0].x)) /
               (a[1].y - ((a[1].x * a[0].y) / a[0].x)));
        x.x = (b.x - (a[1].x * x.y)) / a[0].x;
        return x;
    }

    void Context2D::drawPath(const Path& path) {
        // TODO Deal with line caps
        // TODO Avoid hardcoding resolution
        Mesh mesh = path.toMesh(10.0f);
        for (size_t i = 0; i < mesh.points.size() - 1; i++) {
            vec2 d = access(mesh.points, i - 1);
            vec2 a = access(mesh.points, i);
            vec2 b = access(mesh.points, i + 1);
            vec2 c = access(mesh.points, i + 2);

            vec2 da = a - d;
            vec2 ab = b - a;
            vec2 bc = c - b;

            if (i == 0 && !path.closed) {
                da = ab;
            }

            if (i == mesh.points.size() - 2 && !path.closed) {
                bc = ab;
            }

            vec2 dap = normalize(perp(da));
            vec2 abp = normalize(perp(ab));
            vec2 bcp = normalize(perp(bc));

            vec2 ax;
            vec2 bx;
            if (abs(abp.x) < 0.0001f) {
                ax = solve(transpose(mat2(dap, abp)), vec2(lineWidth / 2.0f));
                bx = solve(transpose(mat2(bcp, abp)), vec2(lineWidth / 2.0f));
            } else {
                ax = solve(transpose(mat2(abp, dap)), vec2(lineWidth / 2.0f));
                bx = solve(transpose(mat2(abp, bcp)), vec2(lineWidth / 2.0f));
            }
            float bendFactorA = dot(abp, dap);
            float bendFactorB = dot(abp, bcp);
            if (bendFactorA > 0.999f) {
                ax = abp * (lineWidth / 2.0f);
            }
            if (bendFactorB > 0.999f) {
                bx = abp * (lineWidth / 2.0f);
            }

            glBegin(GL_TRIANGLE_STRIP);

            if (bendFactorA < -0.9f) {
                // Handle sharp angles
                vertex(a + ax);
                vertex(a - ax);
            } else {
                vertex(a + ax);
                vertex(a - ax);
            }

            if (bendFactorB < -0.9f) {
                // Handle sharp angles
                vertex(b + bx);
                vertex(b - bx);
            } else {
                vertex(b + bx);
                vertex(b - bx);
            }

            glEnd();
        }
    }

    void Context2D::drawFill(const DrawStyle& style) {
        switch (style.type) {
        case DrawStyle::Type::Color:
            fillWithColor(style.color);
            break;
        case DrawStyle::Type::Gradient:
            fillWithGradient(style.gradient);
            break;
        case DrawStyle::Type::Pattern:
            // fillWithPattern(m_drawStyle.pattern);
            break;
        }
    }

    void Context2D::fillWithColor(const Color& color) {
        setColor(color);
        glPushMatrix();
        glLoadIdentity();
        drawRect(vec2(), m_canvas.getDimensions());
        glPopMatrix();
    }

    void Context2D::fillWithGradient(const Gradient& gradient) {}

    mat4& Context2D::transform() { return m_transformStack.top(); }

    const mat4& Context2D::transform() const { return m_transformStack.top(); }
} // namespace canvas
