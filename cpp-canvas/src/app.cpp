#include "cpp-canvas/app.h"

#include <glm/glm.hpp>
#include <sstream>

namespace canvas {
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

        m_canvas.onInitialize();

        ShowWindow(m_hWindow, SW_SHOWDEFAULT);

        pApp = this;
    }

    App::~App() {}

    void App::setCanvasSize(const size_t width, const size_t height) {
        SetWindowPos(m_hWindow, NULL, 0, 0, width, height,
                     SWP_NOMOVE | SWP_NOZORDER);
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
        if (pApp) {
            switch (message) {
            case WM_CLOSE:
                PostQuitMessage(0);
                return 0;
            case WM_MOVE:
                pApp->canvas().onResize(ivec2((int)(short)LOWORD(lParam),
                                              (int)(short)HIWORD(lParam)),
                                        pApp->canvas().getDimensions());
                return 0;
            case WM_SIZE:
                pApp->canvas().onResize(pApp->canvas().getWindowOrigin(),
                                        ivec2((int)(short)LOWORD(lParam),
                                              (int)(short)HIWORD(lParam)));
                return 0;
            case WM_MOUSEMOVE:
                pApp->canvas().onMouseMove(ivec2((int)(short)LOWORD(lParam),
                                                 (int)(short)HIWORD(lParam)));
                return 0;
            case WM_LBUTTONDOWN:
                pApp->canvas().onMouseDown(0);
                return 0;
            case WM_MBUTTONDOWN:
                pApp->canvas().onMouseDown(1);
                return 0;
            case WM_RBUTTONDOWN:
                pApp->canvas().onMouseDown(2);
                return 0;
            case WM_LBUTTONUP:
                pApp->canvas().onMouseUp(0);
                return 0;
            case WM_MBUTTONUP:
                pApp->canvas().onMouseUp(1);
                return 0;
            case WM_RBUTTONUP:
                pApp->canvas().onMouseUp(2);
                return 0;
            case WM_KEYDOWN:
                pApp->canvas().onKeyDown(wParam);
                return 0;
            case WM_KEYUP:
                pApp->canvas().onKeyUp(wParam);
            }
        }

        return DefWindowProc(hWindow, message, wParam, lParam);
    }

    Canvas& App::canvas() { return m_canvas; }
} // namespace canvas
