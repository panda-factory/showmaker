//
// Created by guozhenxiong on 2021-11-01.
//

#include "rect.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {
constexpr double kGIANT_SCALAR = 1.0E+9;

const Rect Rect::ZERO = Rect::FromLTRB(0.0f, 0.0f, 0.0f, 0.0f);

const Rect Rect::LARGEST = Rect::FromLTRB(-kGIANT_SCALAR, -kGIANT_SCALAR, kGIANT_SCALAR, kGIANT_SCALAR);

/// | static |
Rect Rect::FromLTRB(float left, float top, float right, float bottom)
{
    return {.left = left,
            .top = top,
            .right = right,
            .bottom = bottom};
}

/// Rect::operator!=
bool operator != (const Rect& rect1, const Rect& rect2)
{
    if (rect1.bottom != rect2.bottom ||
        rect1.right != rect2.right ||
        rect1.left != rect2.left ||
        rect1.top != rect2.top) {
        return true;
    } else {
        return false;
    }
}
} // namespace sm