//
// Created by guozhenxiong on 2021-10-27.
//

#include "render_object.h"
#include "render/pipeline/render_pipeline.h"

namespace sm {
RenderObject::RenderObject()
  : layer_(nullptr), needs_paint_(false)
{}
void RenderObject::MarkNeedsPaint()
{
    if (needs_paint_ == true) {
        return;
    }
    needs_paint_ = true;
    RenderPipeline::AddNodeNeedingPaint(this);
}

void RenderObject::PaintWithContext(const PaintContext* context, Position offset)
{
    needs_paint_ = false;
    Paint(context, offset);
}
} // namespace sm