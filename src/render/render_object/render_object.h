//
// Created by guozhenxiong on 2021-11-05.
//

#ifndef SHOWMAKER_RENDER_OBJECT_H
#define SHOWMAKER_RENDER_OBJECT_H

#include "node/abstract_node.h"
#include "graphics/rect.h"
#include "semantics/semantics_configuration.h"
#include "render/pipeline/pipeline_owner.h"

namespace sm {
class RenderObject : public AbstractNode {
public:
    virtual bool IsRepaintBoundary() const { return false; }

    virtual Rect GetPaintBounds() = 0;

    virtual Rect GetSemanticBounds() = 0;

    /// | AbstractNode |
    void Attach(void *owner) override;

    PipelineOwner* owner() { return (PipelineOwner*)owner_; }

    void MarkNeedsLayout();

protected:
    virtual void DebugAssertDoesMeetConstraints() = 0;

    virtual void PerformLayout() = 0;

    virtual void PerformResize() = 0;

    virtual void DescribeSemanticsConfiguration(SemanticsConfiguration config) {
        // Nothing to do by default.
    }

    void MarkParentNeedsLayout();

    void MarkNeedsCompositingBitsUpdate();

private:
    bool DebugCanPerformMutations();

    bool DebugSubtreeRelayoutRootAlreadyMarkedNeedsLayout();

    bool debug_disposed_ = false;

    bool debug_doing_this_layout_ = false;

    bool doing_this_layout_with_callback_ = false;

    bool needs_layout_ = true;

    bool needs_compositingB_bits_update_ = false;

    RenderObject* relayout_boundary_;
};
} // namespace sm

#endif //SHOWMAKER_RENDER_OBJECT_H
