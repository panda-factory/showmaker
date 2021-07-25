//
// Created by guozhenxiong on 2021-07-22.
//

#ifndef XXX_GL_WINDOW_CONTEXT_H
#define XXX_GL_WINDOW_CONTEXT_H

#include "window_context.h"

#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkRefCnt.h"
#include "include/core/SkSurface.h"

namespace wtf {
class GLWindowContext : public WindowContext {
public:
    sk_sp<SkSurface> GetBackbufferSurface() override;

    void SwapBuffers() override;

    bool IsValid() override;

protected:
    virtual sk_sp<SkSurface> CreateRenderSurface() = 0;

    void InitializeContext();

    virtual sk_sp<const GrGLInterface> OnInitializeContext() = 0;

    void DestroyContext();
    virtual void OnDestroyContext() = 0;

    virtual void OnSwapBuffers() = 0;

    GLWindowContext(const DisplayParams&);

    sk_sp<const GrGLInterface> backend_context_;
    sk_sp<SkSurface>           surface_;
};
} // namespace wtf

#endif //XXX_GL_WINDOW_CONTEXT_H
