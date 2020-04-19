#include "cpp-canvas/canvas.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/perpendicular.hpp>
#include <Windows.h>
#include <gl/GL.h>

namespace canvas {
    MouseEvent::MouseEvent(const Canvas& canvas, const std::string& eventType)
        : offsetX(*this), offsetY(*this), clientX(*this), clientY(*this),
          pageX(*this), pageY(*this), movementX(*this), movementY(*this),
          screenX(*this), screenY(*this), which(*this), button(*this),
          buttons(*this), m_canvas(canvas), m_eventType(eventType) {}

    int MouseEvent::getOffsetX() {
        return m_canvas.cursorPosition().x - m_canvas.getWindowOrigin().x;
    }

    int MouseEvent::getOffsetY() {
        return m_canvas.cursorPosition().y - m_canvas.getWindowOrigin().y;
    }

    int MouseEvent::getDeltaX() {
        return m_canvas.cursorPosition().x - m_canvas.lastCursorPosition().x;
    }

    int MouseEvent::getDeltaY() {
        return m_canvas.cursorPosition().y - m_canvas.lastCursorPosition().y;
    }

    int MouseEvent::getScreenX() { return m_canvas.cursorPosition().x; }

    int MouseEvent::getScreenY() { return m_canvas.cursorPosition().y; }

    int MouseEvent::getWhichButton() {
        if (m_canvas.mouseButtonDown(0)) {
            return 1;
        } else if (m_canvas.mouseButtonDown(1)) {
            return 2;
        } else if (m_canvas.mouseButtonDown(2)) {
            return 3;
        }
        return 0;
    }

    int MouseEvent::getDownButton() {
        if (m_eventType == "mousedown") {
            return m_canvas.lastMouseButton();
        }
        return 0;
    }

    int MouseEvent::getDownButtons() {
        int accum = 0;
        if (m_eventType == "mousedown") {
            if (m_canvas.mouseButtonDown(0)) {
                accum += 1;
            }
            if (m_canvas.mouseButtonDown(1)) {
                accum += 4;
            }
            if (m_canvas.mouseButtonDown(2)) {
                accum += 2;
            }
        }
        return accum;
    }

    Canvas::Canvas()
        : m_context(*this), backgroundColor(0.0f, 0.0f, 0.0f, 1.0f) {}

    Context2D& Canvas::getContext2D() { return m_context; }

    const Context2D& Canvas::getContext2D() const { return m_context; }

    ivec2 Canvas::cursorPosition() const { return m_cursor; }

    ivec2 Canvas::lastCursorPosition() const { return m_lastCursor; }

    int Canvas::lastMouseButton() const { return m_lastMouseButton; }

    bool Canvas::mouseButtonDown(const int index) const {
        return m_mouseButtons[index];
    }

    ivec2 Canvas::getWindowOrigin() const { return m_windowOrigin; }

    ivec2 Canvas::getDimensions() const { return m_windowDimensions; }

    void Canvas::onInitialize() {
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_STENCIL_TEST);
        glDisable(GL_DEPTH_TEST);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void Canvas::onResize(const ivec2 position, const ivec2 dimensions) {
        m_windowDimensions = dimensions;
        m_windowOrigin = position;
        glViewport(0, 0, dimensions.x, dimensions.y);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, dimensions.x, dimensions.y, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
    }

    void Canvas::onMouseMove(const ivec2 cursor) {
        vec2 screenSpaceCursor = cursor + m_windowOrigin;
        m_lastCursor = m_cursor;
        m_cursor = screenSpaceCursor;
        for (const MouseHandler& handler: m_mouseHandlers["mousemove"]) {
            handler(MouseEvent(*this, "mousemove"));
        }
    }

    void Canvas::onMouseDown(const int button) {
        m_mouseButtons[button] = true;
        m_lastMouseButton = button;
        for (const MouseHandler& handler: m_mouseHandlers["mousedown"]) {
            handler(MouseEvent(*this, "mousedown"));
        }
    }

    void Canvas::onMouseUp(const int button) {
        m_mouseButtons[button] = false;
        m_lastMouseButton = button;
        for (const MouseHandler& handler: m_mouseHandlers["mouseup"]) {
            handler(MouseEvent(*this, "mouseup"));
        }
    }

    void Canvas::addEventListener(const std::string& type, Handler handler) {
        addEventListener(type, [handler](const MouseEvent&) { handler(); });
    }

    void Canvas::addEventListener(const std::string& type,
                                  MouseHandler handler) {
        m_mouseHandlers[type].push_back(std::move(handler));
    }
} // namespace canvas
