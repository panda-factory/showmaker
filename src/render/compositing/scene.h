//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef SHOWMAKER_SCENE_H
#define SHOWMAKER_SCENE_H

#include <memory>

#include "render/layer/layer.h"

namespace sm {
class Scene {
public:
    static std::unique_ptr<Scene> Create(std::shared_ptr<Layer> rootLayer);

    inline std::shared_ptr<Layer> root_layer()
    { return root_layer_; }

    Scene (const Scene& scene) = default;

    ~Scene();

private:
    explicit Scene(std::shared_ptr<Layer> rootLayer);

    std::shared_ptr<Layer> root_layer_;
};
} // namespace sm

#endif //SHOWMAKER_SCENE_H
