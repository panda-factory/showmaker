//
// Created by guozhenxiong on 2021-08-05.
//

#include "rectangle.h"

#include <third-party/skia/include/core/SkRRect.h>

void Rectangle::Draw(SkCanvas* canvas) const
{
    SkPaint selection = SkPaint({0.729f, 0.827f, 0.988f, 1});

    const auto fill_rect = SkRect::MakeXYWH(0, 0, 100, 100);

    canvas->drawRect(fill_rect, selection);

    canvas->save();
}