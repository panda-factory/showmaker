//
// Created by guozhenxiong on 2021-08-07.
//

#ifndef SHOWMAKER_CLIPPING_BOX_H
#define SHOWMAKER_CLIPPING_BOX_H

#include "graphics/position.h"
#include "graphics/size.h"

namespace sm {
struct ClippingBox {
    Position top_left;
    Size size;
};
} // namespace sm

#endif //SHOWMAKER_CLIPPING_BOX_H
