//
// Created by guozhenxiong on 2021-07-23.
//

#ifndef XXX_ANGLE_GL_WINDOW_CONTEXT_H
#define XXX_ANGLE_GL_WINDOW_CONTEXT_H

#include "gl_window_context.h"
// OpenGL ES and EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <windows.h>

namespace wtf {
std::unique_ptr<WindowContext> MakeAngleContextForWin(HWND wnd, const DisplayParams &params);

class AngleGLWindowContext : public GLWindowContext {
public:
    bool CreateSurface(HWND hWnd, EGLint width, EGLint height);

    AngleGLWindowContext(HWND wnd, const DisplayParams &params);

protected:

    sk_sp<SkSurface> CreateRenderSurface() override;

    sk_sp<const GrGLInterface> OnInitializeContext() override;

    void OnDestroyContext() override;

    void OnSwapBuffers() override;

private:
    bool InitializeEGL(
            PFNEGLGETPLATFORMDISPLAYEXTPROC egl_get_platform_display_EXT,
            const EGLint *config,
            bool should_log);

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

#endif //XXX_ANGLE_GL_WINDOW_CONTEXT_H
