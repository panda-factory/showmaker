//
// Created by guozhenxiong on 2021-10-30.
//

#ifndef SHOWMAKER_LEADER_LAYER_H
#define SHOWMAKER_LEADER_LAYER_H

#include "render/layer/container_layer.h"
#include "render/layer/layer_link.h"
#include "graphics/offset.h"

namespace sm {
class LeaderLayer : public ContainerLayer {
public:
    LeaderLayer(LayerLink* link, Offset offset = Offset::ZERO);

protected:
    bool AlwaysNeedsAddToScene() override { return true; }

private:
    Offset offset_;

    LayerLink* link_;
};
} // namespace sm

#endif //SHOWMAKER_LEADER_LAYER_H
