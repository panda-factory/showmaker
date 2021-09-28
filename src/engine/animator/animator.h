//
// Created by guozhenxiong on 2021-09-18.
//

#ifndef XXX_ANIMATOR_H
#define XXX_ANIMATOR_H

#include <memory>

#include "vsync_waiter.h"

namespace wtf {
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
} // namespace wtf

#endif //XXX_ANIMATOR_H
