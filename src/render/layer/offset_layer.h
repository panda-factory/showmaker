//
// Created by guozhenxiong on 2021-08-22.
//

#ifndef XXX_OFFSET_LAYER_H
#define XXX_OFFSET_LAYER_H

#include "render/layer/container_layer.h"

class OffsetLayer : public ContainerLayer {
public:
    void Paint(SkCanvas* canvas) const override;

    void AddToScene(SceneBuilder *,Position2D) override;

    OffsetLayer(const float x, const float y);

private:
    SkPoint offset_;
};


#endif //XXX_OFFSET_LAYER_H
