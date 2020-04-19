#pragma once

#include "cpp-canvas/canvas.h"
#include "cpp-canvas/export.h"

#include <glm/glm.hpp>
#include <functional>
#include <string>
#include <vector>
#include <Windows.h>

namespace canvas {
    class App;

    class MouseEvent {
    public:
        MouseEvent(const App& app);

    private:
        float getOffsetX();
        float getOffsetY();
        float getDeltaX();
        float getDeltaY();
        float getScreenX();
        float getScreenY();

    public:
        Getter<float, MouseEvent, &getOffsetX> offsetX;
        Getter<float, MouseEvent, &getOffsetY> offsetY;
        Getter<float, MouseEvent, &getOffsetX> clientX;
        Getter<float, MouseEvent, &getOffsetY> clientY;
        Getter<float, MouseEvent, &getOffsetX> pageX;
        Getter<float, MouseEvent, &getOffsetY> pageY;
        Getter<float, MouseEvent, &getDeltaX> movementX;
        Getter<float, MouseEvent, &getDeltaY> movementY;
        Getter<float, MouseEvent, &getScreenX> screenX;
        Getter<float, MouseEvent, &getScreenY> screenY;

    private:
        char keys[256];
        vec2 m_lastCursor;
        vec2 m_cursor;
        vec2 m_windowOrigin;
    };

    class CPP_CANVAS_API App {
    public:
        App();
        ~App();

        void setCanvasSize(const size_t width, const size_t height);
        void setBackgroundColor(const std::string& color);
        void requestAnimationFrame(std::function<void()> func);

        static LRESULT CALLBACK eventCallback(HWND hWindow, UINT message,
                                              WPARAM wParam, LPARAM lParam);

        Canvas& canvas();

    private:
        Canvas m_canvas;

        HDC m_hDeviceContext;
        HGLRC m_hRenderingContext;
        HINSTANCE m_hInstance;
        HWND m_hWindow;
        const std::string m_className;
        std::function<void()> m_animationHandler;
        bool m_running;
    };
} // namespace canvas
