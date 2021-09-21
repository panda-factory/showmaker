//
// Created by guozhenxiong on 2021-09-20.
//

#ifndef XXX_VSYNC_WAITER_WIN32_H
#define XXX_VSYNC_WAITER_WIN32_H

#include "vsync_waiter.h"

namespace wtf {
class VsyncWaiterWin32 : public VsyncWaiter {
public:
    // | VsyncWaiter |
    void AwaitVSync() override;

    explicit VsyncWaiterWin32(const TaskRunners *task_runners);

    ~VsyncWaiterWin32() override;

private:
    fml::TimePoint phase_;
};
} // namespace wtf

#endif //XXX_VSYNC_WAITER_WIN32_H
