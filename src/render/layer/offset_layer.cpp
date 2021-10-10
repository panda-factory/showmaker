//
// Created by guozhenxiong on 2021-08-22.
//

#include "offset_layer.h"

#include "render/compositing/scene_builder.h"

namespace strg {
OffsetLayer::OffsetLayer(const float x, const float y)
        : offset_(SkPoint({x, y}))
{
}

void OffsetLayer::Paint(SkCanvas *canvas) const
{
    SkAutoCanvasRestore save(canvas, true);
    canvas->translate(offset_.x(), offset_.y());

    PaintChildren(canvas);
}

void OffsetLayer::AddToScene(SceneBuilder *builder, Position offset)
{
    builder->PushOffset(offset_.x(), offset_.y());
    AddChildrenToScene(builder, offset);
    builder->Pop();
}
} // namespace strg