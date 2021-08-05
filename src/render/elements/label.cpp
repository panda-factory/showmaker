//
// Created by guozhenxiong on 2021-08-04.
//

#include "label.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkFont.h"
#include "include/core/SkGraphics.h"
#include "include/core/SkSurface.h"
#include "render/shape/rectangle.h"

void Label::Draw(SkSurface *surface) const
{
    auto canvas = surface->getCanvas();

    // Clear background
    canvas->clear(SK_ColorWHITE);

    Rectangle rectangle;
    rectangle.Draw(canvas);

    SkPaint paint;

    // Draw a message with a nice black paint
    SkFont font;
    font.setSubpixel(true);
    font.setSize(20);
    paint.setColor(SK_ColorBLACK);

    canvas->save();

    static const char message[] = "Hello World";
    // Draw the text
    canvas->translate(position_.x, position_.y);
    canvas->drawSimpleText(message, strlen(message), SkTextEncoding::kUTF8, 0, 0, font, paint);

    canvas->restore();

}