//
// Created by guozhenxiong on 2021-07-24.
//

#include "gl_window_context_win32.h"
namespace wtf {

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

sk_sp<const GrGLInterface> GLWindowContextWin32::OnInitializeContext() {
    HDC dc = GetDC(fHWND);

    fHGLRC = SkCreateWGLContext(dc, display_params_.fMSAASampleCount, false /* deepColor */,
                                kGLPreferCompatibilityProfile_SkWGLContextRequest);
    if (NULL == fHGLRC) {
        return nullptr;
    }

    SkWGLExtensions extensions;
    if (extensions.hasExtension(dc, "WGL_EXT_swap_control")) {
        extensions.swapInterval(fDisplayParams.fDisableVsync ? 0 : 1);
    }

    // Look to see if RenderDoc is attached. If so, re-create the context with a core profile
    if (wglMakeCurrent(dc, fHGLRC)) {
        auto interface = GrGLMakeNativeInterface();
        bool renderDocAttached = interface->hasExtension("GL_EXT_debug_tool");
        interface.reset(nullptr);
        if (renderDocAttached) {
            wglDeleteContext(fHGLRC);
            fHGLRC = SkCreateWGLContext(dc, fDisplayParams.fMSAASampleCount, false /* deepColor */,
                                        kGLPreferCoreProfile_SkWGLContextRequest);
            if (NULL == fHGLRC) {
                return nullptr;
            }
        }
    }

    if (wglMakeCurrent(dc, fHGLRC)) {
        glClearStencil(0);
        glClearColor(0, 0, 0, 0);
        glStencilMask(0xffffffff);
        glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // use DescribePixelFormat to get the stencil and color bit depth.
        int pixelFormat = GetPixelFormat(dc);
        PIXELFORMATDESCRIPTOR pfd;
        DescribePixelFormat(dc, pixelFormat, sizeof(pfd), &pfd);
        fStencilBits = pfd.cStencilBits;

        // Get sample count if the MSAA WGL extension is present
        if (extensions.hasExtension(dc, "WGL_ARB_multisample")) {
            static const int kSampleCountAttr = SK_WGL_SAMPLES;
            extensions.getPixelFormatAttribiv(dc,
                                              pixelFormat,
                                              0,
                                              1,
                                              &kSampleCountAttr,
                                              &fSampleCount);
            fSampleCount = std::max(fSampleCount, 1);
        } else {
            fSampleCount = 1;
        }

        RECT rect;
        GetClientRect(fHWND, &rect);
        fWidth = rect.right - rect.left;
        fHeight = rect.bottom - rect.top;
        glViewport(0, 0, fWidth, fHeight);
    }
    return GrGLMakeNativeInterface();
}


void GLWindowContextWin32::OnDestroyContext() {
    wglDeleteContext(fHGLRC);
    fHGLRC = NULL;
}


void GLWindowContextWin32::OnSwapBuffers() {
    HDC dc = GetDC((HWND)fHWND);
    SwapBuffers(dc);
    ReleaseDC((HWND)fHWND, dc);
}
} // namespace wtf