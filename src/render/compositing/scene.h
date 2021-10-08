//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef STRUGGLE_SCENE_H
#define STRUGGLE_SCENE_H

#include <memory>

#include "render/layer/layer.h"

namespace strg {
class Scene {
public:
    static std::unique_ptr<Scene> Create(std::shared_ptr<Layer> rootLayer);

    inline std::shared_ptr<Layer> root_layer()
    { return root_layer_; }

    ~Scene();

private:
    explicit Scene(std::shared_ptr<Layer> rootLayer);

    std::shared_ptr<Layer> root_layer_;
};
} // namespace strg

#endif //STRUGGLE_SCENE_H
