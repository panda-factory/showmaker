//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef STRUGGLE_CONTAINER_LAYER_H
#define STRUGGLE_CONTAINER_LAYER_H

#include <vector>

#include "render/layer/layer.h"

namespace strg {
class ContainerLayer : public Layer {
public:
    virtual void Add(std::shared_ptr<Layer> layer);

    void Paint(SkCanvas *canvas) const override;

    void AddToScene(SceneBuilder *builder, Position offset = {0, 0}) override;

    void PaintChildren(SkCanvas *canvas) const;

    ContainerLayer() = default;

    ~ContainerLayer() = default;

protected:
    void AddChildrenToScene(SceneBuilder *builder, Position offset);

private:
    std::vector<std::shared_ptr<Layer>> layers_;
};
} // namespace strg

#endif //STRUGGLE_CONTAINER_LAYER_H
