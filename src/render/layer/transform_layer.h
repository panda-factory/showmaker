//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef XXX_TANSFORM_LAYER_H
#define XXX_TANSFORM_LAYER_H

#include "render/layer/container_layer.h"

class TransformLayer : public ContainerLayer {
public:
    void Paint(SkCanvas* canvas) const override;

    TransformLayer(const SkMatrix& transform);

private:
    SkMatrix transform_;
};


#endif //XXX_TANSFORM_LAYER_H
