//
// Created by guozhenxiong on 2021-10-30.
//

#ifndef SHOWMAKER_FOLLOWER_LAYER_H
#define SHOWMAKER_FOLLOWER_LAYER_H

#include "render/layer/container_layer.h"
#include "render/layer/layer_link.h"

namespace sm {
class FollowerLayer : public ContainerLayer {
public:
    FollowerLayer(LayerLink* link);

protected:
    bool AlwaysNeedsAddToScene() override { return true; }

private:
    LayerLink* link_;
};
} // namespace sm

#endif //SHOWMAKER_FOLLOWER_LAYER_H
