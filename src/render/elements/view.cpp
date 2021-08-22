//
// Created by guozhenxiong on 2021-08-21.
//

#include "view.h"

#include "render/layer/transform_layer.h"

void View::Paint(PaintContext *context)
{
    auto canvas = context->canvas();

    canvas->clear(SK_ColorWHITE);

    for(std::size_t i = 0; i < children_.size(); ++i)
    {
        PaintChild(children_[i].get(), nullptr);
    }

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