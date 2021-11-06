//
// Created by guozhenxiong on 2021-11-05.
//

#ifndef SHOWMAKER_SEMANTICS_HANDLE_H
#define SHOWMAKER_SEMANTICS_HANDLE_H
#include <functional>

namespace sm {
class PipelineOwner;

class SemanticsHandle {
public:
    static std::unique_ptr<SemanticsHandle> Create(PipelineOwner* owner, const std::function<void ()>& listener);

private:
    SemanticsHandle(PipelineOwner* owner, const std::function<void ()>& listener);

    PipelineOwner* owner_;

    std::function<void ()> listener_;
};
} // namespace sm

#endif //SHOWMAKER_SEMANTICS_HANDLE_H
