//
// Created by guozhenxiong on 2021-11-05.
//

#ifndef SHOWMAKER_PIPELINE_OWNER_H
#define SHOWMAKER_PIPELINE_OWNER_H

#include <functional>

#include "semantics/semantics_handle.h"
#include "semantics/semantics_owner.h"

namespace sm {
class RenderObject;

class PipelineOwner {
public:
    friend class RenderObject;

    std::unique_ptr<SemanticsHandle> EnsureSemantics(std::function<void ()> listener = nullptr);

    inline void OnNeedVisualUpdate() {
        if (on_need_visual_update_)
            on_need_visual_update_();
    }

    inline void OnSemanticsOwnerCreated() {
        if (on_need_visual_update_)
            on_semantics_owner_created_();
    }

    inline void OnSemanticsOwnerDisposed() {
        if (on_need_visual_update_)
            on_semantics_owner_disposed_();
    }

    inline void RequestVisualUpdate() {
        OnNeedVisualUpdate();
    }

    inline std::unique_ptr<SemanticsOwner>& semantics_owner() { return semantics_owner_; }

    PipelineOwner(std::function<void ()> on_need_visual_update = nullptr,
                  std::function<void ()> on_semantics_owner_created = nullptr,
                  std::function<void ()> on_semantics_owner_disposed = nullptr) :
            on_need_visual_update_(on_need_visual_update),
            on_semantics_owner_created_(on_semantics_owner_created),
            on_semantics_owner_disposed_(on_semantics_owner_disposed) {}

private:
    std::function<void ()> on_need_visual_update_;

    std::function<void ()> on_semantics_owner_created_;

    std::function<void ()> on_semantics_owner_disposed_;

    int outstanding_semantics_handles_ = 0;

    std::unique_ptr<SemanticsOwner> semantics_owner_;
    std::vector<RenderObject*> nodes_needing_layout_;
};
} // namespace sm

#endif //SHOWMAKER_PIPELINE_OWNER_H
