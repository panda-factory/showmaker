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
} // namespace sm