//
// Created by guozhenxiong on 2021-08-18.
//

#include "layer.h"

namespace sm {
Layer::Layer()
{}

Layer::~Layer() = default;

/// | AbstractNode |
void Layer::AdoptChild(AbstractNode *child)
{
    if (!AlwaysNeedsAddToScene()) {
        MarkNeedsAddToScene();
    }
    AbstractNode::AdoptChild(child);
}

/// | AbstractNode |
void Layer::DropChild(AbstractNode *child)
{
    if (!AlwaysNeedsAddToScene()) {
        MarkNeedsAddToScene();
    }
    AbstractNode::DropChild(child);
}
void Layer::MarkNeedsAddToScene()
{
    // Already marked. Short-circuit.
    if (needs_add_to_scene_) {
        return;
    }

    needs_add_to_scene_ = true;
}
} // namespace sm