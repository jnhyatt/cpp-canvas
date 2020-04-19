#pragma once

#include "cpp-canvas/canvas.h"
#include "cpp-canvas/export.h"

#include <glm/glm.hpp>
#include <functional>
#include <string>
#include <vector>
#include <Windows.h>

namespace canvas {
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

    App* pApp = nullptr;
} // namespace canvas
