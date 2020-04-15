#pragma once

#include "canvas.h"
#include "export.h"

#include <Windows.h>

#include <glm/glm.hpp>
#include <functional>
#include <string>
#include <vector>

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
    const Canvas& canvas() const;

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
