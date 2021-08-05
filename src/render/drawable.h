//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef XXX_DRAWABLE_H
#define XXX_DRAWABLE_H

#include <third-party/skia/include/core/SkCanvas.h>

class Drawable {
public:
    virtual void Draw(SkCanvas*) const = 0;
};


#endif //XXX_DRAWABLE_H
