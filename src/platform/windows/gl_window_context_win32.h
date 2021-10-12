//
// Created by guozhenxiong on 2021-07-24.
//

#ifndef SHOWMAKER_GL_WINDOW_CONTEXT_WIN32_H
#define SHOWMAKER_GL_WINDOW_CONTEXT_WIN32_H

#include "gl_window_context.h"

#include <windows.h>
namespace sm {
class GLWindowContextWin32 : public GLWindowContext {
public:
    GLWindowContextWin32(HWND, const DisplayParams&);
    ~GLWindowContextWin32() override;

protected:
    void OnSwapBuffers() override;

    sk_sp<const GrGLInterface> OnInitializeContext() override;
    void OnDestroyContext() override;

private:
    HWND              fHWND;
    HGLRC             fHGLRC;

    using INHERITED = GLWindowContext;
};
} // namespace sm

#endif //SHOWMAKER_GL_WINDOW_CONTEXT_WIN32_H
