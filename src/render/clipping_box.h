//
// Created by guozhenxiong on 2021-08-07.
//

#ifndef STRUGGLE_CLIPPING_BOX_H
#define STRUGGLE_CLIPPING_BOX_H

#include "graphics/position.h"
#include "graphics/size.h"

namespace strg {
struct ClippingBox {
    Position top_left;
    Size size;
};
} // namespace strg

#endif //STRUGGLE_CLIPPING_BOX_H
