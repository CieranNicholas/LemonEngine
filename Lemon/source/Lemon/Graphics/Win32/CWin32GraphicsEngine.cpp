#include <Lemon/Graphics/LemGraphicsEngine.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <Windows.h>
#include <cassert>
#include <stdexcept>

LemGraphicsEngine::LemGraphicsEngine()
{
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpszClassName = L"DummyWindow";
    wc.lpfnWndProc = &DefWindowProc;
    wc.style = CS_OWNDC;

    auto classId = RegisterClassEx(&wc);
    assert(classId);
    
    auto dummyWindow = CreateWindowEx(
        NULL,
        MAKEINTATOM(classId),
        L"",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        NULL,
        NULL);

    assert(dummyWindow);

    PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
    pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixelFormatDesc.nVersion = 1;
    pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
    pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormatDesc.cColorBits = 32;
    pixelFormatDesc.cAlphaBits = 8;
    pixelFormatDesc.cDepthBits = 24;
    pixelFormatDesc.cStencilBits = 8;
    pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;
    
    auto dummyDC = GetDC(dummyWindow);
    auto pixelFormat = ChoosePixelFormat(dummyDC, &pixelFormatDesc);
    SetPixelFormat(dummyDC, pixelFormat, &pixelFormatDesc);

    auto dummyContext = wglCreateContext(dummyDC);
    assert(dummyContext);

    wglMakeCurrent(dummyDC, dummyContext);

    if (!gladLoadWGL(dummyDC))
        throw std::runtime_error("LemGraphicsEngine - Error - gladLoadWGL failed");
    if (!gladLoadGL())
        throw std::runtime_error("LemGraphicsEngine - Error - gladLoadGL failed");

    wglMakeCurrent(dummyDC, 0);
    wglDeleteContext(dummyContext);
    ReleaseDC(dummyWindow, dummyDC);
    DestroyWindow(dummyWindow);
}

LemGraphicsEngine::~LemGraphicsEngine()
{
}