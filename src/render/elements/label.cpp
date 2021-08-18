//
// Created by guozhenxiong on 2021-08-04.
//

#include "label.h"

#include "include/core/SkGraphics.h"

#include "render/shape/rectangle.h"
#include "render/shape/text.h"

Label::Label(const std::string& text)
    :text_(text)
{

}

void Label::Draw(SkCanvas* canvas)
{

    auto rect = std::make_unique<Rectangle>(text_.MeasureSize());

    Element::Draw(canvas, rect.get(), position_);
    Element::Draw(canvas, &text_, position_);

    canvas->restore();

}

Size2D Label::MeasureSize(SkCanvas* canvas)
{
    const auto text_size = text_.MeasureSize();
    return text_size;
}