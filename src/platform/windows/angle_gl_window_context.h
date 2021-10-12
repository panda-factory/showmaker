//
// Created by guozhenxiong on 2021-07-23.
//

#ifndef SHOWMAKER_ANGLE_GL_WINDOW_CONTEXT_H
#define SHOWMAKER_ANGLE_GL_WINDOW_CONTEXT_H

#include "gl_window_context.h"
// OpenGL ES and EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <windows.h>

namespace sm {
std::unique_ptr<WindowContext> MakeAngleContextForWin(HWND wnd, const DisplayParams &params);

class AngleGLWindowContext : public GLWindowContext {
public:

    AngleGLWindowContext(HWND wnd, const DisplayParams &params);

    int MakeCurrent() override;

protected:

    int CreateSurface() override;

    sk_sp<const GrGLInterface> CreateGLInterface() override;

    void OnInitializeContext() override;

    void OnDestroyContext() override;

    void OnSwapBuffers() override;

private:

    EGLDisplay InitializeEGLDisplay(HDC hdc);

    bool InitializeEGL(
            PFNEGLGETPLATFORMDISPLAYEXTPROC egl_get_platform_display_EXT,
            const EGLint *config);

    HWND hWND_;
    EGLDisplay egl_display_ = EGL_NO_DISPLAY;
    EGLContext egl_context_ = EGL_NO_CONTEXT;
    EGLSurface egl_surface_ = EGL_NO_SURFACE;
    EGLint surface_width_ = 0;
    EGLint surface_height_ = 0;
    EGLConfig egl_config_;
    EGLContext egl_resource_context_;
};
}

#endif //SHOWMAKER_ANGLE_GL_WINDOW_CONTEXT_H
