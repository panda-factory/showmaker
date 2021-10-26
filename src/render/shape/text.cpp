//
// Created by guozhenxiong on 2021-08-05.
//

#include "text.h"
#include "text/paragraph_builder.h"

#include "include/core/SkFont.h"

#include <include/core/SkFontMetrics.h>
#include <third_party/ConvertUTF/UTF8.h>

namespace sm {
Text::Text() = default;

Text::Text(const std::string &text)
        : text_(text)
{
    auto builder = std::make_unique<ParagraphBuilder>(size_, size_);
    std::u16string out;
    UTF::UTF8ToUTF16(text, out);
    //builder->PushTextStyle();
    builder->AddText(out);
    paragraph_ = builder->Build();
}

SkRect Text::GetLocation()
{
    auto locations = paragraph_->GetRectsForRange(text_.position() - 1, text_.position());
    return locations.begin()->rect;
}

size_t Text::GetPosition(double x, double y)
{
    auto pos = paragraph_->GetPositionForOffset(x, y);
    text_.position() = pos.offset;
    return text_.position();
}

void Text::Draw(SkCanvas *canvas, const Position &position)
{
    paragraph_->Paint(canvas, position.x, position.y);
}

Size Text::MeasureSize()
{
    auto builder = std::make_unique<ParagraphBuilder>(size_, size_);
    builder->AddText(text_.text());
    paragraph_ = builder->Build();
    paragraph_->Layout(120);
    return {(SkScalar)paragraph_->width(), (SkScalar)paragraph_->height()};
}
} // namespace sm