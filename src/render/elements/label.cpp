//
// Created by guozhenxiong on 2021-08-04.
//

#include "label.h"

#include <memory>

#include "render/shape/rectangle.h"
#include "render/painting/picture_recorder.h"
#include "render/layer/picture_layer.h"
#include "render/layer/transform_layer.h"
#include "render/painting/picture.h"

#include <third-party/skia/include/core/SkGraphics.h>

Label::Label(const std::string& text)
    :text_(text)
{

}

void Label::Paint(PaintContext *context)
{
    auto canvas = context->canvas();
    auto rect = std::make_unique<Rectangle>(text_.MeasureSize());

    Element::Draw(canvas, rect.get(), position_);
    Element::Draw(canvas, &text_, position_);

    canvas->restore();
}

Size2D Label::MeasureSize()
{
    const auto text_size = text_.MeasureSize();
    return text_size;
}