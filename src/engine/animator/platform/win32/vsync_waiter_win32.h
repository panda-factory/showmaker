//
// Created by guozhenxiong on 2021-09-20.
//

#ifndef STRUGGLE_VSYNC_WAITER_WIN32_H
#define STRUGGLE_VSYNC_WAITER_WIN32_H

#include "vsync_waiter.h"

namespace strg {
class VsyncWaiterWin32 : public VsyncWaiter {
public:
    // | VsyncWaiter |
    void AwaitVSync() override;

    explicit VsyncWaiterWin32(const TaskRunners *task_runners);

    ~VsyncWaiterWin32() override;

private:
    fml::TimePoint phase_;
};
} // namespace strg

#endif //STRUGGLE_VSYNC_WAITER_WIN32_H
