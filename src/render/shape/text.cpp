//
// Created by guozhenxiong on 2021-08-05.
//

#include "text.h"

#include "include/core/SkFont.h"

#include <include/core/SkFontMetrics.h>

Text::Text(const std::string& text)
    : text_(text)
{}

void Text::Draw(SkCanvas* canvas, const Position2D& position)
{
    SkAutoCanvasRestore acr(canvas, true);
    SkPaint paint;

    // Draw a message with a nice black paint
    font_.setSubpixel(true);
    font_.setSize(size_);

    SkFontMetrics metrics;
    font_.getMetrics(&metrics);
    SkScalar offset = -metrics.fAscent;
    paint.setColor(SK_ColorBLACK);

    // Draw the text
    canvas->drawSimpleText(text_.c_str(),
                           text_.size(),
                           SkTextEncoding::kUTF8,
                           position.x,
                           position.y + offset,
                           font_, paint);
}

Size2D Text::MeasureSize()
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

    return {width, height};
}