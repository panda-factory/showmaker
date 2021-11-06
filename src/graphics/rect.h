//
// Created by guozhenxiong on 2021-11-01.
//

#ifndef SHOWMAKER_RECT_H
#define SHOWMAKER_RECT_H

namespace sm {
struct Rect {

    static Rect FromLTRB(float left, float top, float right, float bottom);
    static Rect FromLTWH(float left, float top, float width, float height);

    bool HasNaN() const;

    bool IsValid() const;

    friend bool operator!= (const Rect& rect1, const Rect& rect2);

    /// The offset of the left edge of this rectangle from the x axis.
    float left;

    /// The offset of the top edge of this rectangle from the y axis.
    float top;

    /// The offset of the right edge of this rectangle from the x axis.
    float right;

    /// The offset of the bottom edge of this rectangle from the y axis.
    float bottom;

    /// const
    static const Rect ZERO;

    static const Rect LARGEST;
};
} // namespace sm

#endif //SHOWMAKER_RECT_H
