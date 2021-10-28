//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef SHOWMAKER_LAYER_H
#define SHOWMAKER_LAYER_H

#include "graphics/position.h"
#include "node/abstract_node.h"

#include <third_party/skia/include/core/SkPicture.h>
#include <third_party/skia/include/core/SkCanvas.h>

namespace sm {
class SceneBuilder;

class Layer : public AbstractNode {
public:
    virtual void Paint(SkCanvas *canvas) const = 0;

    virtual void AddToScene(SceneBuilder *builder, Position offset = {0, 0}) = 0;

    /// | AbstractNode |
    void AdoptChild(AbstractNode *child) override;

    /// | AbstractNode |
    void DropChild(AbstractNode *child) override;

    Layer();

    virtual ~Layer();

protected:
    void MarkNeedsAddToScene();

    bool AlwaysNeedsAddToScene() { return false; }

    Layer* previous_sibling_ = nullptr;

private:
    bool needs_add_to_scene_ = true;
};
} // namespace sm

#endif //SHOWMAKER_LAYER_H
