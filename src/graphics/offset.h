//
// Created by guozhenxiong on 2021-10-30.
//

#ifndef SHOWMAKER_OFFSET_H
#define SHOWMAKER_OFFSET_H

namespace sm {
struct Offset {
    Offset(float x, float y);

    float x;
    float y;

    static const Offset ZERO;
};


} // namespace sm

#endif //SHOWMAKER_OFFSET_H
