//
// Created by guozhenxiong on 2021-10-25.
//

#include "editable_text.h"

#include "render/shape/rectangle.h"
#include "window.h"
namespace sm {
EditableText::EditableText(const std::string &text)
  : text_(text), blink_(false)
{
    std::function<void (const std::u16string& u16)> handle = [this] (const std::u16string& u16) {
        this->OnChar(u16);
    };
    Window::RegisterOnChar(handle);
    MarkNeedsPaint();
}

/// | TextInputClient |
void EditableText::OnChar(const std::u16string& c)
{
    text_.text().AddText(c);
}

bool EditableText::HitTest(double x, double y)
{
    auto pos = text_.GetPosition(x, y);
    return false;
}

/// | RenderObject |
void EditableText::Paint(const PaintContext* context, Position offset)
{
    Paint(const_cast<PaintContext*>(context));
}

void EditableText::Paint(PaintContext *context)
{
    auto canvas = context->canvas();
    auto rect = std::make_unique<sm::Rectangle>(text_.MeasureSize());

    Element::Draw(canvas, rect.get(), {0, 0});
    Element::Draw(canvas, &text_, {0, 0});
    auto cursor_rect = text_.GetLocation();
    SkPaint cursor_paint({1, 0, 0, blink_ ? 1.0f : 0.0f});
    blink_ = !blink_;
    canvas->drawRect(cursor_rect, cursor_paint);

    canvas->save();
}

Size EditableText::MeasureSize()
{
    const auto text_size = text_.MeasureSize();
    MarkNeedsPaint();
    return text_size;
}
}