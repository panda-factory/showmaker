//
// Created by guozhenxiong on 2021-07-23.
//

#include "angle_gl_window_context.h"
#include <iostream>
#include "include/gpu/gl/GrGLAssembleInterface.h"
#include "third-party/skia/include/core/SkCanvas.h"
#include "third-party/skia/include/gpu/GrBackendSurface.h"
#include "third-party/skia/include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkRefCnt.h"
#include "include/core/SkSurface.h"

namespace wtf {
namespace {
static void LogEglError(std::string message)
{
    EGLint error = eglGetError();
    std::cerr << "EGL: " << message << std::endl;
    std::cerr << "EGL: eglGetError returned " << error << std::endl;
}

EGLDisplay get_angle_egl_display(HDC hdc) {
    PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT;
    eglGetPlatformDisplayEXT =
            (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");

    // We expect ANGLE to support this extension
    if (!eglGetPlatformDisplayEXT) {
        return EGL_NO_DISPLAY;
    }

    // We currently only support D3D11 ANGLE.
    static constexpr EGLint kType = EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE;
    static constexpr EGLint attribs[] = {EGL_PLATFORM_ANGLE_TYPE_ANGLE, kType, EGL_NONE};
    return eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, hdc, attribs);
}
}

std::unique_ptr<WindowContext> MakeAngleContextForWin(HWND wnd, const DisplayParams &params)
{
    std::unique_ptr<WindowContext> ctx(new AngleGLWindowContext(wnd, params));
    if (!ctx->IsValid()) {
        return nullptr;
    }
    return ctx;
}

AngleGLWindowContext::AngleGLWindowContext(HWND wnd, const DisplayParams &params)
        : GLWindowContext(params), hWND_(wnd)
{
    this->InitializeContext();
}

bool AngleGLWindowContext::CreateSurface(HWND hWnd,
                                         EGLint width,
                                         EGLint height)
{
    if (!hWnd) {
        return false;
    }

    EGLSurface surface = EGL_NO_SURFACE;

    const EGLint surfaceAttributes[] = {
            EGL_FIXED_SIZE_ANGLE, EGL_TRUE, EGL_WIDTH, width,
            EGL_HEIGHT, height, EGL_NONE};

    surface = eglCreateWindowSurface(
            egl_display_, egl_config_,
            static_cast<EGLNativeWindowType>(hWnd),
            surfaceAttributes);

    if (surface == EGL_NO_SURFACE) {
        LogEglError("Surface creation failed.");
    }

    surface_width_ = width;
    surface_height_ = height;
    egl_surface_ = surface;
    return true;
}

bool AngleGLWindowContext::InitializeEGL(
        PFNEGLGETPLATFORMDISPLAYEXTPROC egl_get_platform_display_EXT,
        const EGLint *config,
        bool should_log)
{
    egl_display_ = egl_get_platform_display_EXT(EGL_PLATFORM_ANGLE_ANGLE,
                                                EGL_DEFAULT_DISPLAY, config);

    if (egl_display_ == EGL_NO_DISPLAY) {
        if (should_log) {
            LogEglError("Failed to get a compatible EGLdisplay");
        }
        return false;
    }

    if (eglInitialize(egl_display_, nullptr, nullptr) == EGL_FALSE) {
        if (should_log) {
            LogEglError("Failed to initialize EGL via ANGLE");
        }
        return false;
    }

    return true;
}

sk_sp<const GrGLInterface> AngleGLWindowContext::OnInitializeContext()
{
    HDC dc = GetDC(hWND_);
    egl_display_ = get_angle_egl_display(dc);
    if (EGL_NO_DISPLAY == egl_display_) {
        return nullptr;
    }

    EGLint majorVersion;
    EGLint minorVersion;
    if (!eglInitialize(egl_display_, &majorVersion, &minorVersion)) {
        SkDebugf("Could not initialize display!\n");
        return nullptr;
    }
    EGLint numConfigs;
    sample_count_ = this->GetDisplayParams().fMSAASampleCount;
    const int sampleBuffers = sample_count_ > 1 ? 1 : 0;
    const int eglSampleCnt = sample_count_ > 1 ? sample_count_ : 0;
    const EGLint configAttribs[] = {EGL_RENDERABLE_TYPE,
            // We currently only support ES3.
                                    EGL_OPENGL_ES3_BIT,
                                    EGL_RED_SIZE,
                                    8,
                                    EGL_GREEN_SIZE,
                                    8,
                                    EGL_BLUE_SIZE,
                                    8,
                                    EGL_ALPHA_SIZE,
                                    8,
                                    EGL_SAMPLE_BUFFERS,
                                    sampleBuffers,
                                    EGL_SAMPLES,
                                    eglSampleCnt,
                                    EGL_NONE};

    EGLConfig surfaceConfig;
    if (!eglChooseConfig(egl_display_, configAttribs, &surfaceConfig, 1, &numConfigs)) {
        SkDebugf("Could not create choose config!\n");
        return nullptr;
    }
    // We currently only support ES3.
    const EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    egl_context_ = eglCreateContext(egl_display_, surfaceConfig, nullptr, contextAttribs);
    if (EGL_NO_CONTEXT == egl_context_) {
        SkDebugf("Could not create context!\n");
        return nullptr;
    }
    egl_surface_ = eglCreateWindowSurface(egl_display_, surfaceConfig, hWND_, nullptr);
    if (EGL_NO_SURFACE == egl_surface_) {
        SkDebugf("Could not create surface!\n");
        return nullptr;
    }
    if (!eglMakeCurrent(egl_display_, egl_surface_, egl_surface_, egl_context_)) {
        SkDebugf("Could not make contxt current!\n");
        return nullptr;
    }
    sk_sp<const GrGLInterface> interface(GrGLMakeAssembledInterface(
            nullptr,
            [](void* ctx, const char name[]) -> GrGLFuncPtr {
                return eglGetProcAddress(name); }));
    if (interface) {
        interface->fFunctions.fClearStencil(0);
        interface->fFunctions.fClearColor(0, 0, 0, 0);
        interface->fFunctions.fStencilMask(0xffffffff);
        interface->fFunctions.fClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // use DescribePixelFormat to get the stencil depth.
        int pixelFormat = GetPixelFormat(dc);
        PIXELFORMATDESCRIPTOR pfd;
        DescribePixelFormat(dc, pixelFormat, sizeof(pfd), &pfd);
        stencil_bits_ = pfd.cStencilBits;

        RECT rect;
        GetClientRect(hWND_, &rect);
        width_ = rect.right - rect.left;
        height_ = rect.bottom - rect.top;
        interface->fFunctions.fViewport(0, 0, width_, height_);
    }
    return interface;
}

sk_sp<SkSurface> AngleGLWindowContext::CreateRenderSurface()
{
    return nullptr;
}

void AngleGLWindowContext::OnDestroyContext() {

}

void AngleGLWindowContext::OnSwapBuffers() {
    if (!eglSwapBuffers(egl_display_, egl_surface_)) {
        SkDebugf("Could not complete eglSwapBuffers.\n");
    }
}

} // namespace wtf
