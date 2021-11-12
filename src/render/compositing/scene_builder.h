//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef SHOWMAKER_SCENE_BUILDER_H
#define SHOWMAKER_SCENE_BUILDER_H

#include <memory>

#include "render/compositing/scene.h"
#include "render/painting/picture.h"

namespace sm {
class ContainerLayer;

class SceneBuilder {
public:
    static std::unique_ptr<SceneBuilder> Create();

    std::unique_ptr<Scene> Build();

    void AddPicture(double dx, double dy, std::unique_ptr<Picture> picture);

    void PushOffset(double dx, double dy);

    void Pop();

    SceneBuilder();

    ~SceneBuilder();

private:
    void AddLayer(std::shared_ptr<Layer> layer);

    void PushLayer(std::shared_ptr<ContainerLayer> layer);

    void PopLayer();

    std::vector<std::shared_ptr<ContainerLayer>> layer_stack_;
};
} // namespace sm

#endif //SHOWMAKER_SCENE_BUILDER_H
