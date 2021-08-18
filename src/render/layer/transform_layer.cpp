//
// Created by guozhenxiong on 2021-08-18.
//

#include "transform_layer.h"

TransformLayer::TransformLayer(const SkMatrix &transform)
        : transform_(transform)
{
    if (!transform_.isFinite()) {
        transform_.setIdentity();
    }
}

void TransformLayer::Paint(SkCanvas *canvas) const
{
    SkAutoCanvasRestore save(canvas, true);
    canvas->concat(transform_);

    PaintChildren(canvas);
}