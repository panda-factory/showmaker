//
// Created by guozhenxiong on 2021-11-21.
//

#ifndef SHOWMAKER_GL_WINDOW_CNOTEXT_ANDROID_H
#define SHOWMAKER_GL_WINDOW_CNOTEXT_ANDROID_H

#include "window/gl_window_context.h"
// OpenGL ES and EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

namespace sm {
class GLWindowContextAndroid {
private:
    EGLDisplay egl_display_ = EGL_NO_DISPLAY;
    EGLContext egl_context_ = EGL_NO_CONTEXT;
    EGLSurface egl_surface_ = EGL_NO_SURFACE;
    ANativeWindow* fNativeWindow = nullptr;
};
} // namespace sm

#endif //SHOWMAKER_GL_WINDOW_CNOTEXT_ANDROID_H
