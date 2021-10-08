//
// Created by guozhenxiong on 2021-08-22.
//

#ifndef STRUGGLE_OFFSET_LAYER_H
#define STRUGGLE_OFFSET_LAYER_H

#include "render/layer/container_layer.h"

namespace strg {
class OffsetLayer : public ContainerLayer {
public:
    void Paint(SkCanvas *canvas) const override;

    void AddToScene(SceneBuilder *, Position2D) override;

    OffsetLayer(const float x, const float y);

private:
    SkPoint offset_;
};
} // namespace strg

#endif //STRUGGLE_OFFSET_LAYER_H
