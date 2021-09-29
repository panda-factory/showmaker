//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef STRUGGLE_TANSFORM_LAYER_H
#define STRUGGLE_TANSFORM_LAYER_H

#include "render/layer/container_layer.h"

class TransformLayer : public ContainerLayer {
public:
    void Paint(SkCanvas* canvas) const override;

    void AddToScene(SceneBuilder *,Position2D) override;

    TransformLayer(const SkMatrix& transform);

private:
    SkMatrix transform_;
};


#endif //STRUGGLE_TANSFORM_LAYER_H
