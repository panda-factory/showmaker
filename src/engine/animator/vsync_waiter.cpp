//
// Created by guozhenxiong on 2021-09-20.
//

#include "vsync_waiter.h"

namespace wtf {
VsyncWaiter::VsyncWaiter(const TaskRunners *task_runners)
  : task_runners_(task_runners)
{}

void VsyncWaiter::AsyncWaitForVsync(const Invoker& callback)
{
    this->AwaitVSync();
}

void VsyncWaiter::Invoke(const fml::TimePoint& frame_start_time,
                         const fml::TimePoint& frame_target_time)
{
    Invoker invoker = std::move(invoker_);
    if (invoker_) {
        task_runners_->GetUITaskRunner()->PostTaskForTime(
                [invoker, frame_start_time, frame_target_time]() {
                    invoker(frame_target_time);
                },
                frame_start_time);
    }
}
} // namespace wtf