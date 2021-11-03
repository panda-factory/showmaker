//
// Created by guozhenxiong on 2021-08-22.
//

#include "offset_layer.h"

#include "render/compositing/scene_builder.h"

namespace sm {

/// | Layer |
void OffsetLayer::Paint(SkCanvas *canvas) const
{
    SkAutoCanvasRestore save(canvas, true);
    canvas->translate(offset_.x, offset_.y);

    PaintChildren(canvas);
}

/// | Layer |
void OffsetLayer::AddToScene(SceneBuilder *builder, Position offset)
{
    builder->PushOffset(offset_.x, offset_.y);
    AddChildrenToScene(builder, offset);
    builder->Pop();
}

void OffsetLayer::SetOffset(const Offset& value)
{
    if (value != offset_) {
        MarkNeedsAddToScene();
    }
    offset_ = value;
}

} // namespace sm