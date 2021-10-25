//
// Created by guozhenxiong on 2021-07-21.
//

#include "window_win32.h"

#include <tchar.h>
#include <windowsx.h>
#include "engine/rasterizer/rasterizer.h"
#include "angle_gl_window_context.h"
#include <third_party/ConvertUTF/UTF8.h>
namespace sm {

namespace {

static int gWindowX = CW_USEDEFAULT;
static int gWindowY = 0;
static int gWindowWidth = CW_USEDEFAULT;
static int gWindowHeight = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    int x_pos = 0, y_pos = 0;
    UINT width = 0, height = 0;
    UINT button_pressed = 0;

    WindowWin32 *window = (WindowWin32 *) GetWindowLongPtr(hWnd, GWLP_USERDATA);

    bool eventHandled = false;

    switch (message) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            //window->OnPaint();
            EndPaint(hWnd, &ps);
            eventHandled = true;
            break;
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP:
            if (message == WM_LBUTTONUP) {
                ReleaseCapture();
            }
            button_pressed = message;
            if (message == WM_XBUTTONUP) {
                button_pressed = GET_XBUTTON_WPARAM(wparam);
            }
            x_pos = GET_X_LPARAM(lparam);
            y_pos = GET_Y_LPARAM(lparam);

            window->HitTest(x_pos, y_pos);
        case WM_CLOSE:
            PostQuitMessage(0);
            eventHandled = true;
            break;

        case WM_ACTIVATE:
            // disable/enable rendering here, depending on wParam != WA_INACTIVE
            break;

        case WM_CHAR: {
            wchar_t character = static_cast<wchar_t>(wparam);
            std::u16string text({character});
            std::string utf8;
            UTF::UTF16ToUTF8(text, utf8);

            //eventHandled = window->OnChar(utf8);
            break;
        }
        default:
            return DefWindowProc(hWnd, message, wparam, lparam);
    }

    return eventHandled ? 0 : 1;
}
} // anonymous namespace

// | static |
Window *Window::CreateNativeWindow(void *platformData)
{
    HINSTANCE hInstance = (HINSTANCE) platformData;

    WindowWin32 *window = new WindowWin32();
    if (!window->Init(hInstance)) {
        delete window;
        return nullptr;
    }

    return window;
}

WindowWin32::WindowWin32()
{
}

bool WindowWin32::Attach()
{
    window_context_ = MakeAngleContextForWin(hWnd_, {});
    engine_->SetRasterizer(std::make_unique<Rasterizer>(window_context_.get()));
    return 0;
}

bool WindowWin32::Init(HINSTANCE hInstance)
{
    hInstance_ = hInstance ? hInstance : GetModuleHandle(nullptr);

    // The main window class name
    static const TCHAR gSZWindowClass[] = _T("SkiaApp");

    static WNDCLASSEX wcex;
    static bool wcexInit = false;
    if (!wcexInit) {
        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance_;
        wcex.hIcon = LoadIcon(hInstance_, (LPCTSTR) IDI_WINLOGO);
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = gSZWindowClass;
        wcex.hIconSm = LoadIcon(hInstance_, (LPCTSTR) IDI_WINLOGO);

        if (!RegisterClassEx(&wcex)) {
            return false;
        }
        wcexInit = true;
    }

    hWnd_ = CreateWindow(gSZWindowClass, nullptr, WS_OVERLAPPEDWINDOW,
                         gWindowX, gWindowY, gWindowWidth, gWindowHeight,
                         nullptr, nullptr, hInstance_, nullptr);
    if (!hWnd_) {
        return false;
    }

    SetWindowLongPtr(hWnd_, GWLP_USERDATA, (LONG_PTR) this);
    RegisterTouchWindow(hWnd_, 0);

    return true;
}

void WindowWin32::OnInvalid()
{
    InvalidateRect(hWnd_, nullptr, false);
}

void WindowWin32::Show()
{
    ShowWindow(hWnd_, SW_SHOW);
}

} // namespace sm