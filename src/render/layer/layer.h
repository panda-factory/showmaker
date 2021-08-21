//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef XXX_LAYER_H
#define XXX_LAYER_H

#include "render/position2d.h"

#include <third-party/skia/include/core/SkPicture.h>
#include <third-party/skia/include/core/SkCanvas.h>

class SceneBuilder;

class Layer {
public:
    virtual void Paint(SkCanvas* canvas) const = 0;

    virtual void AddToScene(SceneBuilder* builder, Position2D offset = {0, 0}) = 0;
    Layer();
    virtual ~Layer();
};


#endif //XXX_LAYER_H
