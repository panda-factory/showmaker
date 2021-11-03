//
// Created by guozhenxiong on 2021-10-30.
//

#include "offset.h"

namespace sm {

const Offset Offset::ZERO = {0.0f, 0.0f};

/// Offset::operator!=
bool operator != (const Offset& offset1, const Offset& offset2)
{
    if (offset1.x != offset2.x ||
        offset1.y != offset2.y) {
        return true;
    } else {
        return false;
    }
}
} // namespace sm