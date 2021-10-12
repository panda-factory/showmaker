//
// Created by guozhenxiong on 2021-10-08.
//

#include "rasterizer.h"
#include "window_context.h"
#include "render/compositing/scene.h"

#include <third_party/skia/include/core/SkSurface.h>

namespace sm {

Rasterizer::Rasterizer(WindowContext* window_context)
  : window_context_(window_context)
{}

void Rasterizer::Draw(std::unique_ptr<sm::Scene> scene)
{
    window_context_->MakeCurrent();

    sk_sp<SkSurface> backbuffer = window_context_->GetBackbufferSurface();
    if (backbuffer == nullptr) {
        printf("no backbuffer!?\n");
        // TODO: try recreating testcontext
        return;
    }
    scene->root_layer()->Paint(backbuffer.get()->getCanvas());

    backbuffer->flushAndSubmit();

    window_context_->SwapBuffers();
}
} // namespace sm