#include "cpp-canvas/app.h"

#include <glm/glm.hpp>
#include <sstream>

namespace canvas {
    MouseEvent::MouseEvent(const App& app)
        : offsetX(*this), offsetY(*this), clientX(*this), clientY(*this),
          pageX(*this), pageY(*this), movementX(*this), movementY(*this),
          screenX(*this), screenY(*this) {}

    float MouseEvent::getOffsetX() { return m_cursor.x - m_windowOrigin.x; }

    float MouseEvent::getOffsetY() { return m_cursor.y - m_windowOrigin.y; }

    float MouseEvent::getDeltaX() { return m_cursor.x - m_lastCursor.x; }

    float MouseEvent::getDeltaY() { return m_cursor.y - m_lastCursor.y; }

    float MouseEvent::getScreenX() { return m_cursor.x; }

    float MouseEvent::getScreenY() { return m_cursor.y; }

    App::App()
        : m_hDeviceContext(NULL), m_hRenderingContext(NULL),
          m_hInstance(GetModuleHandle(NULL)), m_hWindow(NULL),
          m_className("canvas-app"), m_running(false) {
        WNDCLASS wc;

        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.lpfnWndProc = App::eventCallback;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = m_hInstance;
        wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = NULL;
        wc.lpszMenuName = NULL;
        wc.lpszClassName = m_className.c_str();

        RegisterClass(&wc);

        m_hWindow = CreateWindowEx(
            WS_EX_OVERLAPPEDWINDOW, m_className.c_str(), "Canvas",
            WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW, 0, 0, 640,
            480, NULL, NULL, m_hInstance, NULL);

        m_hDeviceContext = GetDC(m_hWindow);

        PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
            PFD_TYPE_RGBA, // The kind of framebuffer. RGBA or palette.
            32,            // Colordepth of the framebuffer.
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            24, // Number of bits for the depthbuffer
            8,  // Number of bits for the stencilbuffer
            0,  // Number of Aux buffers in the framebuffer.
            PFD_MAIN_PLANE,
            0,
            0,
            0,
            0};

        int pixelFormat = ChoosePixelFormat(m_hDeviceContext, &pfd);

        SetPixelFormat(m_hDeviceContext, pixelFormat, &pfd);

        m_hRenderingContext = wglCreateContext(m_hDeviceContext);
        wglMakeCurrent(m_hDeviceContext, m_hRenderingContext);

        m_canvas.initialize();

        ShowWindow(m_hWindow, SW_SHOWDEFAULT);
    }

    App::~App() {}

    void App::setCanvasSize(const size_t width, const size_t height) {
        SetWindowPos(m_hWindow, NULL, 0, 0, width, height,
                     SWP_NOMOVE | SWP_NOZORDER);
        m_canvas.onResize(ivec2(width, height));
    }

    void App::setBackgroundColor(const std::string& color) {
        m_canvas.backgroundColor = Color(color);
    }

    void App::requestAnimationFrame(std::function<void()> handler) {
        m_animationHandler = handler;
        if (!m_running) {
            m_running = true;
            while (m_running) {
                MSG msg;
                while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                    if (msg.message == WM_QUIT) {
                        m_running = false;
                    } else {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                }
                if (m_running) {
                    handler = m_animationHandler;
                    m_animationHandler = std::function<void()>();
                    if (handler) {
                        handler();
                    }
                    SwapBuffers(m_hDeviceContext);
                }
            }
        }
    }

    LRESULT CALLBACK App::eventCallback(HWND hWindow, UINT message,
                                        WPARAM wParam, LPARAM lParam) {
        switch (message) {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(hWindow, message, wParam, lParam);
    }

    Canvas& App::canvas() { return m_canvas; }
} // namespace canvas
