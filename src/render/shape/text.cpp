//
// Created by guozhenxiong on 2021-08-05.
//

#include "text.h"
#include "text/paragraph_builder.h"

#include "include/core/SkFont.h"

#include <include/core/SkFontMetrics.h>
#include <third_party/ConvertUTF/UTF8.h>

namespace strg {
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

void Text::Draw(SkCanvas *canvas, const Position &position)
{
    paragraph_->Paint(canvas, position.x, position.y);
}

Size Text::MeasureSize()
{
    SkPaint paint;
    font_.setSize(size_);

    SkFontMetrics metrics;
    font_.getMetrics(&metrics);

    SkRect bounds;
    const SkScalar width = font_.measureText(text_.c_str(),
                                             text_.size(),
                                             SkTextEncoding::kUTF8,
                                             &bounds,
                                             &paint);
    const SkScalar height = std::abs(metrics.fAscent - metrics.fDescent);
    paragraph_->Layout(width);
    return {width, height};
}
} // namespace strg