//
// Created by guozhenxiong on 2021-11-05.
//

#include "render_object.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {
void RenderObject::Attach(void *owner)
{
    FML_CHECK(!debug_disposed_);
    AbstractNode::Attach(owner);

    // If the node was dirtied in some way while unattached, make sure to add
    // it to the appropriate dirty list now that an owner is available
    if (needs_layout_ && relayout_boundary_ != nullptr) {
        // Don't enter this block if we've never laid out at all;
        // scheduleInitialLayout() will handle it
        needs_layout_ = false;
        MarkNeedsLayout();
    }/*
    if (needs_compositingB_bits_update_) {
        needs_compositingB_bits_update_ = false;
        markNeedsCompositingBitsUpdate();
    }
    if (_needsPaint && _layerHandle.layer != null) {
        // Don't enter this block if we've never painted at all;
        // scheduleInitialPaint() will handle it
        _needsPaint = false;
        markNeedsPaint();
    }
    if (_needsSemanticsUpdate && _semanticsConfiguration.isSemanticBoundary) {
        // Don't enter this block if we've never updated semantics at all;
        // scheduleInitialSemantics() will handle it
        _needsSemanticsUpdate = false;
        markNeedsSemanticsUpdate();
    }*/
}

bool RenderObject::DebugCanPerformMutations()
{
    bool result;

    if (debug_disposed_) {
        result = false;
        return true;
    }
    /*.............*/

    return true;
}

bool RenderObject::DebugSubtreeRelayoutRootAlreadyMarkedNeedsLayout()
{
    if (relayout_boundary_ == nullptr)
        return true; // we don't know where our relayout boundary is yet
    RenderObject* node = this;
    while (node != relayout_boundary_) {
        FML_CHECK(node->relayout_boundary_ == relayout_boundary_);
        FML_CHECK(node->parent_ != nullptr);
        node = (RenderObject*)node->parent_;
        if ((!node->needs_layout_) && (!node->debug_doing_this_layout_))
            return false;
    }
    FML_CHECK(node->relayout_boundary_ == node);
    return true;
}

void RenderObject::MarkNeedsLayout()
{
    FML_CHECK(DebugCanPerformMutations());
    if (needs_layout_) {
        FML_CHECK(DebugSubtreeRelayoutRootAlreadyMarkedNeedsLayout());
        return;
    }
    FML_CHECK(relayout_boundary_ != nullptr);
    if (relayout_boundary_ != this) {
        MarkParentNeedsLayout();
    } else {
        needs_layout_ = true;
        if (owner_ != nullptr) {
            owner()->nodes_needing_layout_.emplace_back(this);
            owner()->RequestVisualUpdate();
        }
    }
}

void RenderObject::MarkNeedsCompositingBitsUpdate()
{
    FML_CHECK(!debug_disposed_);
    if (needs_compositingB_bits_update_)
        return;
    needs_compositingB_bits_update_ = true;/*
    if (parent is RenderObject) {
        final RenderObject parent = this.parent! as RenderObject;
        if (parent._needsCompositingBitsUpdate)
            return;
        if (!isRepaintBoundary && !parent.isRepaintBoundary) {
            parent.markNeedsCompositingBitsUpdate();
            return;
        }
    }
    // parent is fine (or there isn't one), but we are dirty
    if (owner != null)
        owner!._nodesNeedingCompositingBitsUpdate.add(this);*/
}

void RenderObject::MarkParentNeedsLayout()
{
    needs_layout_ = true;
    FML_CHECK(this->parent_ != nullptr);
    RenderObject* parent = (RenderObject*)this->parent_;
    if (!doing_this_layout_with_callback_) {
        parent->MarkNeedsLayout();
    } else {
        FML_CHECK(parent->debug_doing_this_layout_);
    }
    FML_CHECK(parent == this->parent_);
}

} // namespace sm