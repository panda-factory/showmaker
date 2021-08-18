//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef XXX_LAYER_H
#define XXX_LAYER_H

#include <third-party/skia/include/core/SkPicture.h>
#include <third-party/skia/include/core/SkCanvas.h>

class Layer {
public:
    virtual void Paint(SkCanvas* canvas) const = 0;

    Layer();
    virtual ~Layer();
};


#endif //XXX_LAYER_H
