//
// Created by guozhenxiong on 2021-11-04.
//

#ifndef SHOWMAKER_RADIUS_H
#define SHOWMAKER_RADIUS_H

namespace sm {
struct Radius {
    Radius(float radius) :
    x(radius), y(radius) {}

    Radius(float radius_x, float radius_y) :
            x(radius_x), y(radius_y) {}

    /// The radius value on the horizontal axis.
    float x;

    /// The radius value on the vertical axis.
    float y;

    static const Radius ZERO;
};
} // namespace sm

#endif //SHOWMAKER_RADIUS_H
