//
// Created by guozhenxiong on 2021-10-25.
//

#include "editable_text.h"

#include "render/shape/rectangle.h"

namespace sm {
EditableText::EditableText(const std::string &text)
  : text_(text), blink_(false)
{
}

bool EditableText::HitTest(double x, double y)
{
    auto pos = text_.GetPosition(x, y);
    return false;
}

void EditableText::Paint(PaintContext *context)
{
    auto canvas = context->canvas();
    auto rect = std::make_unique<sm::Rectangle>(text_.MeasureSize());

    Element::Draw(canvas, rect.get(), {0, 0});
    Element::Draw(canvas, &text_, {0, 0});
    auto cursor_rect = text_.GetLocation();
    //auto cursor = std::make_unique<sm::Rectangle>(Size({cursor_rect.width(), cursor_rect.height()}));
    //Element::Draw(canvas, cursor.get(), {cursor_rect.x(), cursor_rect.y()});
    canvas->drawRect(cursor_rect, SkPaint({1, 0, 0, 1.0f}));

    canvas->save();
}

Size EditableText::MeasureSize()
{
    const auto text_size = text_.MeasureSize();
    return text_size;
}
}