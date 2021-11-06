//
// Created by guozhenxiong on 2021-11-05.
//

#include "pipeline_owner.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {

std::unique_ptr<SemanticsHandle> PipelineOwner::EnsureSemantics(std::function<void ()> listener)
{
    outstanding_semantics_handles_++;
    if (outstanding_semantics_handles_ == 1) {
        FML_CHECK(semantics_owner_ == nullptr);
        semantics_owner_ = std::make_unique<SemanticsOwner>();
        OnSemanticsOwnerCreated();
    }

    return SemanticsHandle::Create(this, listener);
}

} // namespace sm