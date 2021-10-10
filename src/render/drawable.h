//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef STRUGGLE_DRAWABLE_H
#define STRUGGLE_DRAWABLE_H

#include "graphics/position.h"

#include <third_party/skia/include/core/SkCanvas.h>
namespace strg {
class Drawable {
public:
    virtual void Draw(SkCanvas *, const Position &position) = 0;
};
} // namespace strg

#endif //STRUGGLE_DRAWABLE_H
