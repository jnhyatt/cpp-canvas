#pragma once

#include "cpp-canvas/context.h"
#include "cpp-canvas/export.h"
#include "cpp-canvas/field.h"
#include "cpp-canvas/geometry.h"
#include "cpp-canvas/style.h"

#include <functional>
#include <glm/glm.hpp>
#include <stack>
#include <string>
#include <unordered_map>

using namespace glm;

namespace canvas {
    class CPP_CANVAS_API KeyboardEvent {
    public:
        KeyboardEvent(const Canvas& canvas, const std::string& eventType);

    private:
        std::string keyString();

    public:
        Getter<std::string, KeyboardEvent, &keyString> key;

    private:
        const Canvas& m_canvas;
        std::string m_eventType;
    };

    class CPP_CANVAS_API MouseEvent {
    public:
        MouseEvent(const Canvas& canvas, const std::string& eventType);

    private:
        int getOffsetX();
        int getOffsetY();
        int getDeltaX();
        int getDeltaY();
        int getScreenX();
        int getScreenY();
        int getWhichButton();
        int getDownButton();
        int getDownButtons();

    public:
        Getter<int, MouseEvent, &getOffsetX> offsetX;
        Getter<int, MouseEvent, &getOffsetY> offsetY;
        Getter<int, MouseEvent, &getOffsetX> clientX;
        Getter<int, MouseEvent, &getOffsetY> clientY;
        Getter<int, MouseEvent, &getOffsetX> pageX;
        Getter<int, MouseEvent, &getOffsetY> pageY;
        Getter<int, MouseEvent, &getDeltaX> movementX;
        Getter<int, MouseEvent, &getDeltaY> movementY;
        Getter<int, MouseEvent, &getScreenX> screenX;
        Getter<int, MouseEvent, &getScreenY> screenY;
        Getter<int, MouseEvent, &getWhichButton> which;
        Getter<int, MouseEvent, &getDownButton> button;
        Getter<int, MouseEvent, &getDownButtons> buttons;

    private:
        const Canvas& m_canvas;
        std::string m_eventType;
    };

    class CPP_CANVAS_API Canvas {
    public:
        typedef std::function<void()> Handler;
        typedef std::function<void(const MouseEvent&)> MouseHandler;
        typedef std::function<void(const KeyboardEvent&)> KeyHandler;

        Canvas();

        Context2D& getContext2D();
        const Context2D& getContext2D() const;

        ivec2 cursorPosition() const;
        ivec2 lastCursorPosition() const;
        int lastMouseButton() const;
        int lastKey() const;
        bool mouseButtonDown(const int button) const;
        bool keyDown(const int key) const;
        bool isCapital() const;
        ivec2 getWindowOrigin() const;
        ivec2 getDimensions() const;

        void addEventListener(const std::string& type, Handler handler);
        void addEventListener(const std::string& type, MouseHandler handler);
        void addEventListener(const std::string& type, KeyHandler handler);

        void onInitialize();
        void onResize(const ivec2 position, const ivec2 dimensions);
        void onMouseMove(const ivec2 cursor);
        void onMouseDown(const int button);
        void onMouseUp(const int button);
        void onKeyDown(const int key);
        void onKeyUp(const int key);

        Color backgroundColor;

    private:
        ivec2 m_cursor;
        ivec2 m_lastCursor;
        ivec2 m_windowOrigin;
        ivec2 m_windowDimensions;
        int m_lastMouseButton;
        int m_lastKey;
        bool m_mouseButtons[3];
        bool m_keys[256];

        std::unordered_map<std::string, std::vector<MouseHandler>>
            m_mouseHandlers;
        std::unordered_map<std::string, std::vector<KeyHandler>> m_keyHandlers;

        Context2D m_context;
    };
} // namespace canvas
