//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef SHOWMAKER_CONTAINER_LAYER_H
#define SHOWMAKER_CONTAINER_LAYER_H

#include <vector>
#include <list>

#include "render/layer/layer.h"
#include "render/compositing/scene.h"
#include "render/compositing/scene_builder.h"

namespace sm {
class ContainerLayer : public Layer {
public:
    virtual void Add(std::shared_ptr<Layer> layer);

    void Append(Layer* child);

    std::unique_ptr<Scene> BuildScene(SceneBuilder builder);

    void Paint(SkCanvas *canvas) const override;

    void AddToScene(SceneBuilder *builder, Position offset = {0, 0}) override;

    void PaintChildren(SkCanvas *canvas) const;

    /// | Layer |
    void RemoveChild(Layer* child) override;

    ContainerLayer() = default;

    ~ContainerLayer() = default;

protected:
    void AddChildrenToScene(SceneBuilder *builder, Position offset);

private:
    std::vector<std::shared_ptr<Layer>> layers_;

    Layer* last_child_;

    Layer* first_child_;

#if TESTING
public:
    std::list<Layer*> DepthFirstIterateChildren();
    void UpdateSubtreeNeedsAddToScene() override;
#endif // TESTING
};
} // namespace sm

#endif //SHOWMAKER_CONTAINER_LAYER_H
