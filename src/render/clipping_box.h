//
// Created by guozhenxiong on 2021-08-07.
//

#ifndef XXX_CLIPPING_BOX_H
#define XXX_CLIPPING_BOX_H

#include "render/position2d.h"
#include "render/size.h"

struct ClippingBox {
    Position2D top_left;
    Size2D size;
};


#endif //XXX_CLIPPING_BOX_H
