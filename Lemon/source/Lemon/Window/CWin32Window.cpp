#include <Lemon/Window/LemWindow.h>
#include <Windows.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LemWindow* window = (LemWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	switch (msg)
	{
	case WM_DESTROY:
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return NULL;
}

LemWindow::LemWindow()
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"LemWindow";
	wc.lpfnWndProc = &WndProc;
	wc.style = CS_OWNDC;
	
	auto classId = RegisterClassEx(&wc);
	assert(classId);

	RECT rc = { 0, 0, 1024, 768 };
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

	m_handle = CreateWindowEx(
		NULL,
		MAKEINTATOM(classId),
		L"Lemon Engine",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right-rc.left,
		rc.bottom-rc.top,
		NULL,
		NULL,
		NULL,
		NULL);

	assert(m_handle);

	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow((HWND)m_handle, SW_SHOW);
	UpdateWindow((HWND)m_handle);

	// Creating OpenGL Render Context

	auto hDC = GetDC((HWND)m_handle);

	int pixelFormatAttributes[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0
	};

	int pixelFormat = 0;
	UINT numFormats = 0;
	wglChoosePixelFormatARB(hDC, pixelFormatAttributes, nullptr, 1, &pixelFormat, &numFormats);
	assert(numFormats);

	PIXELFORMATDESCRIPTOR pixelformatdesc = {};
	DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelformatdesc);
	SetPixelFormat(hDC, pixelFormat, &pixelformatdesc);

	int openGLAttributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};
	
	m_context = wglCreateContextAttribsARB(hDC, nullptr, openGLAttributes);
	assert(m_context);
}

LemWindow::~LemWindow()
{
	wglDeleteContext(HGLRC(m_context));
	DestroyWindow((HWND)m_handle);
}

void LemWindow::makeCurrentContext()
{
	wglMakeCurrent(GetDC(HWND(m_handle)), HGLRC(m_context));
}

void LemWindow::present(bool vsync)
{
	wglSwapIntervalEXT(vsync);
	wglSwapLayerBuffers(GetDC(HWND(m_handle)), WGL_SWAP_MAIN_PLANE);
}
