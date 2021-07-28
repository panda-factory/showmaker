//
// Created by guozhenxiong on 2021-07-22.
//

#include "gl_window_context.h"

#include "third-party/skia/include/core/SkCanvas.h"
#include "third-party/skia/include/gpu/GrBackendSurface.h"
#include "third-party/skia/include/gpu/GrDirectContext.h"

namespace wtf {
#define GPU_GL_RGBA8 0x8058
#define GPU_GL_RGBA4 0x8056
#define GPU_GL_RGB565 0x8D62
static SkColorType FirstSupportedColorType(GrDirectContext* context,
                                           GrGLenum* format) {
#define RETURN_IF_RENDERABLE(x, y)                 \
  if (context->colorTypeSupportedAsSurface((x))) { \
    *format = (y);                                 \
    return (x);                                    \
  }
    RETURN_IF_RENDERABLE(kRGBA_8888_SkColorType, GPU_GL_RGBA8);
    RETURN_IF_RENDERABLE(kARGB_4444_SkColorType, GPU_GL_RGBA4);
    RETURN_IF_RENDERABLE(kRGB_565_SkColorType, GPU_GL_RGB565);
    return kUnknown_SkColorType;
}

GLWindowContext::GLWindowContext(const DisplayParams& params)
        : WindowContext(params)
        , backend_context_(nullptr)
        , surface_(nullptr) {
}

sk_sp<SkSurface> GLWindowContext::GetBackbufferSurface() {
    if (nullptr == surface_) {
        if (context_) {
            GrGLenum format;
            const SkColorType color_type = FirstSupportedColorType(context_.get(), &format);

            GrGLint fbo = 0;
            GrGLFramebufferInfo framebuffer_info = {};
            framebuffer_info.fFBOID = static_cast<GrGLuint>(fbo);
            framebuffer_info.fFormat = format;

            GrBackendRenderTarget render_target(width_,     // width
                                                height_,    // height
                                                0,                // sample count
                                                0,                // stencil bits (TODO)
                                                framebuffer_info  // framebuffer info
            );

            sk_sp<SkColorSpace> colorspace = SkColorSpace::MakeSRGB();
            SkSurfaceProps surface_props(0, kUnknown_SkPixelGeometry);

            return SkSurface::MakeFromBackendRenderTarget(
                    context_.get(),                                       // Gr context
                    render_target,                                 // render target
                    GrSurfaceOrigin::kBottomLeft_GrSurfaceOrigin,  // origin
                    color_type,                                    // color type
                    colorspace,                                    // colorspace
                    &surface_props                                 // surface properties
            );
        }
    }

    return surface_;
}

void GLWindowContext::InitializeContext() {
    SkASSERT(!context_);

    this->OnInitializeContext();

    backend_context_ = this->CreateGLInterface();

    context_ = GrDirectContext::MakeGL(backend_context_, display_params_.fGrContextOptions);
    if (!context_ && display_params_.fMSAASampleCount > 1) {
        display_params_.fMSAASampleCount /= 2;
        this->InitializeContext();
        return;
    }
}

bool GLWindowContext::IsValid()
{
    return true;
}

void GLWindowContext::SwapBuffers() {
    this->OnSwapBuffers();
}

} // namespace wtf