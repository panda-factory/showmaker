//
// Created by guozhenxiong on 2021-08-18.
//

#include "layer.h"

#include "wtf/diagnostics/diagnostics_property.h"

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

/// | DiagnosticableTree |
void Layer::DebugFillProperties(DiagnosticPropertiesBuilder* properties) {
    DiagnosticableTree::DebugFillProperties(properties);
    properties->Add(DiagnosticsProperty<decltype(owner_)>("owner", owner_, "", parent_ != nullptr ? DiagnosticLevel::HIDDEN : DiagnosticLevel::INFO));
    properties->Add(DiagnosticsProperty<decltype(owner_)>("creator", nullptr, "", DiagnosticLevel::DEBUG));
    //if (_engineLayer != null) {
    //    properties.add(DiagnosticsProperty<String>('engine layer', describeIdentity(_engineLayer)));
    //}
    //properties->Add(DiagnosticsProperty<int>('handles', debugHandleCount));
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