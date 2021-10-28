//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef SHOWMAKER_CONTAINER_LAYER_H
#define SHOWMAKER_CONTAINER_LAYER_H

#include <vector>

#include "render/layer/layer.h"

namespace sm {
class ContainerLayer : public Layer {
public:
    virtual void Add(std::shared_ptr<Layer> layer);

    void Append(Layer* child);

    void Paint(SkCanvas *canvas) const override;

    void AddToScene(SceneBuilder *builder, Position offset = {0, 0}) override;

    void PaintChildren(SkCanvas *canvas) const;

    ContainerLayer() = default;

    ~ContainerLayer() = default;

protected:
    void AddChildrenToScene(SceneBuilder *builder, Position offset);

private:
    std::vector<std::shared_ptr<Layer>> layers_;

    Layer* last_child_;
};
} // namespace sm

#endif //SHOWMAKER_CONTAINER_LAYER_H
