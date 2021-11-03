//
// Created by guozhenxiong on 2021-10-30.
//

#ifndef SHOWMAKER_OFFSET_H
#define SHOWMAKER_OFFSET_H

namespace sm {
struct Offset {
    friend bool operator!= (const Offset& offset1, const Offset& offset2);

    Offset(float x, float y)
    : x(x), y(y) {}

    float x;
    float y;

    static const Offset ZERO;
};


} // namespace sm

#endif //SHOWMAKER_OFFSET_H
