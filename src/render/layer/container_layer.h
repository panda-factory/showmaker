//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef XXX_CONTAINER_LAYER_H
#define XXX_CONTAINER_LAYER_H

#include <vector>

#include "render/layer/layer.h"

class ContainerLayer : public Layer {
public:
    virtual void Add(std::shared_ptr<Layer> layer);

    void Paint(SkCanvas* canvas) const override;

    void PaintChildren(SkCanvas* canvas) const;

private:
    std::vector<std::shared_ptr<Layer>> layers_;
};


#endif //XXX_CONTAINER_LAYER_H