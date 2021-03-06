//
// Created by guozhenxiong on 2021-07-22.
//

#ifndef SHOWMAKER_WINDOW_CONTEXT_H
#define SHOWMAKER_WINDOW_CONTEXT_H

#include "display_params.h"
#include "include/core/SkSurfaceProps.h"
#include "include/gpu/GrTypes.h"

#include "include/core/SkRefCnt.h"

class GrDirectContext;
class SkSurface;

namespace sm {
class WindowContext {
public:
    virtual sk_sp<SkSurface> GetBackbufferSurface() = 0;

    virtual bool IsValid() = 0;

    virtual int MakeCurrent() = 0;

    virtual void SwapBuffers() = 0;

    const DisplayParams& GetDisplayParams() { return display_params_; }

    inline int width() const { return width_; }

    inline int height() const { return height_; }

    WindowContext(const DisplayParams&);

    virtual ~WindowContext();

protected:
    DisplayParams display_params_;
    sk_sp<GrDirectContext> context_;
    int width_;
    int height_;
    int sample_count_;
    int stencil_bits_;
};
} // namespace sm

#endif //SHOWMAKER_WINDOW_CONTEXT_H
