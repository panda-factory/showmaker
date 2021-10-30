//
// Created by guozhenxiong on 2021-10-30.
//

#include "offset.h"

namespace sm {

const Offset Offset::ZERO = {0.0f, 0.0f};

Offset::Offset(float x, float y)
        : x(x), y(y)

{}
} // namespace sm