//
// Created by guozhenxiong on 2021-07-23.
//

#include "angle_gl_window_context.h"
#include <iostream>
#include "include/gpu/gl/GrGLAssembleInterface.h"
#include "third_party/skia/include/core/SkCanvas.h"
#include "third_party/skia/include/gpu/GrBackendSurface.h"
#include "third_party/skia/include/gpu/GrDirectContext.h"

namespace sm {
namespace {
static void LogEglError(std::string message)
{
    EGLint error = eglGetError();
    std::cerr << "EGL: " << message << std::endl;
    std::cerr << "EGL: eglGetError returned " << error << std::endl;
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

AngleGLWindowContext::AngleGLWindowContext(HWND hWnd, const DisplayParams &params)
        : GLWindowContext(params), hWND_(hWnd)
{
    this->InitializeContext();
}

bool AngleGLWindowContext::InitializeEGL(
        PFNEGLGETPLATFORMDISPLAYEXTPROC egl_get_platform_display_EXT,
        const EGLint *config)
{
    egl_display_ = egl_get_platform_display_EXT(EGL_PLATFORM_ANGLE_ANGLE,
                                                EGL_DEFAULT_DISPLAY, config);

    if (egl_display_ == EGL_NO_DISPLAY) {
        LogEglError("Failed to get a compatible EGLdisplay");
        return false;
    }

    if (eglInitialize(egl_display_, nullptr, nullptr) == EGL_FALSE) {
        LogEglError("Failed to initialize EGL via ANGLE");
        return false;
    }

    return true;
}

EGLDisplay AngleGLWindowContext::InitializeEGLDisplay(HDC hdc) {
    PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT;
    eglGetPlatformDisplayEXT =
            (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");

    // We expect ANGLE to support this extension
    if (!eglGetPlatformDisplayEXT) {
        return EGL_NO_DISPLAY;
    }

    const EGLint d3d11_display_attributes[] = {
            EGL_PLATFORM_ANGLE_TYPE_ANGLE,
            EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,

            // EGL_PLATFORM_ANGLE_ENABLE_AUTOMATIC_TRIM_ANGLE is an option that will
            // enable ANGLE to automatically call the IDXGIDevice3::Trim method on
            // behalf of the application when it gets suspended.
            EGL_PLATFORM_ANGLE_ENABLE_AUTOMATIC_TRIM_ANGLE,
            EGL_TRUE,
            EGL_NONE,
    };
    const EGLint d3d11_fl_9_3_display_attributes[] = {
            EGL_PLATFORM_ANGLE_TYPE_ANGLE,
            EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,
            EGL_PLATFORM_ANGLE_MAX_VERSION_MAJOR_ANGLE,
            9,
            EGL_PLATFORM_ANGLE_MAX_VERSION_MINOR_ANGLE,
            3,
            EGL_PLATFORM_ANGLE_ENABLE_AUTOMATIC_TRIM_ANGLE,
            EGL_TRUE,
            EGL_NONE,
    };
    const EGLint d3d11_warp_display_attributes[] = {
            EGL_PLATFORM_ANGLE_TYPE_ANGLE,
            EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,
            EGL_PLATFORM_ANGLE_ENABLE_AUTOMATIC_TRIM_ANGLE,
            EGL_TRUE,
            EGL_NONE,
    };
    const EGLint d3d9_display_attributes[] = {
            EGL_PLATFORM_ANGLE_TYPE_ANGLE,
            EGL_PLATFORM_ANGLE_TYPE_D3D9_ANGLE,
            EGL_TRUE,
            EGL_NONE,
    };
    std::vector<const EGLint*> display_attributes_configs = {
            d3d11_display_attributes,
            d3d11_fl_9_3_display_attributes,
            d3d11_warp_display_attributes,
            d3d9_display_attributes,
    };

    for (auto config : display_attributes_configs) {
        if (InitializeEGL(eglGetPlatformDisplayEXT, config)) {
            break;
        }
    }
}

sk_sp<const GrGLInterface> AngleGLWindowContext::CreateGLInterface()
{
    HDC dc = GetDC(hWND_);
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

void AngleGLWindowContext::OnInitializeContext()
{
    HDC dc = GetDC(hWND_);
    InitializeEGLDisplay(dc);
    if (EGL_NO_DISPLAY == egl_display_) {
        return;
    }

    EGLint majorVersion;
    EGLint minorVersion;
    if (!eglInitialize(egl_display_, &majorVersion, &minorVersion)) {
        SkDebugf("Could not initialize display!\n");
        return;
    }
    sample_count_ = this->GetDisplayParams().fMSAASampleCount;
    const int sampleBuffers = sample_count_ > 1 ? 1 : 0;
    const int eglSampleCnt = sample_count_ > 1 ? sample_count_ : 0;

    const EGLint config_attributes[] = {EGL_RED_SIZE,   8, EGL_GREEN_SIZE,   8,
                                        EGL_BLUE_SIZE,  8, EGL_ALPHA_SIZE,   8,
                                        EGL_DEPTH_SIZE, 8, EGL_STENCIL_SIZE, 8,
                                        EGL_NONE};
    EGLint numConfigs;
    if (!eglChooseConfig(egl_display_, config_attributes, &egl_config_, 1, &numConfigs)) {
        SkDebugf("Could not create choose config!\n");
        return;
    }
    // We currently only support ES3.
    const EGLint context_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    egl_context_ = eglCreateContext(egl_display_, egl_config_, nullptr, context_attribs);
    if (EGL_NO_CONTEXT == egl_context_) {
        SkDebugf("Could not create context!\n");
        return;
    }

    CreateSurface();
    MakeCurrent();
}

int AngleGLWindowContext::MakeCurrent()
{
    if (!eglMakeCurrent(egl_display_, egl_surface_, egl_surface_, egl_context_)) {
        SkDebugf("Could not make contxt current!\n");
        return -1;
    }
    return 0;
}

int AngleGLWindowContext::CreateSurface()
{
    egl_surface_ = eglCreateWindowSurface(egl_display_, egl_config_, hWND_, nullptr);
    if (EGL_NO_SURFACE == egl_surface_) {
        SkDebugf("Could not create surface!\n");
        return -1;
    }
    return 0;
}

void AngleGLWindowContext::OnDestroyContext() {

}

void AngleGLWindowContext::OnSwapBuffers() {
    if (!eglSwapBuffers(egl_display_, egl_surface_)) {
        SkDebugf("Could not complete eglSwapBuffers.\n");
    }
}

} // namespace sm
