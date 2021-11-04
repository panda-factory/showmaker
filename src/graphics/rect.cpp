//
// Created by guozhenxiong on 2021-11-01.
//

#include "rect.h"

#include <limits>

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


bool Rect::HasNaN() const
{
    return std::numeric_limits<decltype(left)>::quiet_NaN() == left ||
           std::numeric_limits<decltype(top)>::quiet_NaN() == top ||
           std::numeric_limits<decltype(right)>::quiet_NaN() == right ||
           std::numeric_limits<decltype(bottom)>::quiet_NaN() == bottom;
}

bool Rect::IsValid() const
{
    FML_CHECK(!HasNaN()) << "Rect argument contained a NaN value.";
    return true;
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