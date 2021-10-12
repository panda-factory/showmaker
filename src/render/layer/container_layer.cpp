//
// Created by guozhenxiong on 2021-08-18.
//

#include "container_layer.h"

namespace sm {
void ContainerLayer::Add(std::shared_ptr<Layer> layer)
{
    layers_.emplace_back(std::move(layer));
}

void ContainerLayer::Paint(SkCanvas *canvas) const
{
    PaintChildren(canvas);
}

void ContainerLayer::PaintChildren(SkCanvas *canvas) const
{
    for (auto &layer : layers_) {
        layer->Paint(canvas);
    }
}

void ContainerLayer::AddToScene(SceneBuilder *builder, Position offset)
{
    AddChildrenToScene(builder, offset);
}

void ContainerLayer::AddChildrenToScene(SceneBuilder *builder, Position offset)
{
    for (auto &layer : layers_) {
        layer->AddToScene(builder);
    }
}
} // namespace sm