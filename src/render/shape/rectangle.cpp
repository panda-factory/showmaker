//
// Created by guozhenxiong on 2021-08-05.
//

#include "rectangle.h"

#include "render/canvas_scope.h"

#include <third_party/skia/include/core/SkRRect.h>

namespace strg {
Rectangle::Rectangle(const Size &size)
        : size_(size)
{}

void Rectangle::Draw(SkCanvas *canvas, const Position &position)
{
    SkAutoCanvasRestore acr(canvas, true);

    SkPaint selection = SkPaint({0.729f, 0.827f, 0.988f, 1});

    const auto fill_rect = SkRect::MakeXYWH(position.x, position.y, size_.width, size_.height);

    canvas->drawRect(fill_rect, selection);

}
} // namespace strg