//
// Created by guozhenxiong on 2021-09-20.
//

#ifndef SHOWMAKER_VSYNC_WAITER_WIN32_H
#define SHOWMAKER_VSYNC_WAITER_WIN32_H

#include "vsync_waiter.h"

namespace sm {
class VsyncWaiterWin32 : public VsyncWaiter {
public:
    // | VsyncWaiter |
    void AwaitVSync() override;

    explicit VsyncWaiterWin32(const TaskRunners *task_runners);

    ~VsyncWaiterWin32() override;

private:
    fml::TimePoint phase_;
};
} // namespace sm

#endif //SHOWMAKER_VSYNC_WAITER_WIN32_H
