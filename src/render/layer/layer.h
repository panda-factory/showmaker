//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef STRUGGLE_LAYER_H
#define STRUGGLE_LAYER_H

#include "graphics/position.h"

#include <third_party/skia/include/core/SkPicture.h>
#include <third_party/skia/include/core/SkCanvas.h>

namespace strg {
class SceneBuilder;

class Layer {
public:
    virtual void Paint(SkCanvas *canvas) const = 0;

    virtual void AddToScene(SceneBuilder *builder, Position offset = {0, 0}) = 0;

    Layer();

    virtual ~Layer();
};
} // namespace strg

#endif //STRUGGLE_LAYER_H
