//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef XXX_SCENE_H
#define XXX_SCENE_H

#include <memory>

#include "render/layer/layer.h"

class Scene {
public:
    static std::unique_ptr<Scene> Create(std::shared_ptr<Layer> rootLayer);

    inline std::shared_ptr<Layer> root_layer() {return root_layer_;}

    ~Scene();
private:
    explicit Scene(std::shared_ptr<Layer> rootLayer);

    std::shared_ptr<Layer> root_layer_;
};


#endif //XXX_SCENE_H