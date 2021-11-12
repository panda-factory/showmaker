//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef SHOWMAKER_LAYER_H
#define SHOWMAKER_LAYER_H

#include "graphics/position.h"
#include "node/abstract_node.h"
#include "wtf/diagnostics/diagnosticable_tree.h"

#include <third_party/skia/include/core/SkPicture.h>
#include <third_party/skia/include/core/SkCanvas.h>

namespace sm {
class SceneBuilder;

class Layer : public AbstractNode, public DiagnosticableTree {
    DECLARE_META_INFO(Layer, AbstractNode);
public:
    virtual void Paint(SkCanvas *canvas) const = 0;

    virtual void AddToScene(SceneBuilder *builder, Position offset = {0, 0}) = 0;

    /// | AbstractNode |
    void AdoptChild(AbstractNode *child) override;

    /// | AbstractNode |
    void DropChild(AbstractNode *child) override;

    /// | DiagnosticableTree |
    void DebugFillProperties(DiagnosticPropertiesBuilder* properties) override;

    void Remove();

    virtual void RemoveChild(Layer* child) {}

    Layer();

    virtual ~Layer();

protected:
    friend class ContainerLayer;

    virtual bool AlwaysNeedsAddToScene() { return false; }

    Layer* previous_sibling_ = nullptr;

    Layer* next_sibling_ = nullptr;

    bool needs_add2scene_ = true;

private:


#if TESTING
public:
    void DebugMarkClean();
    bool DebugSubtreeNeedsAddToScene();
    virtual void UpdateSubtreeNeedsAddToScene();
    void MarkNeedsAddToScene();
#else
public:
    void DebugMarkClean() {}
    bool DebugSubtreeNeedsAddToScene() {return false;}
    virtual void UpdateSubtreeNeedsAddToScene() {}
    void MarkNeedsAddToScene() {}
#endif // TESTING
};
} // namespace sm

#endif //SHOWMAKER_LAYER_H
