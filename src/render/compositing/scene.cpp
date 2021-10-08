//
// Created by guozhenxiong on 2021-08-18.
//

#include "scene.h"

namespace strg {
std::unique_ptr<Scene> Scene::Create(std::shared_ptr<Layer> root_layer)
{
    std::unique_ptr<Scene> scene;
    scene.reset(new Scene(root_layer));
    return std::move(scene);
}

Scene::Scene(std::shared_ptr<Layer> root_layer)
{
    root_layer_ = root_layer;
}

Scene::~Scene() = default;
} // namespace strg