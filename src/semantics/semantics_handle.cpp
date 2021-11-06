//
// Created by guozhenxiong on 2021-11-05.
//

#include "semantics_handle.h"

#include "render/pipeline/pipeline_owner.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {

/// | static |
std::unique_ptr<SemanticsHandle> SemanticsHandle::Create(PipelineOwner* owner, const std::function<void ()>& listener)
{
    FML_CHECK(owner != nullptr);

    return std::unique_ptr<SemanticsHandle>(new SemanticsHandle(owner, listener));
}

SemanticsHandle::SemanticsHandle(PipelineOwner* owner, const std::function<void ()>& listener)
  : owner_(owner), listener_(listener)
{
    if (listener_ != nullptr) {
        if (owner_->semantics_owner()) {
            owner_->semantics_owner()->AddListener(listener);
        }
    }
}
} // namespace sm