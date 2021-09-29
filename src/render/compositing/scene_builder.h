//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef STRUGGLE_SCENE_BUILDER_H
#define STRUGGLE_SCENE_BUILDER_H

#include <memory>

#include "render/compositing/scene.h"
#include "render/layer/container_layer.h"
#include "render/painting/picture.h"

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


#endif //STRUGGLE_SCENE_BUILDER_H
