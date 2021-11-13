//
// Created by guozhenxiong on 2021-07-24.
//

#include "gl_window_context_win32.h"

#include "platform/win32/window_context_factory.h"
namespace sm {

std::unique_ptr<WindowContext> WindowContextFactory::MakeGLForWin(HWND wnd, const DisplayParams& params)
{
    std::unique_ptr<WindowContext> ctx(new GLWindowContextWin32(wnd, params));
    if (!ctx->IsValid()) {
        return nullptr;
    }
    return ctx;
}

GLWindowContextWin32::GLWindowContextWin32(HWND wnd, const DisplayParams& params)
        : INHERITED(params)
        , fHWND(wnd)
        , fHGLRC(NULL) {

    // any config code here (particularly for msaa)?

    this->InitializeContext();
}

GLWindowContextWin32::~GLWindowContextWin32() {
    this->DestroyContext();
}

void GLWindowContextWin32::OnInitializeContext() {
}


void GLWindowContextWin32::OnDestroyContext() {
    wglDeleteContext(fHGLRC);
    fHGLRC = NULL;
}


void GLWindowContextWin32::OnSwapBuffers() {
    HDC dc = GetDC((HWND)fHWND);
    //SwapBuffers(dc);
    ReleaseDC((HWND)fHWND, dc);
}
} // namespace sm