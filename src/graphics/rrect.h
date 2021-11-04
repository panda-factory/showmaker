//
// Created by guozhenxiong on 2021-11-04.
//

#ifndef SHOWMAKER_RRECT_H
#define SHOWMAKER_RRECT_H

#include "rect.h"
#include "radius.h"

namespace sm {
struct RRect {
    static RRect FromRectAndRadius(Rect rect, Radius radius);

    friend bool operator!= (const RRect& rrect1, const RRect& rrect2);

    RRect(float left = 0.0f, float top = 0.0f, float right = 0.0f, float bottom = 0.0f,
          float tlRadiusX = 0.0f, float tlRadiusY = 0.0f,
          float trRadiusX = 0.0f, float trRadiusY = 0.0f,
          float brRadiusX = 0.0f, float brRadiusY = 0.0f,
          float blRadiusX = 0.0f, float blRadiusY = 0.0f)
          : left(left), top(top), right(right), bottom(bottom),
          tlRadiusX(tlRadiusX), tlRadiusY(tlRadiusY),
          trRadiusX(trRadiusX), trRadiusY(trRadiusY),
          brRadiusX(brRadiusX), brRadiusY(brRadiusY),
          blRadiusX(blRadiusX), blRadiusY(blRadiusY)
          {}

    /// The offset of the left edge of this rectangle from the x axis.
    float left;

    /// The offset of the top edge of this rectangle from the y axis.
    float top;

    /// The offset of the right edge of this rectangle from the x axis.
    float right;

    /// The offset of the bottom edge of this rectangle from the y axis.
    float bottom;

    /// The top-left horizontal radius.
    float tlRadiusX;

    /// The top-left vertical radius.
    float tlRadiusY;

    /// The top-right horizontal radius.
    float trRadiusX;

    /// The top-right vertical radius.
    float trRadiusY;

    /// The bottom-right horizontal radius.
    float brRadiusX;

    /// The bottom-right vertical radius.
    float brRadiusY;

    /// The bottom-left horizontal radius.
    float blRadiusX;

    /// The bottom-left vertical radius.
    float blRadiusY;

    static const RRect ZERO;
};
} // namespace sm

#endif //SHOWMAKER_RRECT_H
