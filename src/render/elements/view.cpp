//
// Created by guozhenxiong on 2021-08-21.
//

#include "view.h"

#include "render/layer/transform_layer.h"

void View::Paint(PaintContext *context)
{
    auto canvas = context->canvas();

    canvas->clear(SK_ColorWHITE);

    canvas->restore();
}

void View::PerformLayout()
{
    children_[0]->PerformLayout();
}

Size2D View::MeasureSize()
{
    return {};
}