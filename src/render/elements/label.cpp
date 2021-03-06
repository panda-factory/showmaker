//
// Created by guozhenxiong on 2021-08-04.
//

#include "label.h"

#include <memory>

#include "render/shape/rectangle.h"

#include <third_party/skia/include/core/SkGraphics.h>

namespace sm {
Label::Label(const std::string &text)
        : text_(text)
{

}

/// | RenderObject |
void Label::Paint(const PaintContext* context, Position offset)
{
    Paint(const_cast<PaintContext*>(context));
}

void Label::Paint(PaintContext *context)
{
    auto canvas = context->canvas();
    auto rect = std::make_unique<sm::Rectangle>(text_.MeasureSize());

    Element::Draw(canvas, rect.get(), {0, 0});
    Element::Draw(canvas, &text_, {0, 0});
    canvas->clipRect({0, 0, 10, 10});
    canvas->save();
}

Size Label::MeasureSize()
{
    const auto text_size = text_.MeasureSize();
    return text_size;
}
} // namespace sm