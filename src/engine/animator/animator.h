//
// Created by guozhenxiong on 2021-09-18.
//

#ifndef XXX_ANIMATOR_H
#define XXX_ANIMATOR_H

#include <memory>

#include "vsync_waiter.h"

namespace wtf {
class Animator {
public:
    void AwaitVsync();

    void BeginFrame();

private:
    std::unique_ptr<VsyncWaiter> waiter_;
};
} // namespace wtf

#endif //XXX_ANIMATOR_H
