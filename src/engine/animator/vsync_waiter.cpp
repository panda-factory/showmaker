//
// Created by guozhenxiong on 2021-09-20.
//

#include "vsync_waiter.h"

namespace wtf {
VsyncWaiter::VsyncWaiter(const TaskRunners *task_runners)
  : task_runners_(task_runners)
{}

VsyncWaiter::~VsyncWaiter() = default;

void VsyncWaiter::AsyncWaitForVsync(const Invoker& invoker)
{
    {
        std::scoped_lock lock(invoker_mutex_);
        if (invoker_) {
            return;
        }
        invoker_ = std::move(invoker);
    }
    AwaitVSync();
}

void VsyncWaiter::Invoke(const fml::TimePoint& frame_start_time,
                         const fml::TimePoint& frame_target_time)
{
    Invoker invoker;
    {
        std::scoped_lock lock(invoker_mutex_);
        invoker = std::move(invoker_);
    }

    if (invoker) {
        task_runners_->GetUITaskRunner()->PostTaskForTime(
                [invoker, frame_start_time, frame_target_time]() {
                    invoker(frame_target_time);
                },
                frame_start_time);
    }
}
} // namespace wtf