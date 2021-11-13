//
// Created by guozhenxiong on 2021-07-24.
//

#ifndef SHOWMAKER_GL_WINDOW_CONTEXT_WIN32_H
#define SHOWMAKER_GL_WINDOW_CONTEXT_WIN32_H

#include "window/gl_window_context.h"

#include <Windows.h>
namespace sm {
class GLWindowContextWin32 : public GLWindowContext {
public:
    GLWindowContextWin32(HWND, const DisplayParams&);

    ~GLWindowContextWin32() override;

protected:
    sk_sp<const GrGLInterface> CreateGLInterface() override { return nullptr; }

    int CreateSurface() override { return 0; }

    int MakeCurrent() override { return 0; }

    void OnSwapBuffers() override;

    void OnInitializeContext() override;

    void OnDestroyContext() override;

private:
    HWND              fHWND;
    HGLRC             fHGLRC;

    using INHERITED = GLWindowContext;
};
} // namespace sm

#endif //SHOWMAKER_GL_WINDOW_CONTEXT_WIN32_H
