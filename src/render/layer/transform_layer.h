//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef SHOWMAKER_TANSFORM_LAYER_H
#define SHOWMAKER_TANSFORM_LAYER_H

#include "render/layer/container_layer.h"

namespace sm {
class TransformLayer : public ContainerLayer {
public:
    void Paint(SkCanvas *canvas) const override;

    void AddToScene(SceneBuilder *, Position) override;

    TransformLayer(const SkMatrix &transform);

private:
    SkMatrix transform_;
};
} // namespace sm

#endif //SHOWMAKER_TANSFORM_LAYER_H
