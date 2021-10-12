//
// Created by guozhenxiong on 2021-08-22.
//

#ifndef SHOWMAKER_OFFSET_LAYER_H
#define SHOWMAKER_OFFSET_LAYER_H

#include "render/layer/container_layer.h"

namespace sm {
class OffsetLayer : public ContainerLayer {
public:
    void Paint(SkCanvas *canvas) const override;

    void AddToScene(SceneBuilder *, Position) override;

    OffsetLayer(const float x, const float y);

private:
    SkPoint offset_;
};
} // namespace sm

#endif //SHOWMAKER_OFFSET_LAYER_H
