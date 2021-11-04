//
// Created by guozhenxiong on 2021-11-04.
//

#include "rrect.h"

namespace sm {
const RRect RRect::ZERO = RRect();

/// | static |
RRect RRect::FromRectAndRadius(Rect rect, Radius radius)
{
    return RRect(rect.left, rect.top, rect.right, rect.bottom,
                 radius.x, radius.y,
                 radius.x, radius.y,
                 radius.x, radius.y,
                 radius.x, radius.y);
}

/// Rect::operator!=
bool operator != (const RRect& rrect1, const RRect& rrect2)
{
    if (rrect1.bottom != rrect2.bottom ||
        rrect1.right != rrect2.right ||
        rrect1.left != rrect2.left ||
        rrect1.top != rrect2.top ||
        rrect1.blRadiusY != rrect2.blRadiusY ||
        rrect1.blRadiusX != rrect2.blRadiusX ||
        rrect1.brRadiusY != rrect2.brRadiusY ||
        rrect1.brRadiusX != rrect2.brRadiusX ||
        rrect1.trRadiusY != rrect2.trRadiusY ||
        rrect1.trRadiusX != rrect2.trRadiusX ||
        rrect1.tlRadiusY != rrect2.tlRadiusY ||
        rrect1.tlRadiusX != rrect2.tlRadiusX) {
        return true;
    } else {
        return false;
    }
}
} // namespace sm