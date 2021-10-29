//
// Created by guozhenxiong on 2021-08-18.
//

#include "layer.h"

#include <third_party/flutter/fml/logging.h>

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

void Layer::Remove()
{
    auto parent = (Layer*)parent_;
    parent->RemoveChild(this);
}

#if TESTING
void Layer::MarkNeedsAddToScene()
{
    // Already marked. Short-circuit.
    if (needs_add2scene_) {
        return;
    }

    needs_add2scene_ = true;
}

void Layer::DebugMarkClean() {
    needs_add2scene_ = false;
}
bool Layer::DebugSubtreeNeedsAddToScene() {
    return needs_add2scene_;
}
void Layer::UpdateSubtreeNeedsAddToScene() {
    needs_add2scene_ = needs_add2scene_ || AlwaysNeedsAddToScene();
}
#endif // TESTING
} // namespace sm