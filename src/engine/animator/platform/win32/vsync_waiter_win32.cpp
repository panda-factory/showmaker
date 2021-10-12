//
// Created by guozhenxiong on 2021-09-20.
//

#include "vsync_waiter_win32.h"

#include <chrono>

namespace sm {
namespace {
static fml::TimePoint SnapToNextTick(fml::TimePoint value,
                                     fml::TimePoint tick_phase,
                                     fml::TimeDelta tick_interval) {
    fml::TimeDelta offset = (tick_phase - value) % tick_interval;
    if (offset != fml::TimeDelta::Zero())
        offset = offset + tick_interval;
    return value + offset;
}
} // namespace

VsyncWaiterWin32::VsyncWaiterWin32(const TaskRunners *task_runners)
  : VsyncWaiter(task_runners),
    phase_(fml::TimePoint::Now())
{}

VsyncWaiterWin32::~VsyncWaiterWin32() = default;

// | VsyncWaiter |
void VsyncWaiterWin32::AwaitVSync()
{

    constexpr fml::TimeDelta kSingleFrameInterval =
            fml::TimeDelta::FromSecondsF(1.0 / 60.0);

    auto next =
            SnapToNextTick(fml::TimePoint::Now(), phase_, kSingleFrameInterval);

    Invoke(next, next + kSingleFrameInterval);
}
} // namespace sm