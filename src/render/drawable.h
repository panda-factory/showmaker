//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef STRUGGLE_DRAWABLE_H
#define STRUGGLE_DRAWABLE_H

#include "render/position2d.h"

#include <third_party/skia/include/core/SkCanvas.h>

class Drawable {
public:
    virtual void Draw(SkCanvas*, const Position2D& position) = 0;
};


#endif //STRUGGLE_DRAWABLE_H
