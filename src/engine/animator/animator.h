//
// Created by guozhenxiong on 2021-09-18.
//

#ifndef STRUGGLE_ANIMATOR_H
#define STRUGGLE_ANIMATOR_H

#include <memory>

#include "vsync_waiter.h"

namespace strg {
class Animator final {
public:
    class Delegate {
    public:
        virtual void OnAnimatorBeginFrame(fml::TimePoint frame_target_time) = 0;
    };

    void AwaitVSync();

    void BeginFrame(const fml::TimePoint& frame_target_time);

    void RequestFrame();

    Animator(Delegate& delegate,
             TaskRunners* task_runners,
             std::unique_ptr<VsyncWaiter> waiter);

private:
    Delegate& delegate_;

    const TaskRunners* task_runners_;

    std::unique_ptr<VsyncWaiter> waiter_;
};
} // namespace strg

#endif //STRUGGLE_ANIMATOR_H
