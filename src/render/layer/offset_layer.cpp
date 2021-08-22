//
// Created by guozhenxiong on 2021-08-22.
//

#include "offset_layer.h"

#include "render/compositing/scene_builder.h"

OffsetLayer::OffsetLayer(const SkPoint &offset)
        : offset_(offset)
{
}

void OffsetLayer::Paint(SkCanvas *canvas) const
{
    SkAutoCanvasRestore save(canvas, true);
    canvas->translate(offset_.x(), offset_.y());

    PaintChildren(canvas);
}

void OffsetLayer::AddToScene(SceneBuilder* builder, Position2D offset)
{
    builder->PushOffset(0, 0);
    AddChildrenToScene(builder, offset);
    builder->Pop();
}