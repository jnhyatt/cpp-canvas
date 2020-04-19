#include "cpp-canvas/canvas.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/perpendicular.hpp>
#include <Windows.h>
#include <gl/GL.h>

namespace canvas {
    Canvas::Canvas()
        : m_context(*this), backgroundColor(0.0f, 0.0f, 0.0f, 1.0f) {}

    void Canvas::initialize() {
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_STENCIL_TEST);
        glDisable(GL_DEPTH_TEST);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    Context2D& Canvas::getContext2D() { return m_context; }

    const Context2D& Canvas::getContext2D() const { return m_context; }

    ivec2 Canvas::getDimensions() const { return m_dimensions; }

    void Canvas::onResize(ivec2 dimensions) {
        m_dimensions = dimensions;
        glViewport(0, 0, dimensions.x, dimensions.y);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, dimensions.x, dimensions.y, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
    }
} // namespace canvas
