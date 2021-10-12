//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef SHOWMAKER_DRAWABLE_H
#define SHOWMAKER_DRAWABLE_H

#include "graphics/position.h"

#include <third_party/skia/include/core/SkCanvas.h>
namespace sm {
class Drawable {
public:
    virtual void Draw(SkCanvas *, const Position &position) = 0;
};
} // namespace sm

#endif //SHOWMAKER_DRAWABLE_H
