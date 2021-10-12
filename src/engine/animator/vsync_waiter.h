//
// Created by guozhenxiong on 2021-09-20.
//

#ifndef SHOWMAKER_VSYNC_WAITER_H
#define SHOWMAKER_VSYNC_WAITER_H

#include <mutex>
#include <functional>

#include "engine/thread_host.h"
#include "engine/task_runners.h"

namespace sm {
class VsyncWaiter {
public:
    using Invoker = std::function<void(const fml::TimePoint&)>;

    void AsyncWaitForVsync(const Invoker& invoker);

    virtual void AwaitVSync() = 0;

    virtual ~VsyncWaiter();

protected:
    explicit VsyncWaiter(const TaskRunners *task_runners);

    void Invoke(const fml::TimePoint& frame_start_time,
                const fml::TimePoint& frame_target_time);

private:
    std::mutex invoker_mutex_;

    Invoker invoker_;

    const TaskRunners *task_runners_;
};
} // namespace sm

#endif //SHOWMAKER_VSYNC_WAITER_H
